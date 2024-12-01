#include "game.h"

using namespace std;

// Constructor for the DuelGame class
// Initializes the maximum and remaining attempts and sets the game mode (single-player or multiplayer)
DuelGame::DuelGame(int maxAttempts, bool isSinglePlayer)
    : maxAttempts(maxAttempts), remainingAttempts(maxAttempts), isSinglePlayer(isSinglePlayer) {}

// Sets the secret word for the game
// Resets the current word to underscores and clears the guessed letters
void DuelGame::setSecretWord(const string &word) {
    secretWord = word;
    currentWord = string(secretWord.size(), '_');  // Initialize with underscores
    guessedLetters.clear();  // Clear the previously guessed letters
}

// Loads a random word from the word file (used in single-player mode)
// Ensures the word has at least 3 characters
bool DuelGame::loadRandomWord(const string &filename) {
    ifstream file(filename);  // Open the file
    if (!file) {
        cerr << "Error: Could not open word file: " << filename << endl;  // File not found
        return false;
    }

    // Read all valid words from the file
    vector<string> words;
    string word;
    while (file >> word) {
        if (word.size() >= 3) {  // Only include words with 3 or more characters
            words.push_back(word);
        }
    }

    if (words.empty()) {
        cerr << "Error: No valid words found in file." << endl;
        return false;
    }

    // Select a random word from the list
    srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    secretWord = words[rand() % words.size()];
    setSecretWord(secretWord);  // Initialize the game with the selected word

    return true;
}

// Displays the current game state including the guessed letters, the current word, and remaining attempts
void DuelGame::displayState() const {
    cout << "\nCurrent word: ";
    for (char c : currentWord) {
        cout << c << " ";
    }
    cout << "\nGuessed letters: ";
    for (char c : guessedLetters) {
        cout << c << " ";  // Display all guessed letters
    }
    cout << "\nRemaining attempts: " << remainingAttempts << "\n";
}

// Draws the cartoon head progressively as the player makes incorrect guesses
void DuelGame::drawCartoonHead() const {
    // ASCII art stages of the cartoon head
    static const char *stages[] = {
        "",  // Stage 0 (no incorrect guesses)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / /
)",  // Stage 1 (2 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / /
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
)",  // Stage 2 (4 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / /
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
)",  // Stage 3 (6 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / /
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
)",  // Stage 4 (8 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / /
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
  / /  / _ \|  \/  |/ _ \  \ \
 | |  | | | | \  / | | | |  | |
)",  // Stage 5 (10 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / /
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
  / /  / _ \|  \/  |/ _ \  \ \
 | |  | | | | \  / | | | |  | |
 | |  | | | | |\/| | | | |  | |
 | |  | |_| | |  | | |_| |  | |
)",  // Stage 6 (12 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / /
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
  / /  / _ \|  \/  |/ _ \  \ \
 | |  | | | | \  / | | | |  | |
 | |  | | | | |\/| | | | |  | |
 | |  | |_| | |  | | |_| |  | |
 | |  _\___/|_|  |_|\___/_  | |
  \_\|______|      |______|/_/
)"  // Stage 7 (14 lines, complete head)
    };

    // Calculate the stage index based on incorrect guesses
    int stageIndex = maxAttempts - remainingAttempts;
    if (stageIndex >= 0 && stageIndex < 8) {
        cout << stages[stageIndex] << "\n";  // Display the current stage
    }
}

// Processes a player's guess, checks if it's correct, and updates the game state
bool DuelGame::playTurn(char guess) {
    guess = tolower(guess);  // Convert the guess to lowercase
    if (guessedLetters.count(guess)) {  // Check if the letter has already been guessed
        cout << "You already guessed that letter. Try again.\n";
        return false;
    }

    guessedLetters.insert(guess);  // Add the guessed letter to the set
    bool correct = false;

    // Check if the guessed letter is in the secret word
    for (size_t i = 0; i < secretWord.size(); ++i) {
        if (tolower(secretWord[i]) == guess) {
            currentWord[i] = secretWord[i];  // Reveal the letter in the current word
            correct = true;
        }
    }

    if (!correct) {
        --remainingAttempts;  // Decrease remaining attempts for an incorrect guess
        cout << "Wrong guess!\n";
        drawCartoonHead();  // Draw the next stage of the cartoon head
    } else {
        cout << "Correct guess!\n";
    }

    return true;
}

// Checks if the player has won the game
bool DuelGame::isGameWon() const {
    return currentWord == secretWord;
}

// Checks if the player has lost the game
bool DuelGame::isGameLost() const {
    return remainingAttempts <= 0;
}

// Prints the game result (win/loss message)
void DuelGame::printResult() const {
    if (isGameWon()) {
        cout << "Congratulations! You guessed the word: " << secretWord << "\n";
    } else {
        cout << "You lost! The word was: " << secretWord << "\n";
    }
}

// Clears the console screen (platform-dependent)
void DuelGame::clearScreen() const {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux/Mac
#endif
}
