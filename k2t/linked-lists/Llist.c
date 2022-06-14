#include <stdio.h>
#include <stdlib.h>
#include "Llist.h"


void init_Llist(Llist *l) {
    *l = NULL;
}

void append_Lnode(Llist *l, int key) {

    Lnode *nn = (Lnode*)malloc(sizeof(Lnode));
    if (!nn) {
        printf("Unable to malloc Lnode\n");
        return;
    }
    nn->key = key;
    nn->next = NULL;

    if (!(*l)) {
        *l = nn;
        return;
    }
    Lnode *p = *l;
    Lnode *q = p;

    while(p) {
        q = p;
        p = p->next;
    }
    q->next = nn;

}


int get_Lnode_count(Llist l) {

    int count = 0;
    Lnode *p = l;

    while(p) {
        ++count;
        p = p->next;
    }

    return count;
}

void traverse_Lnode(Llist l) {

    Lnode *p = l;
    while (p) {
        printf("%d-", p->key);
        p = p->next;
    }
}

void destroy_Llist(Llist *l) {

    Lnode *p = *l;
    Lnode *q = NULL;

    while(p) {
        q = p;
        p = p->next;
        free(q);
    }

    *l = NULL;
}

