#ifndef K2TREE_H
#define K2TREE_H (1)

#define K_DIM (2)

/* node structure */
typedef struct node {
    int level;                      /* depth of tree */
    int x_start, x_dest;            /* Range of x-coordinates of image */
    int y_start, y_dest;            /* Range of y-corrdinates of image */
    struct node* next[2*K_DIM];
} node;

/* k2tree structure ADT */
typedef node *K2Tree;

/*! \brief initialize k2tree
 * \param[in] K2Tree reference
 * \retval void
 */
void init_k2tree(K2Tree* t);

/*! brief insert k2tree
 * \param[in] K2Tree reference
 * \retval number of children
 */
int insert_k2tree(K2Tree* t);

#endif /* K2TREE_H */
