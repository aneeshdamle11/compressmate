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
    int **arr5 = make_image(fp);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            printf("%10d ", arr5[i][j]);
        }
        putchar('\n');
    }

    //free(arr);

    fclose(fp);

    //int arr3[36] = {1,0,1,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,1,1,1,0,0,1,1,0,1,1,0,0,1};

/*
    putchar('\n');
    FILE *fp1 = fopen("temp.txt", "r");

    int temp[2][2] = {0};
    fill_img_array(fp1, 2, 2, temp);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; j++) {
            printf("%d\n", temp[i][j]);
        }
    }

    fclose(fp1);
*/
    return 0;
}
/*
void k2compress(int rows, int columns, int arr[rows][columns]) {

    int i, j;

    if (rows == 1 && columns == 1) {
        fwrite(arr, 1, sizeof(int), out_l);
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

    int simg = 0;
    for (int i = 0; i < 4; ++i) {
        simg = simg * 2 + flag[i];
    }
    //printf("%d-", simg);
    fwrite(&simg, 1, 1, out_t);
    simg = 0;

    //putchar('\n');
    if (flag[0]) {
        for (int i = 0; i < rows/2; ++i) {
            for (j = 0; j < columns/2; ++j) {
               temp[i][j] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp);
    }


    if (flag[1]) {
        for (int i = 0; i < rows/2; ++i) {
            for (j = columns/2; j < columns; ++j) {
                temp[i][j-columns/2] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp);
    }


    if (flag[2]) {
        for (int i = rows/2; i < rows; ++i) {
            for (j = 0; j < columns/2; ++j) {
                temp[i-rows/2][j] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp);
    }


    if (flag[3]) {
        for (int i = rows/2; i < rows; ++i) {
            for (j = columns/2; j < columns; ++j) {
                temp[i-rows/2][j-columns/2] = arr[i][j];
            }
        }
        k2compress(rows/2, columns/2, temp);
    }

    return;

}


void fill_img_array(FILE *fp, int rows, int columns, int arr[rows][columns]) {

    if (!fp)
        return;

    int i, j;
    char ch[4];

    if (rows == 1 && columns == 1) {

        for (i = 0; i < 4; ++i) {
            //fscanf(fp, "%c", (ch + i));
            printf("%d, ", 1);
        }
        return;
    }

    int temp[rows/2][columns/2];

    for (i = 0; i < 4; ++i) {
        //fscanf(fp, "%c", (ch + i));
        if (ch[i] == EOF)
            return;
    }

    if (ch[0] == '0') {
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

        fill_img_array(fp, rows/2, columns/2, temp);

        for (i = 0; i < rows/2; ++i) {
            for (j = 0; j < columns/2; j++) {
                arr[i][j] = temp[i][j];
            }
        }
    }

    if (ch[1] == '0') {
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
 
        fill_img_array(fp, rows/2, columns/2, temp);

        for (i = 0; i < rows/2; ++i) {
            for (j = columns/2; j < columns; ++j) {
                arr[i][j] = temp[i][j - columns/2];
            }
        }
    }

    if (ch[2] == '0') {
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
 
       fill_img_array(fp, rows/2, columns/2, temp);

        for (i = rows/2; i < rows; ++i) {
            for (j = 0; j < columns/2; ++j) {
                arr[i][j] = temp[i - rows/2][j];
            }
        }

    }
 
    if (ch[3] == '0') {
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

        fill_img_array(fp, rows/2, columns/2, temp);

        for (i = rows/2; i < rows; ++i) {
            for (j = columns/2; j < columns; ++j) {
                arr[i][j] = temp[i - rows/2][j - columns/2];
            }
        }

    }

}

void make_image(FILE *fp) {

    int row, col;
    char ch, ch1;

    putchar('\n');
    fscanf(fp, "%d%c%d%c", &row, &ch, &col, &ch);

    int arr[row][col];

    fill_img_array(fp, row, col, arr);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            printf("%10d ", arr[i][j]);
        }
        putchar('\n');
    }
    return;
}

void k2compress(int rows, int columns, int arr[rows][columns]) {

    if (!arr)
        return;
    
    K2Tree t1;

    init_k2tree(&t1, 0, rows, 0, columns);

    build_k2tree(4, 4, arr, &t1);

    return;
}
*/

