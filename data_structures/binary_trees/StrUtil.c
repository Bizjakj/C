#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "CuTest.h"
#include "binary_search_tree.c"


void TestHeight(CuTest *tc) {
    node* root = NULL;
    int data = 0;
    root = insert(root,data);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, -1);
    CuAssertIntEquals(tc, 4, height(root));
    root = delete(root, 3);
    root = delete(root, 3);
    root = delete(root, 10);
    CuAssertIntEquals(tc, 3, height(root));
}

void TestFindNode(CuTest *tc){
    node* root = NULL;

    int data = 0;
    root = insert(root,data);

    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, -1);
    path* c = find(root, 3);

    CuAssertTrue(tc, c->found);
    CuAssertIntEquals(tc, 1, c->arr[0]);
    CuAssertIntEquals(tc, 0,  c->arr[1]);

    root = delete(root, 3);
    root = delete(root, 3);
    root = delete(root, 10);
    c = find(root, 4);
    CuAssertTrue(tc, c->found);

}

void TestTraversal(CuTest *tc){
    node* root = NULL;
    int file = creat("trav.txt", O_APPEND | O_RDWR);
    int save_out = dup(1);
    if(dup2(file,1) < 0){
        //printf("FAILED");
    }

    int data = 0;
    root = insert(root,data);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, -1);

    int result = dup2(save_out, 1);
    char *c = (char *) calloc(10, sizeof(char));
    read(file, c, 5);

    close(file);
}

CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestHeight);
    SUITE_ADD_TEST(suite, TestFindNode);
    SUITE_ADD_TEST(suite, TestTraversal);
    return suite;
}
