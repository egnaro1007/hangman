#include <iostream>
#include <fstream>
#include "random.h"

void openDictionary(std::fstream &file, std::string path);
std::string wordFromDictionary(std::string path = "dictionary.txt");// Default path

void play();
char inputGuessChar();
bool update(const std::string &word, std::string &guessedWord, char &guessChar, unsigned int &wrongGuessCount);
void render(std::string &guessedWord, unsigned int &wrongGuessCount);

void gameOver(bool win, std::string word);



int main() 
{
    play();
}

void play() {
    char guessChar;
    std::string word;
    std::string guessedWord = "";
    unsigned int wrongGuessCount = 0;

    word = wordFromDictionary();
    unsigned int wordLength = word.length();
    for (int i = 0; i < wordLength; i++)
    {
        guessedWord = '_' + guessedWord;
    }
    render(guessedWord, wrongGuessCount);
    

    // Game loop
    bool gameRunning = true;
    do {
        guessChar = inputGuessChar();
        update(word, guessedWord, guessChar, wrongGuessCount);
        render(guessedWord, wrongGuessCount);

        // Win
        if (guessedWord == word) {
            gameOver(true, word);
            gameRunning = false;
        }
        
        // Lose
        if (wrongGuessCount >= 7) {
            gameOver(false, word);
            gameRunning = false;
        }
    } while (gameRunning);  
}

char inputGuessChar() {
    char input;
    std::cin >> input;
    return input;
}

bool update(const std::string &word, std::string &guessedWord, char &guessChar, unsigned int &wrongGuessCount) {
    if (!('a' <= guessChar && guessChar <= 'z')) {
        if (!('A' <= guessChar && guessChar <= 'Z')) {
            ++wrongGuessCount;
            return false;
        }
        else {
            guessChar += ' ';
        }
    }
    
    unsigned int wordLength = word.length();
    bool wrong = true;
    for (unsigned int i = 0; i < wordLength; i++)
    {
        if (guessedWord[i] == '_') {
            if (word[i] == guessChar) {
                guessedWord[i] = word[i];
                wrong = false;
            }
        } 
    }
    if(wrong) {
            ++wrongGuessCount;
            return false;
        }
    return true;
}

void render(std::string &guessedWord, unsigned int &wrongGuessCount) {
    std::cout << guessedWord << "\n";
    std::cout << "Wrong: " << wrongGuessCount << "\n";
}

void gameOver(bool win, std::string word) {
    system("cls");
    if (win) {
        std::cout << "You Guessed It!\n"; 
    }
    else {
        std::cout << "Hang man !!!\n";
    } 
    std::cout << "The word is: " << word;
}



void openDictionary(std::fstream &file, std::string path) { 
    file.open(path);
    while (!file.is_open()) {
        system("cls");
        std::cout << "File not found!\n";
        std::cout << "Enter full path: ";
        std::cin >> path;
        file.open(path);
    }
}
std::string wordFromDictionary(std::string path) {
    //return "abcdefa";
    std::fstream file;
    openDictionary(file, path);


    double pos = get_random_double();
    std::string s;
    for (double i = 0; i < pos; i++)
    {
        file >> s;
    }
    
    return s;
}