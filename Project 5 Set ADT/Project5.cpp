/*
 * Set ADT
 * Project5.c 
 *
 * Brian Coombs
 * Thursday 1:30
 * Spring 2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}
//Returns -1 if not found, and index if found
int binarySearch(const Set* self, int x){
    int min = 0;
    int max = self->len-1;
    while(min <= max){
        int mid = min+((max-min)/2);
        if(self->elements[mid]==x)return mid;      //If x is present at mid, then return
        if(self->elements[mid]<x) min = mid +1;     //If x is bigger, ignore left half
        else max = mid-1;                           //If x is smaller, ignore right half
    }
    return -1;


}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    if(binarySearch(self, x) == -1){
        return false;
    }
    else return true;
}
//Returns -1 if present and closest index otherwise
int indexOf(Set* self, int x, int min, int max){
    int mid =0;
    while(min <= max){
        mid = min+((max-min)/2);
        if(self->elements[mid]>x) { //If x is smaller, ignore right half
            max = mid-1;
        }
        else if(self->elements[mid]<x) { //If x is bigger, ignore left half
            min = mid +1;
        }
        else{ //If x is present at mid, return -1
            return -1;
        }
    }
    return min;
}
void insertSet(Set* self, int x) {
    int index = indexOf(self, x, 0, self->len-1);
    if(index == -1)return;
    if(self->len==0){
        createSingletonSet(self, x);
        return;
    }
    else {
        self->elements = (int *) realloc(self->elements, sizeof(int) * (self->len + 1));
        self->len++;
    }
    int z = 0;
    int y = x;
    for(; index <self->len-1; index++) {
        z = self->elements[index];
        self->elements[index] = y;
        y = z;
    }
    self->elements[self->len-1] = y;
}
//Remove the int selected
void removeSet(Set* self, int x) {
    int index = binarySearch(self, x);
    if(index != -1) {
        if(index != self->len) {
            for (; index < self->len - 1; index++) {
                self->elements[index] = self->elements[index + 1];
            }
        }
        self->len--;
    }
}
/* done for you already */
void displaySet(const Set* self) {
	int k;
	printf("{");
	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len != other->len) return false;
    for(int i=0; i<self->len; i++){
        if(self->elements[i] != other->elements[i]) return false;
    }
    return true;
}

//Checks whether self is within other
bool isSubsetOf(const Set* self, const Set* other) {
    int i = 0, j = 0;
    while (i < self->len) {
        if (j >= other->len) {
            return false;
        } else if (self->elements[i] < other->elements[j]) {
            return false;
        } else if (self->elements[i] > other->elements[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    return true;

}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

// Remove all elements from self that are not also elements of other
void intersectFromSet(Set* self, const Set* other) {
    int len = 0, i = 0, j = 0;
    int* elements = (int*) malloc(self->len * sizeof(int));


    while ((i < self->len) && (j < other->len)) {
        if (self->elements[i] < other->elements[j]) {
            i++;
        } else if (self->elements[i] > other->elements[j]) {
            j++;
        } else {
            elements[len++] = self->elements[i];
            i++;
            j++;
        }
    }

    free(self->elements);
    self->elements = elements;
    self->len = len;
}

// remove all elements from self that are also elements of other
void subtractFromSet(Set* self, const Set* other) {
    int len = 0, i = 0, j = 0;
    int* elements = (int*) malloc(self->len * sizeof(int));

        while (i < self->len) {
            if (j >= other->len) {
                elements[len++] = self->elements[i];
                i++;
            } else if (self->elements[i] < other->elements[j]) {
                elements[len++] = self->elements[i];
                i++;
            } else if (self->elements[i] > other->elements[j]) {
                j++;
            } else {
                i++;
                j++;
            }
        }

    free(self->elements);
    self->elements = elements;
    self->len = len;
}

// Add all elements of other to self (obviously, without creating duplicate elements)
void unionInSet(Set* self, const Set* other) {
    int len = 0, i = 0, j = 0;
    int *elements = (int *) malloc((self->len + other->len) * sizeof(int));
    while (i < self->len || j < other->len) {
        if (i >= self->len) {
            elements[len++] = other->elements[j];
            j++;
        } else if (j >= other->len) {
            elements[len++] = self->elements[i];
            i++;
        } else if (self->elements[i] < other->elements[j]) {
            elements[len++] = self->elements[i];
            i++;
        } else if (self->elements[i] > other->elements[j]) {
            elements[len++] = other->elements[j];
            j++;
        } else {
            elements[len++] = self->elements[i];
            i++;
            j++;
        }
    }
    free(self->elements);
    self->elements = elements;
    self->len = len;
}