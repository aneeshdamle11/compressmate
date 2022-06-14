#ifndef LINKED_LIST_H
#define LINKED_LIST_H (1)

/* Node */
typedef struct node {
    int key;
    struct node* next;
} node;

/* List */
typedef node* list;


/*! \brief initialise the linked list to NULL
 * \param[in] list ref
 * \retval void
 */
void init_list(list *l);

/*! \brief Insert a node at the end
 * \param[in] list ref, key to be inserted
 * \retval void
 */
void append_node(list *l, int key);

/*! \brief count total elements in a linked list
 * \param[in] list ref
 * \retval number of elements
 */
int get_node_count(list l);

/*! \brief Destroy a linked list
 * \param[in] list pointer ref
 * \retval void
 */
void destroy_list(list *l);


#endif /* ifndef LINKED_LIST_H */
