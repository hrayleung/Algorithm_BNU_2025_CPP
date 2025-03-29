#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include <algorithm>
using namespace std;

// Defining constants for the board size and possible knight moves
constexpr int BOARD_SIZE = 8;
constexpr int dx[] = {-1, 1, -2, 2, -2, 2, -1, 1};
constexpr int dy[] = {2, 2, 1, 1, -1, -1, -2, -2};

// Initializing the chessboard with zeros
int board[BOARD_SIZE][BOARD_SIZE];

// Function declarations
bool isValidPosition(int row, int col);
int getAccessibility(int row, int col);
bool solve(int row, int col, int step);
void printBoard();

// Check if a given position is within the bounds of the board
bool isValidPosition(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

// Count accessible and unvisited positions from a given position
int getAccessibility(int row, int col) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        if (isValidPosition(newRow, newCol) && board[newRow][newCol] == 0) {
            count++;
        }
    }
    return count;
}

// Print the current state of the chessboard
void printBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << setw(3) << board[i][j];
        }
        cout << endl;
    }
}

// Recursive function to solve the Knight's Tour problem using Warnsdorff's rule
bool solve(int row, int col, int step) {
    if (step > BOARD_SIZE * BOARD_SIZE) {
        return true; // Solution found
    }

    vector<pair<int, int>> possible_moves;

    // Calculate possible moves and their accessibility
    for (int i = 0; i < 8; ++i) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];

        if (isValidPosition(newRow, newCol) && board[newRow][newCol] == 0) {
            int accessibility = getAccessibility(newRow, newCol);
            possible_moves.push_back({accessibility, i});
        }
    }

    // Sort moves by ascending accessibility (Warnsdorff's rule)
    sort(possible_moves.begin(), possible_moves.end());

    // Try each move in order of accessibility
    for (const auto& move_pair : possible_moves) {
        int moveIndex = move_pair.second;
        int newRow = row + dx[moveIndex];
        int newCol = col + dy[moveIndex];

        board[newRow][newCol] = step; // Place knight
        if (solve(newRow, newCol, step + 1)) {
            return true; // Solution continues
        }

        board[newRow][newCol] = 0; // Backtrack
    }

    return false;
}

int main() {
    int startRow, startCol;

    cin >> startRow >> startCol;

    // Check and handle invalid starting position
    if (!isValidPosition(startRow, startCol)) {
         cerr << "Error: Starting position (" << startRow << ", " << startCol
              << ") is outside the " << BOARD_SIZE << "x" << BOARD_SIZE << " board." << endl;
         return 1;
    }

    board[startRow][startCol] = 1; // Place knight at starting position

    // Attempt to solve from the starting position
    if (solve(startRow, startCol, 2)) {
        printBoard(); // Print the solution board
    } else {
        cout << "No solution exists" << endl; // No solution found
    }

    return 0;
}