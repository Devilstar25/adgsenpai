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


//I COULDNT GET THE CPP FILE TO UPLOAD SO IM PUTTING THE MAIN CPP HERE 

#include "Morabaraba.h"
#include <iostream>
#include <string>

using namespace std;

Morabaraba::Morabaraba() {
 initializeBoard();
 currentPlayer = 1; // Start with player 1
 phase = 1; // Start with phase 1
}
void Morabaraba::initializeBoard() {
    // Initialize the game board
    board = {
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
    };
}
void Morabaraba::printBoard() {
    // Print the current state of the board
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout <<endl;
    }
}
bool Morabaraba::isMillFormed(int row, int col, char player) {
    // Check if a mill is formed at a position

    // Check horizontal mills
    if ((board[row][(col + 1) % 8] == player && board[row][(col + 2) % 8] == player) ||
        (board[row][(col + 6) % 8] == player && board[row][(col + 7) % 8] == player)) {
        return true;
    }

    // Check vertical mills
    if ((board[(row + 1) % 3][col] == player && board[(row + 2) % 3][col] == player) ||
        (board[(row + 2) % 3][col] == player && board[(row + 4) % 3][col] == player)) {
        return true;
    }

    // Check diagonal mills
    if (col % 2 == 0) {
        if (board[(row + 1) % 3][(col + 1) % 8] == player && board[(row + 2) % 3][(col + 2) % 8] == player) {
            return true;
        }
        if (board[(row + 1) % 3][(col + 7) % 8] == player && board[(row + 2) % 3][(col + 6) % 8] == player) {
            return true;
        }
    } else {
        if (board[(row + 1) % 3][(col + 1) % 8] == player && board[(row + 2) % 3][(col + 6) % 8] == player) {
            return true;
        }
        if (board[(row + 1) % 3][(col + 7) % 8] == player && board[(row + 2) % 3][(col + 2) % 8] == player) {
            return true;
        }
    }

    return false;
}
bool Morabaraba::isPlayerPiece(int row, int col, char player) {
    // Check if a position belongs to the player

    // Check if the position is valid and contains the player's piece
    if (row < 0 || row >= 3 || col < 0 || col >= 8 || board[row][col] != player) {
        return false;
    }

    return true;
}

bool Morabaraba::isValidMove(int fromRow, int fromCol, int toRow, int toCol, char player) {
    // Check if a move is valid

    // Check if the source position contains the player's piece
    if (!isPlayerPiece(fromRow, fromCol, player)) {
        return false;
    }

    // Check if the destination position is empty
    if (board[toRow][toCol] != ' ') {
        return false;
    }

    // Check if the move is within the valid range
    if (fromRow < 0 || fromRow >= 3 || fromCol < 0 || fromCol >= 8 ||
        toRow < 0 || toRow >= 3 || toCol < 0 || toCol >= 8) {
        return false;
    }

    // Check if the move is within the allowed range
    if (phase == 1) {
        // Phase 1: Any empty adjacent position
        if (abs(fromRow - toRow) > 1 || abs(fromCol - toCol) > 1) {
            return false;
        }
    } else {
        // Phase 2: Any position connected by a line
        if (!((fromRow == toRow && abs(fromCol - toCol) == 4) ||
              (fromCol == toCol && abs(fromRow - toRow) == 1) ||
              ((fromRow == 0 || fromRow == 2) && (toRow == 0 || toRow == 2) && abs(fromCol - toCol) == 3))) {
            return false;
        }
    }

    return true;
}
bool Morabaraba::hasValidMoves(char player) {
    // Check if a player has any valid moves

    // Iterate through each position on the board
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 8; col++) {
            // Check if the position contains the player's piece
            if (isPlayerPiece(row, col, player)) {
                // Check all possible destination positions
                for (int toRow = 0; toRow < 3; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        // Check if the move is valid
                        if (isValidMove(row, col, toRow, toCol, player)) {
                            return true; // Found a valid move
                        }
                    }
                }
            }
        }
    }

    return false; // No valid moves found
}
void Morabaraba::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    // Move a piece on the board

    // Check if the move is valid
    if (!isValidMove(fromRow, fromCol, toRow, toCol, currentPlayer)) {
        return; // Invalid move, do nothing
    }

    // Perform the move by updating the board
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = ' ';

    // Check if the move resulted in a mill for the current player
    if (isMillFormed(toRow, toCol, currentPlayer)) {
        // Player formed a mill, additional action may be required
        // ...
        // Implement logic for handling additional actions after forming a mill
        // ...
    } else {
        switchPlayer(); // Switch to the next player
    }
}

void Morabaraba::removePiece(int row, int col) {
    // Remove a piece from the board

    // Check if the position is valid and contains a player's piece
    if (row < 0 || row >= 3 || col < 0 || col >= 8 || board[row][col] == ' ') {
        return; // Invalid position or empty space, nothing to remove
    }

    char player = board[row][col]; // Player owning the piece
    board[row][col] = ' '; // Remove the piece from the board

    // Check if the piece formed a mill and remove opponent's piece if necessary
    if (isMillFormed(row, col, player)) {
        // Iterate through each position on the board
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 8; c++) {
                // Check if the position contains the opponent's piece
                if (isPlayerPiece(r, c, (player == '1' ? '2' : '1')) && !isMillFormed(r, c, (player == '1' ? '2' : '1'))) {
                    // Remove the opponent's piece
                    board[r][c] = ' ';
                    return; // Only remove one opponent's piece per mill
                }
            }
        }
    }
}
void Morabaraba::makeMove() {
    // Make a move in the game

    // Check if it's the player's turn
    if (currentPlayer != '1' && currentPlayer != '2') {
        return; // Invalid player, do nothing
    }

    // Check if the move is valid
    if (!isValidMove(fromRow, fromCol, toRow, toCol, currentPlayer)) {
        return; // Invalid move, do nothing
    }

    // Perform the move by updating the board
    board[toRow][toCol] = currentPlayer;
    board[fromRow][fromCol] = ' ';

    // Check if the move resulted in a mill for the current player
    if (isMillFormed(toRow, toCol, currentPlayer)) {
        // Player formed a mill, additional action may be required
        // ...
        // Implement logic for handling additional actions after forming a mill
        // ...
    } else {
        switchPlayer(); // Switch to the next player
    }
}
void Morabaraba::switchPlayer() {
    // Switch to the next player's turn

    // Check the current player and switch to the other player
    if (currentPlayer == '1') {
        currentPlayer = '2';
    } else if (currentPlayer == '2') {
        currentPlayer = '1';
    }
}
bool Morabaraba::isGameOver() {
    // Check if the game is over

    // Check if any player has less than 3 pieces remaining
    int player1Pieces = countPlayerPieces('1');
    int player2Pieces = countPlayerPieces('2');

    if (player1Pieces < 3 || player2Pieces < 3) {
        return true; // Game over, one player has less than 3 pieces remaining
    }

    // Check if any player has no valid moves
    bool player1HasMoves = hasValidMoves('1');
    bool player2HasMoves = hasValidMoves('2');

    if (!player1HasMoves || !player2HasMoves) {
        return true; // Game over, one player has no valid moves
    }

    return false; // Game is not over
}
int main()
{
    Morabaraba game;

    // Game loop
    while (!game.isGameOver()) {
        // Display the current state of the board
        game.printBoard();

        // Get the current player's move (algorithm vs algorithm)
        int fromRow, fromCol, toRow, toCol;
        // Algorithm 1 makes the move
        game.getAlgorithmMove(fromRow, fromCol, toRow, toCol, '1');
        game.makeMove(fromRow, fromCol, toRow, toCol);

        // Algorithm 2 makes the move
        game.getAlgorithmMove(fromRow, fromCol, toRow, toCol, '2');
        game.makeMove(fromRow, fromCol, toRow, toCol);
    }

    // Display the final state of the board
    game.printBoard();

    // Determine the winner
    char winner = game.getWinner();
    if (winner == '1') {
        std::cout << "Player 1 wins!" << std::endl;
    } else if (winner == '2') {
        std::cout << "Player 2 wins!" << std::endl;
    } else {
        std::cout << "It's a draw!" << std::endl;
    }

    return 0;
}





