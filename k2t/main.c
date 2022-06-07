#include <stdio.h>
#include "k2tree.h"

/* K2Tree ADT implementation */
int main(void) {

    K2Tree t1;
    init_k2tree(&t1);
    
    /* image matrix */
    int arr[4][4] = {
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 0}
    };

    k2compress();

    return 0;
}

void k2compress(void) {
    return;
}

