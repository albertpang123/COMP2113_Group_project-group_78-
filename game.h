#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

// Class to handle game logic
class DuelGame {
private:
    string secretWord;           // Word to guess
    string currentWord;          // Current state of the word with guessed letters
    set<char> guessedLetters;    // Set to track guessed letters
    int maxAttempts;             // Maximum incorrect guesses allowed
    int remainingAttempts;       // Remaining incorrect guesses allowed
    bool isSinglePlayer;         // Mode: Single-player or Multiplayer

    void drawCartoonHead() const;     // Display ASCII art for incorrect guesses

public:
    DuelGame(int maxAttempts, bool isSinglePlayer);
    void setSecretWord(const string &word); // Set the secret word
    bool loadRandomWord(const string &filename); // Load word from file
    bool playTurn(char guess);                    // Process a player's guess
    bool isGameWon() const;                       // Check if the word is guessed
    bool isGameLost() const;                      // Check if attempts are exhausted
    void printResult() const;                     // Print game result
    void displayState() const;                    // Display the game state (moved to public)
    void clearScreen() const;                     // Clear the console screen (moved to public)
};

#endif
