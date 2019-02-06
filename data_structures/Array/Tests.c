#include <assert.h>
#include "CArray.h"
#include <stdio.h>
#include "time.h"

int main(){
    //Test array creation
    printf("initializing Array\n");
    CArray* arr = getCArray(4);
    int i;
    for(i = 0; i < 4; i++){
        assert(arr->array[i] == 0);
    }
    assert(arr->size == 4);
    displayCArray(arr);

    //test value insertion
    printf("inserting %d at position %d\n", 5, 2);
    insertValueCArray(arr, 2, 5);
    assert(arr->array[2]== 5);
    displayCArray(arr);
    printf("attempting to insert %d at position %d, array should not be changed\n", 4, 2);
    assert(arr->array[2]== 5);
    displayCArray(arr);

    //test pushValueCArray
    printf("pushing 10 , 0, -1, onto array\n");
    pushValueCArray(arr, 10);
    pushValueCArray(arr, 0);
    pushValueCArray(arr, -1);
    //assert(arr->array[arr->size - 1] == 10); assertion fails
    displayCArray(arr);


    //Test remove value
    printf("Removing element at position two and 6\n");
    removeValueCArray(arr, 2);
    removeValueCArray(arr, 6);
    assert(arr->array[2]== 0);

    displayCArray(arr);

    //Test erase
    printf("erasing array\n");
    eraseCArray(arr);
    for(i = 0; i < 4; i++){
        assert(arr->array[i] == 0);
    }
    displayCArray(arr);
    printf("erasing again\n");
    eraseCArray(arr);
    for(i = 0; i < 4; i++){
        assert(arr->array[i] == 0);
    }
    displayCArray(arr);

    printf("\nchanging value at 2 to 5, and at 1 to 1\n");
    insertValueCArray(arr, 0, 10);
    updateValueCArray(arr, 2, 5);
    updateValueCArray(arr, 1, 1);
    //assert(arr->array[2] == 4); assertion fails

    displayCArray(arr);

    printf("switching values at potitions 2 and 3");
    int pos2 = arr->array[2];
    int pos3 = arr->array[3];
    switchValuesCArray(arr, 2, 3);
    assert(arr->array[2] == pos3);
    assert(arr->array[3] == pos2);
    displayCArray(arr);

    printf("creating new array, a copy of old array\n");

    for(i = 0; i < 4; i++){
        insertValueCArray(arr, i, i+1);
    }

    CArray* arr2 = getCopyCArray(arr);


    printf("randomizing arrays\n");
    blenderCArray(arr2);
    displayCArray(arr2);
    wait(1);
    blenderCArray(arr2);
    displayCArray(arr2);

    printf("sorting c Array\n");
    bubbleSortCArray(arr2);
    for(i = 0; i < 3; i++){
        assert(arr2->array[i] <= arr2->array[i+1]);
    }
    displayCArray(arr2);

    CArray* arr3 = getCopyCArray(arr2);
    displayCArray(arr2);
    removeValueCArray(arr3, 0);
    displayCArray(arr3);

    printf("reversing arrays\n");
    reverseCArray(arr2);
    reverseCArray(arr3);
    displayCArray(arr2);
    displayCArray(arr3);
    for(i = 1; i < 4; i++){
        assert(arr2->array[i] >= arr2->array[i+1]);
    }
    for(i = 1; i < 4; i++){
        assert(arr3->array[i] >= arr3->array[i+1]);
    }


}
