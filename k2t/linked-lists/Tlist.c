#include <stdio.h>
#include <stdlib.h>
#include "Tlist.h"


void init_Tlist(Tlist *l) {
    *l = NULL;
}

void append_Tnode(Tlist *l, uint8_t key) {

    Tnode *nn = (Tnode*)malloc(sizeof(Tnode));
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
    Tnode *p = *l;
    Tnode *q = p;

    while(p) {
        q = p;
        p = p->next;
    }
    q->next = nn;

}


void traverse_Tnode(Tlist l) {

    Tnode *p = l;
    while (p) {
        printf("%d-", p->key);
        p = p->next;
    }
}

int get_Tnode_count(Tlist l) {

    int count = 0;
    Tnode *p = l;

    while(p) {
        ++count;
        p = p->next;
    }

    return count;
}


void destroy_Tlist(Tlist *l) {

    Tnode *p = *l;
    Tnode *q = NULL;

    while(p) {
        q = p;
        p = p->next;
        free(q);
    }

    *l = NULL;
}

