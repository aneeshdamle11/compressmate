#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "k2tree.h"

#define FIRST_IMG_BIT(X)        (X & 8)
#define SECOND_IMG_BIT(X)       (X & 4)
#define THIRD_IMG_BIT(X)        (X & 2)
#define FOURTH_IMG_BIT(X)       (X & 1)

Tnode *ptrT;
Lnode *ptrL;

void k2compress(int rows, int columns, int arr[rows][columns], K2Tree *p) {

    int i, j;
    K2Tree T = *p;

    if (rows == 1 && columns == 1) {
        //fwrite(arr, 1, sizeof(int), fp);
        append_Lnode(&(T->llist), arr[0][0]);
        return;
    }

    int flag[4] = {0};
    int temp[rows/2][columns/2];

    // Subimage 1
    for (int i = 0; i < rows/2; ++i) {
        for (j = 0; j < columns/2; j++) {
            if (arr[i][j]) {
                //putchar('1');
                flag[0] = 1;
                break;
            }
        }
        if (flag[0] == 1)
            break;
    }
    if (flag[0] == 0);
        //putchar('0');


    // Subimage 2
    for (int i = 0; i < rows/2; ++i) {
        for (j = columns/2; j < columns; j++) {
            if (arr[i][j]) {
                //putchar('1');
                flag[1] = 1;
                break;
            }
        }
        if (flag[1] == 1)
            break;
    }
    if (flag[1] == 0);
        //putchar('0');


    // Subimage 3
    for (int i = rows/2; i < rows; ++i) {
        for (j = 0; j < columns/2; j++) {
            if (arr[i][j]) {
                //putchar('1');
                flag[2] = 1;
                break;
            }
        }
        if (flag[2] == 1)
            break;
    }
    if (flag[2] == 0);
        //putchar('0');


    // Subimage 4
    for (int i = rows/2; i < rows; ++i) {
        for (j = columns/2; j < columns; j++) {
            if (arr[i][j]) {
                //putchar('1');
                flag[3] = 1;
                break;
            }
        }
        if (flag[3] == 1)
            break;
    }
    if (flag[3] == 0);
        //putchar('0');

    uint8_t simg = 0;
    for (int i = 0; i < 4; ++i) {
        simg = simg * 2 + flag[i];
    }
    //printf("%d-", simg);
    //fwrite(&simg, 1, 1, out_t);
    append_Tnode(&(T->tlist), simg);
    simg = 0;

    //putchar('\n');
    if (flag[0]) {
        for (int i = 0; i < rows/2; ++i) {
            for (j = 0; j < columns/2; ++j) {
               temp[i][j] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp, p);
    }


    if (flag[1]) {
        for (int i = 0; i < rows/2; ++i) {
            for (j = columns/2; j < columns; ++j) {
                temp[i][j-columns/2] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp, p);
    }


    if (flag[2]) {
        for (int i = rows/2; i < rows; ++i) {
            for (j = 0; j < columns/2; ++j) {
                temp[i-rows/2][j] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp, p);
    }


    if (flag[3]) {
        for (int i = rows/2; i < rows; ++i) {
            for (j = columns/2; j < columns; ++j) {
                temp[i-rows/2][j-columns/2] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp, p);
    }

    return;

}


K2Tree k2_image_compress(int rows, int columns, int arr[rows][columns]) {
    K2Tree p = (K2Tree)malloc(sizeof(k2node));
    p->tlist = NULL;
    p->llist = NULL;

    k2compress(rows, columns, arr, &p);
    return p;
}

void fill_img_array(K2Tree p, int rows, int columns, int arr[rows][columns]) {

    int i, j;
    uint8_t imgbit;

    if (rows == 1 && columns == 1) {

        if (ptrL == NULL)
            return;
        arr[0][0] = ptrL->key;
        ptrL = ptrL->next;
        return;
    }

    int temp[rows/2][columns/2];

    //fscanf(fp, "%c", (ch + i));
    if (ptrT == NULL)
        return;
    imgbit = ptrT->key;
    ptrT = ptrT->next;

    if (FIRST_IMG_BIT(imgbit) == 0) {
        for (i = 0; i < rows/2; ++i) {
            for (j = 0; j < columns/2; j++) {
                arr[i][j] = 0;
            }
        }
    } else {

        for (i = 0; i < rows/2; ++i) {
            for (j = 0; j < columns/2; j++) {
                temp[i][j] = 0;
            }
        }

        fill_img_array(p, rows/2, columns/2, temp);

        for (i = 0; i < rows/2; ++i) {
            for (j = 0; j < columns/2; j++) {
                arr[i][j] = temp[i][j];
            }
        }
    }

    if (SECOND_IMG_BIT(imgbit) == 0) {
        for (i = 0; i < rows/2; ++i) {
            for (j = columns/2; j < columns; ++j) {
                arr[i][j] = 0;
            }
        }
    } else {
        for (i = 0; i < rows/2; ++i) {
            for (j = columns/2; j < columns; ++j) {
                temp[i][j] = 0;
            }
        }
 
        fill_img_array(p, rows/2, columns/2, temp);

        for (i = 0; i < rows/2; ++i) {
            for (j = columns/2; j < columns; ++j) {
                arr[i][j] = temp[i][j - columns/2];
            }
        }
    }

    if (THIRD_IMG_BIT(imgbit) == 0) {
        for (i = rows/2; i < rows; ++i) {
            for (j = 0; j < columns/2; j++) {
                arr[i][j] = 0;
            }
        }
    } else {
        for (i = rows; i < rows/2; ++i) {
            for (j = 0; j < columns/2; j++) {
                temp[i][j] = 0;
            }
        }
 
        fill_img_array(p, rows/2, columns/2, temp);

        for (i = rows/2; i < rows; ++i) {
            for (j = 0; j < columns/2; ++j) {
                arr[i][j] = temp[i - rows/2][j];
            }
        }

    }
 
    if (FOURTH_IMG_BIT(imgbit) == 0) {
        for (i = rows/2; i < rows; ++i) {
            for (j = columns/2; j < columns; ++j) {
                arr[i][j] = 0;
            }
        }
    } else {
        for (i = 0; i < rows/2; ++i) {
            for (j = 0; j < columns/2; ++j) {
                temp[i][j] = 0;
            }
        }

        fill_img_array(p, rows/2, columns/2, temp);

        for (i = rows/2; i < rows; ++i) {
            for (j = columns/2; j < columns; ++j) {
                arr[i][j] = temp[i - rows/2][j - columns/2];
            }
        }

    }

}


void fill_k2_tree(FILE *fp, K2Tree *T) {

    int t_count, l_count;

    // Read T count
    fread(&t_count, sizeof(int), 1, fp);

    K2Tree p = *T;

    int i, t_fill, l_fill;
    for (i = 0; i < t_count; ++i) {
        fread(&t_fill, 1, 1, fp);
        append_Tnode(&(p->tlist), t_fill);
    }

    // Read L count
    fread(&l_count, sizeof(int), 1, fp);

    for (int i = 0; i < l_count; ++i) {
        fread(&l_fill, sizeof(int), 1, fp);
        append_Lnode(&(p->llist), l_fill);
    }

    traverse_Lnode(p->llist);
    printf("\nLtraverse_done\n");
    traverse_Tnode(p->tlist);
    printf("\nTtraverse_done\n");
    putchar('\n');

}

int** make_image(FILE *fp) {
/*
    fread(&t_count, 1, 1, fp);
    printf("%d\n", FIRST_IMG_BIT(t_count));
    printf("%d\n", SECOND_IMG_BIT(t_count));
    printf("%d\n", THIRD_IMG_BIT(t_count));
    printf("%d\n", FOURTH_IMG_BIT(t_count));
*/

    // Make a K2Tree
    K2Tree p = (K2Tree)malloc(sizeof(k2node));
    p->tlist = NULL;
    p->llist = NULL;

    fill_k2_tree(fp, &p);

    ptrT = p->tlist;
    ptrL = p->llist;

    int row = 8, col = 8;
    int temp[row][col];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            temp[i][j] = 0;
        }
        
    }

    // Fill the image array
    fill_img_array(p, row, col, temp);

    destroy_Llist(&(p->llist));
    destroy_Tlist(&(p->tlist));
    free(p);

    int **arr = (int **)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; ++i) {
        arr[i] = (int*)malloc(sizeof(int) * col);
        for (int j = 0; j < col; j++) {
            arr[i][j] = temp[i][j];
        }
    }


    return arr;
}




