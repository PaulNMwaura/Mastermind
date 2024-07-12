# Mastermind Game

## Overview
This is a C implementation of the classic Mastermind game. The goal of the game is to guess a secret 4-digit code with unique digits. The game provides feedback on each guess in the form of well-placed and misplaced digits.

## Features
```
- Generate a random 4-digit secret code with unique digits.
- Allow user to guess the code within a limited number of attempts.
- Provide hints when requested by the user.
- Display the number of well-placed and misplaced digits after each guess.
- Allow customization of the secret code and number of attempts through command-line flags.
- Option to play the game again after completing a round.
```
## Getting Started
Running the Game <br />
    To run the compiled game, use the following command:
    ```
    $>./Mastermind 
    ```

Command-Line Flags
    -c [code]: Specify a custom 4-digit secret code with unique digits. <br />
    -t [attempts]: Specify the maximum number of attempts allowed. <br />

Examples <br />
    Run the game with a custom secret code:
    ```
    $>./mastermind -c 1234
    ```
    Run the game with a specified number of attempts:
    ```
    $>./mastermind -t 15
    ```
    Run the game with both custom code and attempts:
    ```
    $>./mastermind -c 1234 -t 15
    ```

Game Instructions
1. The game will prompt you to guess the 4-digit secret code.
2. Enter your guess and press Enter.
3. The game will provide feedback:
4. Well placed pieces: The number of digits that are correct and in the correct position.
5. Misplaced pieces: The number of digits that are correct but in the wrong position.
6. If you want a hint, type hint and press Enter.
7. The game continues until you either guess the code correctly or run out of attempts.
8. After the game ends, you will have the option to play again.

Example Game Session
```
Will you find the secret code?
For a hint type "hint"
Please enter your guess
Round 1
>1234
---
Well placed pieces: 1
Misplaced pieces: 1
Round 2
>hint
3 is part of the code
Round 3
>5678
---
Well placed pieces: 0
Misplaced pieces: 1
Round 4
>3481
---
Well placed pieces: 2
Misplaced pieces: 2
...
Play Again? (Y/N): N
The secret code was: 4312
```

Notes
- The secret code is guaranteed to have unique digits unless specified otherwise with the -c command-line flag.
- The game will notify you if your guess has an incorrect number of digits.
- The game will terminate early if you guess the secret code correctly before using all attempts.

### Prerequisites
- GCC (GNU Compiler Collection) or any other C compiler.

### Compilation
To compile the Mastermind game, use the following command:
```sh
gcc -o Mastermind my_mastermind.c
```

Acknowledgments
<span><i>This project was inspired by the classic Mastermind board game.</a></i></span>

<span><i>This README file provides clear instructions on how to compile, run, and play the game, as well as examples of usage and customization options. It also includes an example game session to illustrate the game's functionality.</a></i></span>