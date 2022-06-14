#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void init_list(list *l) {
    *l = NULL;
}

void append_node(list *l, int key) {

    node *nn = (node*)malloc(sizeof(node));
    if (!nn) {
        printf("Unable to malloc node\n");
        return;
    }
    nn->key = key;
    nn->next = NULL;

    if (!(*l)) {
        *l = nn;
        return;
    }
    node *p = *l;
    node *q = p;

    while(p) {
        q = p;
        p = p->next;
    }
    q->next = nn;

}


int get_node_count(list l) {

    int count = 0;
    node *p = l;

    while(p) {
        ++count;
        p = p->next;
    }

    return count;
}


void destroy_list(list *l) {

    node *p = *l;
    node *q = NULL;

    while(p) {
        q = p;
        p = p->next;
        free(q);
    }

    *l = NULL;
}

