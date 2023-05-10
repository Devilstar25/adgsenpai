#ifndef MORABARABA_H
#define MORABARABA_H

#include <vector>

using namespace std;

class Morabaraba{
public:
    Morabaraba();
    void playGame(); // Start the game
    void printBoard(); // Print the current state of the board
    void getWinner();
    void getAlgorithmMove();

private:
    vector<vector<char>> board; // Game board
    int currentPlayer; // Current player: 1 or 2
    int phase; // Game phase: 1 or 2

    void initializeBoard(); // Initialize the game board
    bool isMillFormed(int row, int col, char player); // Check if a mill is formed at a position
    bool isPlayerPiece(int row, int col, char player); // Check if a position belongs to the player
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, char player); // Check if a move is valid
    bool hasValidMoves(char player); // Check if a player has any valid moves
    void movePiece(int fromRow, int fromCol, int toRow, int toCol); // Move a piece on the board
    void removePiece(int row, int col); // Remove a piece from the board
    void makeMove(char player); // Make a move for a player
    void switchPlayer(); // Switch the current player
    bool isGameOver(); // Check if the game is over
};

#endif
