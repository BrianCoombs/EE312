#include <stdio.h>

int main() {
    int x[] = { 1, 8, 6, 4, 3 };
    if(sumsTo(x,5, 3, 9)){
        printf("True");
    }
    else{
        printf("False");
    }

}

//x is array
//n is length
//k is num of ints to sum
//v is total sum
int sumsTo(int x[], int n, int k, int v) {
    if(k==0 && v==0){
        return 1;
    }
    if(n==0){
        return 0;
    }
    int i = sumsTo(x+1, n-1, k-1, v-x[0]);
    if(i){
        return i;
    }
    else{
        return sumsTo(x+1, n-1, k, v);
    }

}

