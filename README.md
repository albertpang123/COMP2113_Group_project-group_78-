Video link: https://youtu.be/xhJySPieblQ

1. Team Members:
- Pang Wang Pok (UID: 3036181795)



2. Title:
- Duel of the Words



3. Description:

- Duel of the Words is a fun and engaging word-guessing game base on the traditional Hangman game, where players try to guess a hidden word by guessing one letter at a time. The game can be played in single-player mode, where the word is randomly selected from a file, or in multiplayer mode, where one player sets the word, and the other tries to guess it.

- The game features a progressive cartoon head drawing that appears as you make incorrect guesses. You have a limited number of attempts to guess the word before the cartoon head is fully drawn—at which point the game is lost!


4. Rules:

    (1) The game starts with a hidden word represented by underscores (_), where the number of underscores matches the length of the word.
Players guess one letter at a time.

    (2) If the guessed letter is in the word, it is revealed in its correct positions.

    (3) If the guessed letter is not in the word, you lose an attempt, and part of the cartoon head is drawn.

    (4) The player wins by guessing all the letters in the word before running out of attempts.

    (5) The player loses if all attempts are used up before the word is fully guessed, and the cartoon head is fully drawn.

    (6) In single-player mode:
    - The word is chosen randomly from a file (word.txt).

    (7) In multiplayer mode:
    - Player 1 enters the secret word, and Player 2 tries to guess it.

5. Features:

    (1) Game Modes:

    - Single-Player Mode: The computer selects a random word for you to guess.
    - Multiplayer Mode: One player sets the word, and the other guesses.

    (2)Progressive Cartoon Drawing:

    - As incorrect guesses are made, a cartoon head is progressively drawn in seven stages. The game is over when the full cartoon head is complete.

    (3)Hints About the Game State:

    - The current state of the word is displayed with revealed letters and underscores for unguessed letters.
    - Already guessed letters are displayed to help players avoid repeating guesses.
    - Remaining attempts are displayed after each guess.

    (4)Winning and Losing Messages:

    - A congratulatory message is shown if you win.
    - A losing message reveals the word if you lose.


6. Compilation and Execution Instructions

- Ensure the following files are in the same directory:

    - game.h: Header file defining the DuelGame class.
    - game.cpp: Implementation of the DuelGame class.
    - main.cpp: Entry point of the game.
    - word.txt: A text file containing a list of words (used for single-player mode). Each word should be on a separate line.
    - Makefile: A file for automating the build process.


- Open the terminal and navigate to the directory containing the game files.
- Use the provided Makefile to compile the program, this will generate an executable named duel.
- Or use the following command: g++ -std=c++11 -o duel main.cpp game.cpp
- Run the game by executing the compiled program: ./duel
- Follow the on-screen menu:
    - Choose 1 for Single-Player mode.
    - Choose 2 for Multiplayer mode.
    - Choose 3 to quit the game.
  - If you are playing in Single-Player mode, ensure the word.txt file is present and contains valid words.
