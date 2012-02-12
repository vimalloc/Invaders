#ifndef LINKED_LIST
#define LINKED_LIST

/*
 * doubly linked list, designed to used for bullet objects in Invaders.
 */

/*
 * Nodes used in this singly linked list
 */
typedef struct ll_node_t ll_node_t;
struct ll_node_t{
    ll_node_t *next;
    ll_node_t *prev;
    void *item;
};

/*
 * Struct for a singly linked list
 */
typedef struct {
    ll_node_t *head;
    ll_node_t *tail;
} ll_t;

/*
 * Creates a new singly linked list
 */
ll_t* ll_init();

/*
 * Frees all the memory used by a singly linked list
 */
void ll_free(ll_t *ll);

/*
 * Insert an item into the start of the linked list
 */
void ll_insert(ll_t *ll, void *item);

/*
 * Removes the given node from the singly linked list
 */
ll_node_t* ll_remove(ll_node_t *node);

/*
 * Returns the next node in the linked list, or NULL if there
 * are no more items in the linked list.
 */
ll_node_t* ll_next_node(ll_t *ll, ll_node_t *node);

/*
 * Returns the contents stored in a given node.
 */
void* ll_get_item(ll_node_t *node);

/*
 * Returns the first node in this linked list, or NULL if the list is empty
 */
ll_node_t* ll_get_first_node(ll_t *ll);

#endif

