/*
 * Project1.cpp
 * Name: Brian Coombs
 * bjc2975
 * EE312 Fall 2017
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
typedef unsigned uint32_t;

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other 'support functions' that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

/* Returns the length of the array of characters
 * input: array of characters
 * output: length of array of characters
 */

uint32_t length(char s[]){
    uint32_t i;
    for(i=0; 0 != s[i]; i++){}
    return i;
}

/* Modifies the array at pointer s, turning all the letters into lowercase
 * Inputs: Pointer to character array s
 * Outputs: none
 */

void lower(char* s){
    while(*s != 0) {
        if (*s >= 'A' && *s <= 'Z') {
            *s += ('a' - 'A');
        }
        s++;
    }
}

/* Returns the character only if it a letter
 * Input: Character
 * Output: Character only if it is a letter, otherwise, a zero
 */

char isLetter(char c){
    return ((c >= 'a' && c <= 'z'));
}

/* Boolean function that checks whether array of chars w is in dictionary
 * inputs: pointer to first char in null-terminated array w and the array of chars dictionary that contains correct words
 * 1. Iterates through whole dictionary to search for word that matches
 * 2. Returns to beginning of array if not a match
 */

bool word(char* w, char dictionary[]){
    if(length(w) <= 1){return true;}
    char* wOrig = w;
    char* dictPtr = dictionary;
    while(*dictionary != '\0'){
        if(*dictionary == '\n'){
            if(*w == '\0'){
                uint32_t l;
                for(l = 0; dictPtr[l] != '\n'; l++){}       //Size of current word in dict
                if(l == length(wOrig)){
                    return true;
                }
            }
        }
        if(*dictionary == *w){
            w++;
        }
        else{
            w = wOrig;
            if(*dictionary == '\n'){
                dictPtr = dictionary+1;
            }
        }
        dictionary++;
    }
    return false;
}

/* Actual spellCheck function
 * 1. makes sure that the article and dictionary are both lower case to allow ASCII comparison
 * 2. Iterates through entire article creating words, checking if those words are in the dictionary using the subr
 * 3. If the word is not in the dictionary, it is printed
 * 4. Checks the edge case
 */

void spellCheck(char article[], char dictionary[]) {

    lower(article);
    lower(dictionary);

    char* printWord = article;
    while (*article != '\0') {
        if(isLetter(*article) == 0){
            *article = '\0';
            if(!word(printWord, dictionary)){
                printf("%s\n", printWord);
            }
            printWord = article+1;
        }
        article++;
    }
    //Edge case for checking last word
    if (!word(printWord, dictionary)) {
        printf("%s\n", printWord);
    }
}