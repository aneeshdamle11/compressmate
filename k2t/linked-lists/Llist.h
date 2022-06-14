#ifndef L_LINKED_LIST_H
#define L_LINKED_LIST_H (1)
#include <stdint.h>

/* Node */
typedef struct Lnode {
    uint8_t key;
    struct Lnode* next;
} Lnode;

/* List */
typedef Lnode* Llist;


/*! \brief iniLialise Lhe linked lisL Lo NULL
 * \param[in] list ref
 * \retval void
 */
void init_Llist(Llist *l);

/*! \brief Insert a node at the end
 * \param[in] list ref, key to be inserted
 * \retval void
 */
void append_Lnode(Llist *l, uint8_t key);

void traverse_Lnode(Llist l);

/*! \brief count total elements in a linked list
 * \param[in] list ref
 * \retval number of elements
 */
int get_Lnode_count(Llist l);

/*! \brief Destroy a linked list
 * \param[in] list pointer ref
 * \retval void
 */
void destroy_Llist(Llist *l);


#endif /* L_LINKED_LISL_H */
