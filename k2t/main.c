#include <stdio.h>
#include <stdlib.h>
#include "k2tree.h"


//void k2compress(int rows, int columns, int arr[rows][columns]);
//void make_image(FILE *fp);
//void fill_img_array(FILE *fp, int rows, int columns, int arr[rows][columns]);

/* K2Tree ADT implementation */
int main(void) {

    /* image matrix */

/*
    int arr[4][4] = {
        {1, 2, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 0}
    };
*/

    int arr2[8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0},
        {1,1,0,0,0,0,1,1},
        {0,1,0,0,0,0,0,0}
    };

    int i = 0, t_key = 0, l_key = 0;

    printf("%dx%d \n", 8, 8);

    K2Tree p = k2_image_compress(8, 8, arr2);
    if (!p) {
        printf("Noooo\n");
        return 1;
    }
    int t_count = get_Tnode_count(p->tlist);
    int l_count = get_Lnode_count(p->llist);

    FILE *fp = fopen("comp3.txt", "wb");
    if (!fp) {
        printf("Unable to access file\n");
        return 2;
    }

    // Write size of T array
    fwrite(&t_count, sizeof(int), 1, fp);
    // Write contents of T array in file
    Tnode *pT = p->tlist;
    for (i = 0; i < t_count; ++i) {
        t_key = pT->key;
        pT = pT->next;
        fwrite(&t_key, 1, 1, fp);
    }

    printf("T success\n");

    // Write size of L array
    fwrite(&l_count, sizeof(int), 1, fp);
    // Write contents of L array in file
    Lnode *pL = p->llist;
    for (int i = 0; i < l_count; ++i) {
        l_key = pL->key;
        pL = pL->next;
        fwrite(&l_key, sizeof(int), 1, fp);
    }

    printf("L success\n");

    fclose(fp);
    destroy_Llist(&(p->llist));
    destroy_Tlist(&(p->tlist));
    free(p);

    // Reading file contents
    fp = fopen("comp3.txt", "rb");
    if (!fp) {
        printf("Unable to access file\n");
        return 3;
    }

    int row = 8, col = 8;
    int **arr5 = make_image(fp, row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            printf("%10d ", arr5[i][j]);
        }
        putchar('\n');
    }

    //free(arr);

    fclose(fp);

    return 0;
}

