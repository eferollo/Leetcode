#include <stdbool.h>
#include <stdlib.h>

/**
 * Problem:
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to 
 * be validated according to the following rules:
 *   Each row must contain the digits 1-9 without repetition.
 *   Each column must contain the digits 1-9 without repetition.
 *   Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 
 *   1-9 without repetition
 *
 * Solution:
 * We track the presence of digits (1–9) using three 2D arrays:
 * - row[i][d]  -> digit d appears in row i
 * - col[j][d]  -> digit d appears in column j
 * - box[k][d]  -> digit d appears in 3x3 sub-box k
 *
 * For each cell:
 * - If it's not '.', convert the char to a number (1–9)
 * - Compute the sub-box index: (i / 3) * 3 + (j / 3)
 * - Check if the number already appeared in the same row, column, or box
 *   -> if yes, the board is invalid
 * - Otherwise, mark the number as seen in all three structures
 *
 * Time Complexity:
 * - O(n^2), where n = boardSize (for standard Sudoku, n = 9)
 * - We scan each cell exactly once and perform O(1) checks
 *
 * Space Complexity:
 * - O(n^2)
 *   We allocate three n x n matrices (row, col, box)
 *   -> total auxiliary space is 3 * n^2 = O(n^2)
 *
 * Note:
 * For standard Sudoku (9x9), both time and space are effectively O(1)
 * since n is fixed.
 */

bool isValidSudoku(char **board, int boardSize, int *boardColSize)
{
    int row[9][9] = {0};
    int col[9][9] = {0};
    int box[9][9] = {0};

    int i, j, num, k;

    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] != '.') {
                num = board[i][j] - '0';
                k = (i / 3) * 3 + (j / 3);
                if (row[i][num - 1] || col[j][num - 1] ||
                    box[k][num - 1]) {
                    return false;
                }
                row[i][num - 1] = col[j][num - 1] = box[k][num - 1] = 1;
            }
        }
    }

    return true;
}

int main(void)
{
    char *board[] = {"53..7....",
                     "6..195...",
                     ".98....6.",
                     "8...6...3",
                     "4..8.3..1",
                     "7...2...6",
                     ".6....28.",
                     "...419..5",
                     "....8..79"};

    int colsize = 9;
    int r = isValidSudoku(board, colsize, &colsize);
    return EXIT_SUCCESS;
}
