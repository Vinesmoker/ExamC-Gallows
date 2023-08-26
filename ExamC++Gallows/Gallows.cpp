#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctype.h>
#include <iostream>
#include <fstream>

using namespace std;

// The file with rules
void Rules()
{
    ifstream in("Rules.txt");
    string rules;
    while (getline(in, rules))
    {
        cout << rules << endl;
    }
    cout << endl;
    in.close();
}
// Array for guessed letters
vector<bool> initializeGuessedLetters(string word)
{
    vector<bool> guessedLetters(word.length(), false);
    return guessedLetters;
}
// Displaying the current state of the game
void displayGameStatus(string word, vector<bool> guessedLetters)
{
    cout << "Word: ";
    for (int i = 0; i < word.length(); i++)
    {
        if (guessedLetters[i])
        {
            cout << word[i] << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}
// Updating guessed letters
void updateGuessedLetters(string word, vector<bool>& guessedLetters, char guess)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == guess) {
            guessedLetters[i] = true;
        }
    }
}
// Checking if a word is guessed
bool isWordGuessed(vector<bool> guessedLetters)
{
    for (bool letter : guessedLetters)
    {
        if (!letter)
        {
            return false;
        }
    }
    return true;
}
// The game
void Game()
{
    Rules();
    int numberOfPlayers;
    cout << "Enter the number of players (1-4): ";
    cin >> numberOfPlayers;
    string word;
    cout << "Host of the game, enter the word to guess: ";
    cin >> word;
    vector<bool> guessedLetters = initializeGuessedLetters(word);
    int currentPlayer = 1;
    int attempts = 10;
    char guess;
    while (attempts > 0 && !isWordGuessed(guessedLetters))
    {
        cout << "Attempts remaining: " << attempts << endl;
        displayGameStatus(word, guessedLetters);
        cout << "Player " << currentPlayer << ", enter your guess: ";
        cin >> guess;

        if (word.find(guess) != string::npos)
        {
            updateGuessedLetters(word, guessedLetters, guess);
            cout << "Correct guess!" << endl;
        }
        else
        {
            attempts--;
            cout << "Incorrect guess!" << endl;
            currentPlayer = (currentPlayer % numberOfPlayers) + 1;
            if (currentPlayer == 1) {
                string hint;
                cout << "Host of the game, enter a hint: ";
                cin >> hint;
                cout << "Hint: " << hint << endl;
            }
        }
    }
    if (isWordGuessed(guessedLetters))
    {
        cout << "Congratulations! Player " << currentPlayer << " guessed the word: " << word << "\n\n";
    }
    else
    {
        cout << "You lost! The word was: " << word << "\n\n";
    }
}
void main()
{
    Game();
    cout << "If You want to play again, press Y! To quit press any other key!" << endl;
    string answer;
    cin >> answer;
    if (answer == "y" || answer == "Y")
    {
        Game();
    }
    else
    {
        cout << "GoodBye! See You later!";
    }
}