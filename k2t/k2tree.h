#ifndef K2TREE_H
#define K2TREE_H (1)

#include "linked-lists/Llist.h"
#include "linked-lists/Tlist.h"

// Node
typedef struct k2node {
    Tlist tlist;
    Llist llist;
} k2node;

typedef k2node *K2Tree;

/*! \brief Compresses given file as per K2 format
 * \param[in] image array with dimensions
 * \retval void
 */
K2Tree k2_image_compress(int rows, int columns, int arr[rows][columns]);

/*! \brief Decompresses file
 * \param[in] Input file reference
 * \retval pointer to image
 */
//void fill_img_array(FILE *fp, int rows, int columns, int arr[rows][columns]);
int** make_image(FILE *fp, int rows, int columns);

#endif /* K2TREE_H */
