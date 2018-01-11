/*
 * Brian Coombs
 * bjc2975
 * EE312 Project 3
 * Due October 2nd
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "String.h"

/* use these two macros and the function functions if you want -- not
   required */
#define SIGNATURE (~0xdeadbeef)

/** STRING(s)
 * Helper macro for accessing ut String object (if applicable)
 * [INPUT] pointer to cstring
 * [OUTPUT] pointer to UT String object (if applicable)
 */
#define STRING(s) ((String*)(s - 3*sizeof(uint32_t)))

/* this simple function can be useful when you implement stage 4 you
 * are not required to use the function, and you can implement stage 4
 * without it */
int32_t isOurs(const char* s) {
    if (STRING(s)->check == SIGNATURE) { return 1; }
    else { return 0; }
}

//Added function to check whether data is valid and has signature
void checkValid(char* s){
    assert(*((uint32_t*)s - 3) == SIGNATURE);		//check the ut_check for string s to be eql to signature
    assert(isOurs(s));                              //Creates redundancy by checking in two different ways
}

/* allocate a utstring on the heap, initialize the string correctly by
 * copying the characters from 'src' and return a pointer to the first
 * character of actual string data */

char* utstrdup(const char* src){
	char* ret;
    String* str = (String*)malloc(sizeof(String) + strlen(src) + 1);
	str->length = strlen(src);
    str->capacity = strlen(src);
    str->check = ~0xdeadbeef;
	for(int i = 0; i<strlen(src); i++){
        str->data[i] = src[i];
    }
    str->data[strlen(src)] =  0;
	ret = str->data;

    return ret;
}

/* the parameter 'utstr' must be a utstring. Find the length of this
 * string by accessing the meta-data and return that length */
uint32_t utstrlen(const char* utstr) {
    uint32_t length;
    checkValid((char*) utstr);      //Make sure 0xdeadbeef check is in string ptr
    String* str = STRING(utstr);
    length = str->length;
    return length;
}

/* s must be a utstring. suffix can be an ordinary string (or a
 * utstring) append the characters from suffix to the string s. Do not
 * allocate any additional storage, and only append as many characters
 * as will actually fit in s. Update the length meta-data for utstring
 * s and then return s */
char* utstrcat(char* s, const char* suffix) {
    checkValid(s);
    String* str = STRING(s);
    uint32_t length = strlen(suffix);		            //src length
    uint32_t dlength = str->length;		                //dst length
    assert(dlength == str->length);	                    //assure s length actually correct

    if (length > (str->capacity - dlength)) {
        int x = 0;
        for (int i = dlength; i < str->capacity ; i++) {
            str->data[i] = suffix[x];	                //add suffix data in utstring
            x++;
        }
        str->length = str->capacity;		            //fix s length
        str->data[str->capacity] = 0;		            //null term.
    }
    else {
        int j = 0;
        for (int i = dlength; i <= dlength + length; i++) {
            str->data[i] = suffix[j];		            //add suffix data in utstring
            j++;
        }
        str->length = dlength + length;		        //update length of dest
    }
    return s;
}

/* 'dst' must be a utstring. 'src' can be an ordinary string (or a
 * utstring) overwrite the characters in dst with the characters from
 * src. Do not overflow the capacity of dst For example, if src has
 * five characters and dst has capacity for 10, then copy all five
 * characters However, if src has ten characters and dst only has
 * capacity for 8, then copy only the first 8 characters. Do not
 * allocate any additional storage, do not change capacity. Update the
 * length meta-data for dst and then return dst */
char* utstrcpy(char* dst, const char* src) {
    checkValid(dst);
    String* str = STRING(dst);
    uint32_t length;
    uint32_t dlength;
    length = strlen(src);		                        //src string length
    dlength = str->length;	                            //dst string length
    assert(dlength == strlen(dst));		                //check dst length, same as above
    if (length > str->capacity) {
        for (int i = 0; i < str->capacity; i++) {
            str->data[i] = src[i];
        }
        str->data[str->capacity] = 0;		    //null term.
        str->length = str->capacity;		    //fix dlength
    }
    else {
        for (int i = 0; i <= length; i++) {
            str->data[i] = src[i];
        }
        str->length = length;
    }
    return dst;
}

/* self must be a utstring. deallocate the storage for this string
 * (i.e., locate the start of the chunk and call free to dispose of
 * the chunk, note that the start of the chunk will be 12 bytes before
 * *self) */
void utstrfree(char* self) {
    checkValid(self);
    free( ((uint32_t*)self) - 3 );		              //free first element on heap
}

/* s must be a utstring.  ensure that s has capacity at least as large
 * as 'new_capacity' if s already has capacity equal to or larger than
 * new_capacity, then return s if s has less capacity than
 * new_capacity, then allocate new storage with sufficient space to
 * store new_capacity characters (plus a terminating zero), copy the
 * current characters from s into this new storage. Update the
 * meta-data to correctly describe new new utstring you've created,
 * deallocate s and then return a pointer to the first character in
 * the newly allocated storage */
char* utstrrealloc(char* s, uint32_t new_capacity) {
    checkValid(s);
    String* str = STRING(s);
    char* retStr;
    if (str->capacity >= new_capacity) {
        return s;
    }
    else {
        String* newStr = (String*)malloc(sizeof(String) + new_capacity + 1);		//alloc space
        newStr->capacity = new_capacity;		        //chang length and capacity for string
        newStr->length = strlen(s);
        newStr->check = ~0xdeadbeef;
        for (int i = 0; i < newStr->length; i++) {
            newStr->data[i] = s[i];		                //copying chars from s to new str_data
        }
        newStr->data[newStr->length] = 0;	            //add null term
        retStr = newStr->data;		                    //return new str
        utstrfree(s);		                            //free up start str
    }
    return retStr;
}