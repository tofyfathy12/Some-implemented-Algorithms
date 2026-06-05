#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 9
#define EMPTY 0

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
    for (int col = 0; col < SIZE; col++) {
        if (board[i][col] == num) return false;
    }

    // check for the column
    for (int row = 0; row < SIZE; row++) {
        if (board[row][j] == num) return false;
    }

    //check for the 3x3 square containing board[i][j]
    int smaller_size = int_sqrt(SIZE);
    if (smaller_size == -1) {
        printf("Error: SIZE IS NOT APPROPRIATE !!\n");
        exit(1);
    }

    int start_row = (i/smaller_size) * smaller_size;
    int start_col = (j/smaller_size) * smaller_size;
    for (int row = start_row; row < start_row + smaller_size; row++) {
        for (int col = start_col; col < start_col + smaller_size; col++) {
            if (board[row][col] == num) return false;
        }
    }

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

bool solve(int board[SIZE][SIZE], int *start_row, int *start_col) {
    if (!find_next_empty(board, start_row, start_col))
        return true;

    int row = *start_row, col = *start_col;
    for (int k = 1; k <= SIZE; k++) {
        if (is_valid(board, *start_row, *start_col, k)) {
            board[*start_row][*start_col] = k;

            if (solve(board, &row, &col)) return true;

            board[*start_row][*start_col] = EMPTY;
        }
    }

    return false;
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
    
        int i = 0, j = 0;
        if (solve(board, &i, &j)) {
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