#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void displayGrid(vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j > 0 && j % 3 == 0) {
                cout << "| ";
            }
            cout << board[i][j] << " ";
        }
        cout << endl;
        if (i < 8 && (i + 1) % 3 == 0) {
            cout << "---------------------" << endl;
        }
    }
}

bool canWePlace(vector<vector<char>> &board, int row, int col, char num) {
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == num) return false;
    }
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) return false;
    }
    int r = (row / 3) * 3;
    int c = (col / 3) * 3;
    for (int i = r; i < (r + 3); i++) {
        for (int j = c; j < (c + 3); j++) {
            if (board[i][j] == num) return false;
        }
    }
    return true;
}

bool sudoku(vector<vector<char>> &board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                for (char num = '1'; num <= '9'; num++) {
                    if (canWePlace(board, row, col, num)) {
                        board[row][col] = num;
                        if (sudoku(board)) return true;
                        board[row][col] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void generateSudoku(vector<vector<char>> &board, int clues) {
    if (!sudoku(board)) {
        cout << "Error generating Sudoku puzzle." << endl;
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    int removeSomeNumbers = 81 - clues;

    while (removeSomeNumbers > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (board[row][col] != '.') {
            board[row][col] = '.';
            removeSomeNumbers--;
        }
    }
}

int main() {
    vector<vector<char>> board(9, vector<char>(9, '.'));

    int clues = 25;
    generateSudoku(board, clues);

    cout << "Sudoku Puzzle" << endl;
    cout << "Fill the empty cells and clear it by entering '.'" << endl;

    while (true) {
        displayGrid(board);

        int row, col;
        char num;

        cout << "Enter row (1-9), column (1-9), and number (1-9): ";
        cin >> row >> col >> num;

        if (row < 1 || row > 9 || col < 1 || col > 9 || num - '0' < 0 || num - '0' > 9) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        if (board[row - 1][col - 1] == '.') {
            if(canWePlace(board, row-1, col-1, num))
                board[row - 1][col - 1] = num;
            else{
                cout<<"Wrong Input. Please check again!"<<endl;
            }
        } else {
            cout << "This cell is already filled. Choose a different one." << endl;
        }

        if (canWePlace(board, row, col, num)) {
            continue;
        } else {
            cout << "Keep going..." << endl;
        }
    }


    return 0;
}
