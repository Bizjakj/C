// #include "CuTest.h"
// #include "CArray.h"
//
// void TestInsertValueCArray(CuTest *tc){
//     CArray* arr = getCArray(4);
//     insertValueCArray(arr, 0, 1);
//     CuAssertIntEquals(tc, arr->array[0], 1);
//
// }
//
// CuSuite* InsertValGetSuite(){
//     CuSuite* suite = CuSuiteNew();
//     SUITE_ADD_TEST(suite, TestInsertValueCArray);
//     return suite;
// }

#include "CuTest.h"

char* StrToUpper(char* str) {
    return str;
}

void TestStrToUpper(CuTest *tc) {
    char* input = strdup("hello world");
    char* actual = StrToUpper(input);
    char* expected = "HELLO WORLD";
    CuAssertStrEquals(tc, expected, actual);
}

CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestStrToUpper);
    return suite;
}
