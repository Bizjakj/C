#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "CuTest.h"
#include "CArray.c"


void TestGetCArray(CuTest *tc) {
    CArray* arr = getCArray(4);
    int actual = arr->size;
    int expected = 4;
    CuAssertIntEquals(tc, expected, actual);
    int i;
    for(i = 0; i < 4; i++){
        CuAssertIntEquals(tc, 0, arr->array[i]);
    }
}

void TestInsertCArray(CuTest *tc) {
    CArray* arr = getCArray(10);

    int i;
    for(i = 0; i < 15; i++){
        int r = rand();
        int res = insertValueCArray(arr, i, r);
        if(i < arr->size){
            CuAssertIntEquals(tc, r, arr->array[i]);
        }else{
            CuAssertIntEquals(tc, 1, res);
        }
    }
}

void TestPushCArray(CuTest *tc) {
    CArray* arr = getCArray(4);

    pushValueCArray(arr, 10);
    pushValueCArray(arr, -1);
    pushValueCArray(arr, 10);
    int res = pushValueCArray(arr, 10);

    CuAssertIntEquals(tc, 10, arr->array[0]);
    CuAssertIntEquals(tc, -1, arr->array[1]);
    CuAssertIntEquals(tc, 10, arr->array[2]);
    CuAssertIntEquals(tc, 0, res);
}

void TestRemoveCArray(CuTest *tc) {
    CArray* arr = getCArray(4);

    insertValueCArray(arr, 1, 4);
    insertValueCArray(arr, 2, 5);

    int test1 = removeValueCArray(arr, 1);
    int test2 = removeValueCArray(arr, 6);

    CuAssertIntEquals(tc, 0, arr->array[1]);
    CuAssertIntEquals(tc, 0, test1);
    CuAssertIntEquals(tc, 1, test2);

}

void TestEraseCArray(CuTest *tc) {
    CArray* arr = getCArray(4);
    int i;
    for(i = 0; i < 15; i++){
        int r = rand();
        int res = insertValueCArray(arr, i, r);
    }

    eraseCArray(arr);

    for(i = 0; i < 4; i++){
        CuAssertIntEquals(tc, 0, arr->array[i]);
    }
}

void TestUpdateCArray(CuTest *tc){
    CArray* arr = getCArray(4);

    insertValueCArray(arr, 1, 4);
    insertValueCArray(arr, 2, 5);
    insertValueCArray(arr, 3, 5);

    int res1 = updateValueCArray(arr, 2, 5);
    int res2 = updateValueCArray(arr, 1, 1);
    updateValueCArray(arr, 3, 1);

    CuAssertIntEquals(tc, 1, arr->array[1]);
    CuAssertIntEquals(tc, 5, arr->array[2]);
    CuAssertIntEquals(tc, 1, arr->array[3]);

    CuAssertIntEquals(tc, 0, res1);
}

void TestSwitchCArray(CuTest *tc){
    CArray* arr = getCArray(4);

    insertValueCArray(arr, 0, 3);
    insertValueCArray(arr, 1, 5);
    insertValueCArray(arr, 2, 7);
    insertValueCArray(arr, 3, 8);

    int rval = switchValuesCArray(arr, 2, 3);
    CuAssertIntEquals(tc, 8, arr->array[2]);
    CuAssertIntEquals(tc, 7, arr->array[3]);
    CuAssertIntEquals(tc, 0, rval);

}

void TestSortCArray(CuTest *tc){
    CArray* arr = getCArray(10);
    int i;
    for(i = 0; i < 4; i++){
        int r = rand();
        int res = insertValueCArray(arr, i, r);
    }
    bubbleSortCArray(arr);

    for(i = 0; i < 3; i++){
        CuAssertTrue(tc, arr->array[i] <= arr->array[i+1]);
    }
}
void TestReverseCArray(CuTest *tc){
    CArray* arr = getCArray(10);
    int i;
    for(i = 0; i < 4; i++){
        int r = rand();
        int res = insertValueCArray(arr, i, r);
    }
    bubbleSortCArray(arr);


    reverseCArray(arr);
    for(i = 0; i < 3; i++){
        CuAssertTrue(tc, arr->array[i] >= arr->array[i+1]);
    }
}

CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestGetCArray);
    SUITE_ADD_TEST(suite, TestInsertCArray);
    SUITE_ADD_TEST(suite, TestPushCArray);
    SUITE_ADD_TEST(suite, TestRemoveCArray);
    SUITE_ADD_TEST(suite, TestEraseCArray);
    SUITE_ADD_TEST(suite, TestUpdateCArray);
    SUITE_ADD_TEST(suite, TestSwitchCArray);
    SUITE_ADD_TEST(suite, TestSortCArray);
    SUITE_ADD_TEST(suite, TestReverseCArray);
    return suite;
}
