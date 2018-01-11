/* Project2.cpp
 * Brian Coombs
 * EE312, Spring 2017
 * Project 2, Matrix Multiplication
 */

#include <stdio.h>
#include <stdint.h>
#include "MatrixMultiply.h"
#include <stdlib.h>

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {

    int n = 0;
    int curRow = 0;
    int curCol = 0;
    while(curRow < a_rows){
        curCol=0;
        while(curCol < b_cols){
            n = 0;
            c[curRow*b_cols + curCol] = 0;
            while(n < a_cols){
                c[curRow*b_cols+curCol] += a[curRow*a_cols+n] * b[n*b_cols + curCol];
                n++;
            }
            curCol++;
        }
        curRow++;
    }
}

// https://en.wikipedia.org/wiki/Row-_and_column-major_order
double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
    int n = 0;
    int curRow = 0;
    int curCol = 0;
    double** ret;
    ret = (double **)malloc(sizeof(double *) * a_rows);
    for(int i = 0; i< a_rows; i++){
        ret[i] = (double*)malloc(b_cols*sizeof(double));
    }
    while(curRow < a_rows) {
        curCol = 0;
        while (curCol < b_cols) {
            n = 0;
            ret[curRow][curCol] = 0;
            while (n < a_cols) {
                ret[curRow][curCol] += a[curRow][n] * b[n][curCol];
                n++;
            }
            curCol++;
        }
        curRow++;
    }

    return ret;
}

// https://en.wikipedia.org/wiki/Transpose

double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
    int curRow = 0;
    int curCol = 0;
    double** ret;
    ret = (double **)malloc(sizeof(double *) * a_cols);
    for(int i = 0; i< a_cols; i++){
        ret[i] = (double*)malloc(a_rows*sizeof(double));
    }
    while(curRow < a_cols) {
        curCol = 0;
        while (curCol < a_rows) {
                ret[curRow][curCol] = a[curCol][curRow];
                curCol++;
        }
        curRow++;
    }

    return ret;
}
