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

// Class to handle game logic
class HangmanGame {
private:
    std::string secretWord;           // Word to guess
    std::string currentWord;          // Current state of the word with guessed letters
    std::set<char> guessedLetters;    // Set to track guessed letters
    int maxAttempts;                  // Maximum incorrect guesses allowed
    int remainingAttempts;            // Remaining incorrect guesses allowed
    bool isSinglePlayer;              // Mode: Single-player or Multiplayer

    void displayState() const;        // Display the game state
    void drawHangman() const;         // Display ASCII art for incorrect guesses
    void clearScreen() const;         // Clear the console screen

public:
    HangmanGame(int maxAttempts, bool isSinglePlayer);
    void setSecretWord(const std::string &word); // Set the secret word
    bool loadRandomWord(const std::string &filename); // Load word from file
    bool playTurn(char guess);                    // Process a player's guess
    bool isGameWon() const;                       // Check if the word is guessed
    bool isGameLost() const;                      // Check if attempts are exhausted
    void printResult() const;                     // Print game result
};

#endif
