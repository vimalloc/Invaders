#include "linked_list.h"
#include "errors.h"

static ll_node_t* ll_node_init(void *item) {
    ll_node_t *node;

    node = malloc(sizeof(ll_node_t));
    if(!node)
        system_error("Malloc error in ll_node_init");

    node->item = item;
    return node;
}

ll_t* ll_init() {
    ll_t *ll;

    ll = malloc(sizeof(ll_t));
    if(!ll)
        system_error("Malloc error in ll_init");

    /* Create the initial empty list */
    ll->head = ll_node_init(NULL);
    ll->tail = ll_node_init(NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;

    return ll;
}

void ll_free(ll_t *ll) {
    ll_node_t *node;

    /* Free all of the nodes in the list*/
    node = ll->head->next;
    node = ll_get_first_node(ll);
    while(node) {
        node = ll_remove(ll, node);
    }

    free(ll->head);
    free(ll->tail);
    free(ll);
}

void ll_insert(ll_t *ll, void *item) {
    ll_node_t *node;
    ll_node_t *head;

    node = ll_node_init(item);
    head = ll->head;

    /* Do the insertion into the linked list */
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

ll_node_t* ll_remove(ll_t *ll, ll_node_t *node) {
    ll_node_t *next;
    ll_node_t *prev;

    prev = node->prev;
    next = node->next;

    /* Remove this node from the list */
    prev->next = next;
    next->prev = prev;
    free(node);

    if(next ==  ll->tail)
        return NULL;
    return next;
}

ll_node_t* ll_next_node(ll_t *ll, ll_node_t *node) {
    if(node->next == ll->tail)
        return NULL;

    return node->next;
}

void* ll_get_item(ll_node_t *node) {
    return node->item;
}

ll_node_t* ll_get_first_node(ll_t *ll) {
    if(ll->head->next == ll->tail)
        return NULL;
    return ll->head->next;
}

void ll_append_list(ll_t *l1, ll_t *l2) {
    ll_node_t *node;

    node = ll_get_first_node(l1);
    while(node) {
        ll_insert(l2, ll_get_item(node));
        node = ll_next_node(l1, node);
    }
}

