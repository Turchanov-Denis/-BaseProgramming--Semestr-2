#include <iostream>
#define N 100
int main() {
    int mas_a[N] = {1,2,3,4,5};
    int mas_b[N] = {0};
    int* srcPtr = mas_a;
    int* destPtr = mas_b;
    // no indexing
    while (srcPtr < mas_a + N) {
        *destPtr++ = *srcPtr++;
    }
    return 0;
}