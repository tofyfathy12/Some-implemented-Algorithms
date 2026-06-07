#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 9
#define EMPTY 0

bool rows_filled[SIZE][SIZE];
bool cols_filled[SIZE][SIZE];
bool subboxes_filled[SIZE][SIZE];

void print_board(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) printf("_ ");
            else printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int int_sqrt(int num) {
    for (int i = 0; i <= num/2; i++) {
        if (i*i == num) return i;
    }

    return -1;
}

bool is_valid(int board[SIZE][SIZE], int i, int j, int num) {
    // check for the row
    if (rows_filled[i][num - 1]) return false;

    // check for the column
    if (cols_filled[j][num - 1]) return false;

    //check for the 3x3 square containing board[i][j]
    int smaller_size = int_sqrt(SIZE);
    if (smaller_size == -1) {
        printf("Error: SIZE IS NOT APPROPRIATE !!\n");
        exit(1);
    }

    int index = (i / smaller_size) * smaller_size + (j / smaller_size);
    if (subboxes_filled[index][num - 1]) return false;

    return true;
}

bool find_next_empty(int board[SIZE][SIZE], int *row, int *col) {
    for (int i = *row; i < SIZE; i++) {
        for (int j = *col; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                *row = i;
                *col = j;
                return true;
            }
        }
        *col = 0;
    }
    return false;
}

void fill(int i, int j, int num, bool fill) {
    rows_filled[i][num - 1] = fill;
    cols_filled[j][num - 1] = fill;
    
    int index = (i/3)*3 + (j/3);
    subboxes_filled[index][num - 1] = fill;
}

bool solve_helper(int board[SIZE][SIZE], int *start_row, int *start_col) {
    if (!find_next_empty(board, start_row, start_col))
        return true;

    int row = *start_row, col = *start_col;
    for (int k = 1; k <= SIZE; k++) {
        if (is_valid(board, *start_row, *start_col, k)) {
            board[*start_row][*start_col] = k;
            fill(*start_row, *start_col, k, true);

            if (solve_helper(board, &row, &col)) return true;

            board[*start_row][*start_col] = EMPTY;
            fill(*start_row, *start_col, k, false);
        }
    }

    return false;
}

bool solve(int board[SIZE][SIZE]) {
    memset(rows_filled, false, sizeof(rows_filled));
    memset(cols_filled, false, sizeof(cols_filled));
    memset(subboxes_filled, false, sizeof(subboxes_filled));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != EMPTY)
                fill(i, j, board[i][j], true);
        }
    }

    int i = 0, j = 0;
    return solve_helper(board, &i, &j);
}

int main(int argc, char *arv[]) {
    int board[SIZE][SIZE];

    // read from file
    FILE *f = fopen("sudoku.txt", "r");
    if (f == NULL) {
        printf("Failed to open file !!\n");
        return 1;
    }

    int board_num;
    while (fscanf(f, "%d", &board_num) == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                char input[20];
                if (fscanf(f, "%19s", input) != 1) {
                    printf("Invalid input file !!\n");
                    fclose(f);
                    return 1;
                }
    
                if (input[0] == '_') board[i][j] = EMPTY;
                else board[i][j] = atoi(input);
            }
        }
        printf("\n============================== BOARD %d =============================\n", board_num);
        printf("Before solving:\n");
        print_board(board);
    
        if (solve(board)) {
            printf("After solving:\n");
            print_board(board);
        }
        else {
            printf("No solution found !!\n");
        }
    }
    fclose(f);
    return 0;
}