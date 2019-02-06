#include <assert.h>
#include "CArray.h"

int main(){
    CArray* arr = getCArray(4);
    insertValueCArray(arr, 0, 1);
    assert(arr->array[0]== 1);
}
