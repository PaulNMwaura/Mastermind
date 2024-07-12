#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define BUF_SIZE 5
#define MAX 5

char* my_itoa(int val, int base) {
    static char buf[32] = {0};
    int i = 30;

    for (; val && i; --i, val /= base) 
        buf[i] = "0123456789abcdef"[val % base];
    return &buf[i + 1];
}

char* get_input() {
    char* buf = malloc(sizeof(char) * BUF_SIZE);
    char c;
    int nbr_read;
    int index = 0;

    while (index < BUF_SIZE && (nbr_read = read(STDIN_FILENO, &c, 1)) > 0) {
        if (c == '\n') {
            break;
        }
        buf[index] = c;
        index += 1;
    }
    if (nbr_read == 0 && index == 0) {
        return NULL;
    }
    buf[index] = '\0';
    return buf;
    free(buf);
}

void give_hint(char* secrete_code_str) {
    time_t x;
    srand((unsigned)time(&x));
    int random_index = rand() % ((int)strlen(secrete_code_str));
    printf("%c is part of the code\n", secrete_code_str[random_index]);
}

int guess_code_success(char* input, char* secrete_code_str) {
    if(strcmp(input, secrete_code_str) == 0) {
        printf("Congratz! You cracked the code!\n");
        return 0;
    }
    return -1;
}

int guess_code_invalid(char* input, char* secrete_code_str) {
    if (strlen(input) != strlen(secrete_code_str)) {
        printf("Wrong Input. %d characters required in your guess\n", MAX - 1);
        return 0;
    }
    return -1;
}

void guess_code_matching(char* input, char* secrete_code_str, int well_placed, int misplaced){ 
    for (int i = 0; (unsigned)i < strlen(input); i++) {
        for (int j = 0; (unsigned)j < strlen(secrete_code_str); j++) {
            if ((input[i] == secrete_code_str[j]) && i == j) {
                well_placed++;
            }
            else if ((input[i] == secrete_code_str[j]) && i != j) {
                misplaced++;
            }
        }
    }
    printf("Well placed pieces: %d\n", well_placed);
    printf("Misplaced pieces: %d\n", misplaced);   
}

void handle_input(char* input, char* secrete_code_str) {
    int well_placed = 0; 
    int misplaced   = 0;
    if(strlen(input) != strlen(secrete_code_str)) {
        if(strlen(input) > strlen(secrete_code_str)) {
            return;
        }
        printf("The code is %d digits long\n", (int)strlen(secrete_code_str));
    } else if(strcmp(input, "hint") == 0) {
        give_hint(secrete_code_str);
    } else if((guess_code_success(input, secrete_code_str)) == -1) {
        if((guess_code_invalid(input, secrete_code_str)) == -1){
            guess_code_matching(input, secrete_code_str, well_placed, misplaced);
        }
    } 
    else {
        exit(EXIT_SUCCESS);
    }
}

bool is_unique(char* secrete_code_str){
    bool unique = true;
    for(int i = 0; i < (int)strlen(secrete_code_str); i++) {
        for(int j = 0; j < (int)strlen(secrete_code_str); j++) {
            if(secrete_code_str[i] == secrete_code_str[j]) {
                unique = false;
            }
        }
    }
    return unique;
}

char* generate_code(char* secrete_code_str) {
    if((secrete_code_str == NULL)) {
        secrete_code_str = (char*)malloc(MAX * sizeof(char));
        int digits[10];
        time_t t;
        srand((unsigned)time(&t));
        
        // Populate digits[] with nums 0-9
        for (int i = 0; i < 10; i++) {
            digits[i] = i;
        }

        // Shuffle the array using Fisher-Yates algorithm
        for (int i = 9; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = digits[i];
            digits[i] = digits[j];
            digits[j] = temp;
        }

        // Use the first four digits for the unique 4-digit number
        for (int i = 0; i < 4; i++) {
            secrete_code_str[i] =  '0' + digits[i];
        }
        secrete_code_str[4] = '\0';
    }
    return secrete_code_str;
}

char* handle_cflag(int argc, char* argv[]){
    for(int i = 0; i < argc; i++) {
        if(argv[i][1] == 'c') {
            return argv[i + 1];
        }
    }
    char* secrete_code_str = generate_code(NULL);
    return secrete_code_str;
}

int handle_attempts(int argc, char* argv[]) {
    for(int i = 0; i < argc; i++) {
        if(argv[i][1] == 't') {
            return atoi(argv[i + 1]);
        }
    }
    return 10;
}

void start_game(int argc, char* argv[]) {
    int round   = 0;
    int attempts = handle_attempts(argc, argv);
    char* secrete_code_str = handle_cflag(argc, argv);
    printf("Will you find the secrete code?\nFor a hint type \"hint\"\nPlease enter your guess\n");

    while(round < attempts) {
        // Printing round + 1 to match corresponding attempt number;
        printf("Round %d\n", round + 1);
        char* input = get_input();

        if(input != NULL) {
            printf(">%s\n---\n", input);
            handle_input(input, secrete_code_str);
            round++;
            free(input);
        }
    }
    printf("Play Again? (Y/N): ");
    char* restart = get_input();
    if(strcmp(restart, "Y") == 0)
    {
        start_game(argc, argv);
    } else {
        printf("The secrete code was: %s\n", secrete_code_str);
        free(restart);
        free(secrete_code_str);
    }
    return;
}

void validate_commands(int argc, char* argv[]) {
    start_game(argc, argv);
}

void execute(int argc, char* argv[]) {
    // Changed architecture so that if 2 or more flags are presents, The game only runs once.
    validate_commands(argc, argv);
}

int main(int argc, char* argv[]) {
    execute(argc, argv);

    // Not necessary for this project, but allows for user to manually terminate program 
    // by pressing ENTER when the game is done.
    getchar();
}