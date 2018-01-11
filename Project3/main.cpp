// StringADT demonstration file main.cpp
#include <stdio.h>
#include <string.h> // declares the built-in C string library functions, like strcat
#include "String.h" // declares our new improved String functions, like utstrcat
#include <stdlib.h>

#define STRING(s) ((String*)(s - 3*sizeof(uint32_t)))
#define BIG_STR "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
#define MSV_STR "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

void testStage1(void) {
    char p[12];
    const char* q = "Hello World";
    char* s;
    char* t;
    unsigned k;

    printf("this test should print Hello World three times\n");

    for (k = 0; k < 12; k += 1) {
        p[k] = q[k];
    }
    s = utstrdup(p);
    printf(s);
    printf("\n");

    q = "you goofed!";
    for (k = 0; k < 12; k += 1) {
        p[k] = q[k];
    }
    printf(s);
    printf("\n");

    t = utstrdup(s);
    utstrfree(s);

    printf(t);
    printf("\n");
    utstrfree(t);
}

void testStage2(void) {
    char c_str1[20] = "hello";
    char* ut_str1;
    char* ut_str2;

    printf("Starting stage 2 tests\n");
    strcat(c_str1, " world");
    printf("%s\n", c_str1); // nothing exciting, prints "hello world"

    ut_str1 = utstrdup("hello ");
    ut_str1 = utstrrealloc(ut_str1, 20);

    utstrcat(ut_str1, c_str1);
    printf("%s\n", ut_str1); // slightly more exciting, prints "hello hello world"
    utstrcat(ut_str1, " world");
    printf("%s\n", ut_str1); // exciting, should print "hello hello world wo", 'cause there's not enough room for the second world

    ut_str2 = utstrdup("");
    ut_str2 = utstrrealloc(ut_str2, 11);
    utstrcpy(ut_str2, ut_str1 + 6);
    printf("%s\n", ut_str2); // back to "hello world"

    ut_str2 = utstrrealloc(ut_str2, 23);
    utstrcat(ut_str2, " ");
    utstrcat(ut_str2, ut_str1);
    printf("%s\n", ut_str2); // now should be "hello world hello hello"

    utstrfree(ut_str1);
    utstrfree(ut_str2);
}

#define BIG 1000000
void testStage3(void) {
    int k;
    char* ut_str1 = utstrdup("");
    ut_str1 = utstrrealloc(ut_str1, BIG); // big, big string

    printf("attempting stage 3 test. This shouldn't take long...\n");
    printf("(no really, it shouldn't take long, if it does, you fail this test)\n");
    fflush(stdout);

    for (k = 0; k < BIG; k += 1) {
        utstrcat(ut_str1, "*");
    }
    if (ut_str1[BIG-1] != '*') {
        printf("stage3 fails for not copying all the characters\n");
    } else if (strlen(ut_str1) != BIG) {
        printf("Hmmm, stage3 has something wrong\n");
    } else {
        printf("grats, stage 3 passed (unless it took a long time to print this message)\n");
    }
    utstrfree(ut_str1);
}

void testStage4(void) {

    /* each of the following lines should crash the program (an assert should fail)
     * try each of them in turn to make sure you're catching the obvious mistakes
     * just uncomment the line and see what happens (it should crash)
     */
    char p[20] = "Hello";
    //printf("crashing with utstrlen\n\n\n"); utstrlen("Hello World");
    //printf("crashing with utstrcpy\n\n\n"); utstrcpy(p, "Hello World");
    //printf("crashing with utstrcat\n\n\n"); utstrcat(p, "Hello World");
    //printf("crashing with utstrfree\n\n\n"); utstrfree((char *)malloc(20));
    //printf("crashing with utstrrealloc\n\n\n"); utstrrealloc((char *)malloc(20), 40);
}

void testStageCustom(void){
    printf("\nStarting custom tests\n");

    // really long strings
    char* testStr = utstrdup(BIG_STR);
    char* longUTString = utstrdup(MSV_STR);
    //should print: CAPACITY: 445 | LENGTH: 445
    printf("CAPACITY: %d | LENGTH: %d\n", STRING(testStr)->capacity, STRING(testStr)->length);
    //should print: CAPACITY: 2229 | LENGTH: 2229
    printf("CAPACITY: %d | LENGTH: %d\n", STRING(longUTString)->capacity, utstrlen(longUTString));

    // set the string and check capcity and length
    testStr = utstrcpy(testStr, "blanked");
    //should print: blanked | CAPACITY: 445 | LENGTH: 7
    printf("%s | CAPACITY: %d | LENGTH: %d\n", testStr, STRING(testStr)->capacity, utstrlen(testStr));

    // test concat w/ nothing a bunch of times
    for(int i = 0; i < 1024; i++){
        utstrcat(testStr, "");
    }
    //should print: blanked | CAPACITY: 445 | LENGTH: 7
    printf("%s | CAPACITY: %d | LENGTH: %d\n", testStr, STRING(testStr)->capacity, utstrlen(testStr));

    // test concat w/ something a bunch number of times
    for(int i = 0; i < 1024; i++){
        utstrcat(testStr, "a");
    }
    //should print: CAPACITY: 445 | LENGTH: 445
    printf("CAPACITY: %d | LENGTH: %d\n", STRING(testStr)->capacity, utstrlen(testStr));

    // realloc
    testStr = utstrrealloc(testStr, 1023);
    //should print: CAPACITY: 1023 | LENGTH: 445
    printf("CAPACITY: %d | LENGTH: %d\n", STRING(testStr)->capacity, utstrlen(testStr));

    // actually blank string
    testStr = utstrcpy(testStr, "");
    //should print:  | CAPACITY: 1023 | LENGTH: 0
    printf("%s | CAPACITY: %d | LENGTH: %d\n", testStr, STRING(testStr)->capacity, STRING(testStr)->length);

    // copy a really really really big literal string
    testStr = utstrcpy(testStr, MSV_STR);
    //should print: CAPACITY: 1023 | LENGTH: 1023 | CHECK: 0xdeadbeef
    printf("CAPACITY: %d | LENGTH: %d | CHECK: %p\n", STRING(testStr)->capacity, utstrlen(testStr), (void*)~STRING(testStr)->check);

    // set string and concat with really really really big utstring
    testStr = utstrcpy(testStr, "hello! ");
    utstrcat(testStr, longUTString);
    //should print: CAPACITY: 1023 | LENGTH: 1023 | CHECK: 0xdeadbeef
    printf("CAPACITY: %d | LENGTH: %d | CHECK: %p\n", STRING(testStr)->capacity, utstrlen(testStr), (void*)~STRING(testStr)->check);

    // actually print out above (first 28 characters at least) to verify concat
    printf("%.28s\n", testStr); // should print: hello! Lorem ipsum dolor sit

    utstrfree(testStr);
    utstrfree(longUTString);
}

int main(void) {
    testStage1();
    testStage2();
    testStage3();
    testStage4();
    testStageCustom();
    return 0;
}