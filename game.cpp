#include "game.h"

HangmanGame::HangmanGame(int maxAttempts, bool isSinglePlayer)
    : maxAttempts(maxAttempts), remainingAttempts(maxAttempts), isSinglePlayer(isSinglePlayer) {}

void HangmanGame::setSecretWord(const std::string &word) {
    secretWord = word;
    currentWord = std::string(secretWord.size(), '_');
    guessedLetters.clear();
}

bool HangmanGame::loadRandomWord(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open word file: " << filename << std::endl;
        return false;
    }

    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
        if (word.size() >= 3) {
            words.push_back(word);
        }
    }

    if (words.empty()) {
        std::cerr << "Error: No valid words found in file." << std::endl;
        return false;
    }

    srand(static_cast<unsigned>(time(0)));
    secretWord = words[rand() % words.size()];
    setSecretWord(secretWord);

    return true;
}

void HangmanGame::displayState() const {
    std::cout << "\nCurrent word: ";
    for (char c : currentWord) {
        std::cout << c << " ";
    }
    std::cout << "\nGuessed letters: ";
    for (char c : guessedLetters) {
        std::cout << c << " ";
    }
    std::cout << "\nRemaining attempts: " << remainingAttempts << "\n";
}

void HangmanGame::drawHangman() const {
    static const char *stages[] = {
        "", // Stage 0 (no incorrect guesses)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
)", // Stage 1 (2 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
)", // Stage 2 (4 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
)", // Stage 3 (6 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
)", // Stage 4 (8 lines of the head)
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
)", // Stage 5 (10 lines of the head)
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
)", // Stage 6 (12 lines of the head)
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
)" // Stage 7 (14 lines, complete head)
    };

    int stageIndex = maxAttempts - remainingAttempts;
    if (stageIndex >= 0 && stageIndex < 8) {
        std::cout << stages[stageIndex] << "\n";
    }
}

bool HangmanGame::playTurn(char guess) {
    guess = std::tolower(guess);
    if (guessedLetters.count(guess)) {
        std::cout << "You already guessed that letter. Try again.\n";
        return false;
    }

    guessedLetters.insert(guess);
    bool correct = false;

    for (size_t i = 0; i < secretWord.size(); ++i) {
        if (std::tolower(secretWord[i]) == guess) {
            currentWord[i] = secretWord[i];
            correct = true;
        }
    }

    if (!correct) {
        --remainingAttempts;
        std::cout << "Wrong guess!\n";
    } else {
        std::cout << "Correct guess!\n";
    }

    return true;
}

bool HangmanGame::isGameWon() const {
    return currentWord == secretWord;
}

bool HangmanGame::isGameLost() const {
    return remainingAttempts <= 0;
}

void HangmanGame::printResult() const {
    if (isGameWon()) {
        std::cout << "Congratulations! You guessed the word: " << secretWord << "\n";
    } else {
        std::cout << "You lost! The word was: " << secretWord << "\n";
    }
}

void HangmanGame::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
