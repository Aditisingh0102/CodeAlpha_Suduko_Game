                                                 // SUDUKO SOLVER 
#include <iostream>
using namespace std;

#define N 9 // Size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Check if placing a number in a cell is safe (row, column, and 3x3 grid)
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is in the current row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check if the number is in the current column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check the 3x3 sub-grid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we've reached the last cell, the puzzle is solved
    if (row == N - 1 && col == N)
        return true;

    // Move to the next row if we've reached the end of the current row
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip the cells that are already filled
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    // Try placing numbers 1 to 9 in the current cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // Place the number

            // Recursively solve the rest of the grid
            if (solveSudoku(grid, row, col + 1))
                return true;
        }

        // Undo the assignment (backtrack)
        grid[row][col] = 0;
    }

    // Trigger backtracking
    return false;
}

int main() {
    // Initial Sudoku grid with some pre-filled values
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    // Solve the Sudoku puzzle and print the result
    if (solveSudoku(grid, 0, 0)) {
        cout << "Solved Sudoku Grid:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}