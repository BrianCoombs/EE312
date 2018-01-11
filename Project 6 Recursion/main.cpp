#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MazeParams.h"
#include "Recursion.h"


int maze[MATRIX_SIZE][MATRIX_SIZE];
#define WALL (1 << 30)
#define MARK (1 << 29)
#define MASK (((-1) ^ WALL) ^ MARK)
int start_col; // the starting column for the maze;

void printMaze(void) {
    unsigned r, c;
    for (r = 0; r < MATRIX_SIZE; r += 1) {
        for (c = 0; c < MATRIX_SIZE; c += 1) {
            switch (maze[r][c] ) {
                case 0:
                    putchar(' ');
                    break;
                case 1:
                    putchar('#');
                    break;
                case 2: // bread crumb
                    putchar('o');
                    break;
                default: // error!
                    putchar('@');
                    break;
            }
        }
        putchar('\n');
    }
}

void printCodedMaze(void) {
    unsigned r, c;
    for (r = 0; r < MATRIX_SIZE; r += 1) {
        for (c = 0; c < MATRIX_SIZE; c += 1) {
            switch(maze[r][c] & WALL) {
                case WALL:
                    putchar('#');
                    break;
                case 0:
                    putchar(' ');
                    break;
            }
        }
        putchar('\n');
    }
}

enum Directions {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void interpretDir(int* prow, int* pcol, int dir) {
    switch (dir) {
        case UP: *prow = *prow - 1; break;
        case DOWN: *prow = *prow + 1; break;
        case LEFT: *pcol = *pcol - 1; break;
        case RIGHT: *pcol = *pcol + 1; break;
    }
}

void clearWall(int row, int col, int dir) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;
    interpretDir(&r, &c, dir);
    maze[r][c] &= ~WALL;
}

void markCell(int row, int col) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;

    maze[r][c] |= MARK;
}

int isMarked(int row, int col) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;

    return (maze[r][c] & MARK);
}


/*
 * return an integer that uniquely identifies each cell
 */
int cellID(int row, int col) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;
    return r * MATRIX_SIZE + c;
}

/*
 * reverse the cellID to compute the row and col numbers
 */
void findCell(int cell, int* prow, int* pcol) {
    int r = cell / MATRIX_SIZE;
    int c = cell % MATRIX_SIZE;
    *prow = r / 2;
    *pcol = c / 2;
}

/*
 * store some annotation information in a cell
 * (the annotation must be an int less than 25 bits (i.e., smaller than 32 million)
 */
void annotateCell(int row, int col, int annotation) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;

    maze[r][c] &= ~MASK;
    maze[r][c] |= annotation;
}

int annotation(int row, int col) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;

    return maze[r][c] & MASK;
}

void clearCellMark(int row, int col) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;

    maze[r][c] &= ~MARK;
}

void clearCell(int row, int col) {
    int r = row * 2 + 1;
    int c = col * 2 + 1;

    maze[r][c] = 0;
}

void makeAllWalls(void) {
    unsigned r, c;
    unsigned row, col;
    for (r = 0; r < MATRIX_SIZE; r += 1) {
        for (c = 0; c < MATRIX_SIZE; c += 1) {
            maze[r][c] = WALL;
        }
    }
    for (row = 0; row < MAZE_SIZE; row += 1) {
        for (col = 0; col < MAZE_SIZE; col += 1) {
            clearCell(row, col);
        }
    }
}

/*
 * this function makes a random maze with exactly one path between
 * any two points in the maze
 *
 * If you're curious about the algorithm, come talk to me.  It's not very
 * complicated (although the code might be confusing)
 */
void makeMaze() {
    int num_visited = 1;
    int first;
    int finish_col;
    makeAllWalls();
    markCell(0, 0);  // mark the first cell as visited

    /* add the first cell (row 0, col 0) to the linked list of visited cells */
    first = cellID(0, 0);
    annotateCell(0, 0, 0);

    while(num_visited < MAZE_SIZE * MAZE_SIZE) {
        int visit = rand() % num_visited;
        int cell = first;
        int row, col;
        int d;
        int nrow, ncol;

        findCell(cell, &row, &col);
        while (visit > 0) {
            cell = annotation(row, col);
            findCell(cell, &row, &col);
            visit -= 1;
        }
        d = rand() % 4;
        nrow = row; // row of neighbor cell
        ncol = col; // col of neighbor cell
        interpretDir(&nrow, &ncol, d);
        if (nrow >= 0 && nrow < MAZE_SIZE
            && ncol >= 0 && ncol < MAZE_SIZE
            && !isMarked(nrow, ncol)) {
            clearWall(row, col, d);
            num_visited += 1;
            markCell(nrow, ncol);
            annotateCell(nrow, ncol, first);
            first = cellID(nrow, ncol);
        }
    }

    start_col = rand() % MAZE_SIZE;
    start_col = 2 * start_col + 1;
    maze[0][start_col] &= ~WALL;
    finish_col = rand() % MAZE_SIZE;
    maze[MATRIX_SIZE - 1][2 * finish_col + 1] &= ~WALL;
}

void makeVoidMaze() {
    int num_visited = 1;
    int first;
    makeAllWalls();
    markCell(0, 0);  // mark the first cell as visited

    /* add the first cell (row 0, col 0) to the linked list of visited cells */
    first = cellID(0, 0);
    annotateCell(0, 0, 0);

    while(num_visited < MAZE_SIZE * MAZE_SIZE) {
        int visit = rand() % num_visited;
        int cell = first;
        int row, col;
        int d;
        int nrow, ncol;

        findCell(cell, &row, &col);
        while (visit > 0) {
            cell = annotation(row, col);
            findCell(cell, &row, &col);
            visit -= 1;
        }
        d = rand() % 4;
        nrow = row; // row of neighbor cell
        ncol = col; // col of neighbor cell
        interpretDir(&nrow, &ncol, d);
        if (nrow >= 0 && nrow < MAZE_SIZE
            && ncol >= 0 && ncol < MAZE_SIZE
            && !isMarked(nrow, ncol)) {
            clearWall(row, col, d);
            num_visited += 1;
            markCell(nrow, ncol);
            annotateCell(nrow, ncol, first);
            first = cellID(nrow, ncol);
        }
    }

    start_col = rand() % MAZE_SIZE;
    start_col = 2 * start_col + 1;
    maze[0][start_col] &= ~WALL;
}

/*
 * recode the maze so that all walls are exactly 1 and all
 * other cells are exactly zero
 */
void recodeMaze(void) {
    int r, c;
    for (r = 0; r < MATRIX_SIZE; r += 1) {
        for (c = 0; c < MATRIX_SIZE; c += 1) {
            maze[r][c] = ((maze[r][c] & WALL) == WALL);
        }
    }
}


int main(void) {
    srand(time(NULL));
    int arr[10];
    /* test min */
    printf("Testing minRec1\n");
    for (int i = 0; i < 3; i++) {
        printf("The random array of numbers 0-20 is:");
        for (int i = 0; i < 10; i++) {
            arr[i] = rand() % 21;
            printf(" %d,");
        }
        printf("\nthe smallest of the array is: %d\n", minRec1(arr, 10));
    }

    printf("\nTesting minRec2\n");
    for (int i = 0; i < 3; i++) {
        printf("The random array of numbers 0-20 is:");
        for (int i = 0; i < 10; i++) {
            arr[i] = rand() % 21;
            printf(" %d");
            if (i != 9) {
                printf(",");
            }
        }
        printf("\nthe smallest of the array is: %d\n", minRec2(arr, 10));
    }


    /* test sqrt */
    printf("\nTesting sqrtRec\n");
    double rndV;
    printf("the sqrt of 1 is %.16g\n", sqrtRec(1.0, 0, 1.0));
    printf("the sqrt of 0 is %.16g\n", sqrtRec(0, 0, 0));
    for (int i = 0; i < 3; i++) {
        rndV = rand()%101;
        printf("the sqrt of %.16g is %.16g\n", rndV, sqrtRec(rndV, 0, rndV));
    }

    /* test strCompare */
    printf("\nTesting strCompare\n");
    char* s1; char* s2;
    s1 = "apple"; s2 = "apricot";
    if (strCompare(s1, s2) < 0) {
        printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
    }

    s1 = "apples"; s2 = "apples and bananas";
    if (strCompare(s1, s2) < 0) {
        printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
    }

    s1 = "Apple"; s2 = "apple";
    if (strCompare(s1, s2) < 0) {
        printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
    }

    s1 = "baby boy"; s2 = "banana";
    if (strCompare(s1, s2) < 0) {
        printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
    }

    s1 = "a rather silly string"; s2 = "a rather silly string";
    if (strCompare(s1, s2) == 0) {
        printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
    }

    s1 = ""; s2 = "";
    if (strCompare(s1, s2) == 0) {
        printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
    }

    s1 = "12345"; s2 = "12345";
    if (strCompare(s1, s2) == 0) {
        printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
    }

    s1 = "Numbers: 12345"; s2 = "12345";
    if (strCompare(s1, s2) > 0) {
        printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
    }

    s1 = "Texas"; s2 = "California";
    if (strCompare(s1, s2) > 0) {
        printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
    }

    s1 = "apples and bananas"; s2 = "apples";
    if (strCompare(s1, s2) > 0) {
        printf("\"%s\" is greater than \"%s\", very good\n\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be greater than \"%s\"\n\n", s1, s2);
    }

    /* test strCompare2 */
    printf("Testing strCompare2\n");
    s1 = "apple"; s2 = "Apricot";
    if (strCompare2(s1, s2) < 0) {
        printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
    }

    s1 = "Batman!"; s2 = "bat man";
    if (strCompare2(s1, s2) == 0) {
        printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
    }

    s1 = "OMG, WTF?"; s2 = "oh my goodness, what the heck?";
    if (strCompare2(s1, s2) > 0) {
        printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
    }

    s1 = ""; s2 = "!!!@!@!@#!@";
    if (strCompare2(s1, s2) == 0) {
        printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
    }

    s1 = "ap45325ples"; s2 = "apples[]'/'and bananas";
    if (strCompare2(s1, s2) < 0) {
        printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
    }

    s1 = "a!ppl   es an981651d bana[]'][nas"; s2 = "apples";
    if (strCompare2(s1, s2) > 0) {
        printf("\"%s\" is greater than \"%s\", very good\n\n", s1, s2);
    } else {
        printf("oops, \"%s\" should be greater than \"%s\"\n\n", s1, s2);
    }

    /* test maze */
    makeMaze();
    recodeMaze();
    printf("recursive solution to the maze with an exit\n");
    solveMazeRec(0, start_col);
    printMaze();
    printf("\n");
    makeVoidMaze();
    recodeMaze();
    printf("recursive solution to the maze without an exit\n");
    solveMazeRec(0, start_col);
    printMaze();
    printf("\n");


    /* test Martian */
    printf("Test of random change with nick=5 and dodek=12\n");
    int a, b,c;
    Martian changed;
    for(int i =0; i<3; i++) {
        a = rand() % 51;
        changed = change(a);
        printf("change given is %d and the result is: %dd %dn %dp\n", a, changed.dodeks, changed.nicks,
               changed.pennies);
    }



    printf("\nTest of random change, nick value, and dodek value\n");
    for(int i =0; i<3; i++) {
        a = rand() % 51;
        b = rand() % 11;
        while (b < 2) {
            b = rand() % 11;
        }
        c = b +(rand()%11)+1;
        changed = change(a, b, c);
        printf("change given is %d, nick=%d, dodek=%d and the result is: %dd %dn %dp\n", a, b, c, changed.dodeks,
               changed.nicks, changed.pennies);
    }
}
