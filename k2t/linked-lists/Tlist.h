#ifndef T_LINKED_LIST_H
#define T_LINKED_LIST_H (1)
#include <stdint.h>

/* Node */
typedef struct Tnode {
    uint8_t key;
    struct Tnode* next;
} Tnode;

/* List */
typedef Tnode* Tlist;


/*! \brief initialise the linked list to NULL
 * \param[in] list ref
 * \retval void
 */
void init_Tlist(Tlist *l);

/*! \brief Insert a node at the end
 * \param[in] list ref, key to be inserted
 * \retval void
 */
void append_Tnode(Tlist *l, uint8_t key);

void traverse_Tnode(Tlist l);

/*! \brief count total elements in a linked list
 * \param[in] list ref
 * \retval number of elements
 */
int get_Tnode_count(Tlist l);

/*! \brief Destroy a linked list
 * \param[in] list pointer ref
 * \retval void
 */
void destroy_Tlist(Tlist *l);


#endif /* T_LINKED_LIST_H */
