#include <stdlib.h>
#include "Implementation.h"
#include "LinkedList.h"

/*
 * Look for the integer in the linked list
 * return 1 if is in the list, 0 if not
 */
int belongs(list l, int value) {
    node *actual = l.head;
    while (actual != NULL) {
        if (*(int *)actual->data == value) {
            return 1;
        }
        actual = actual->next;
    }
    return 0;
}


/*
 * automata: fa
 * T: array of states (int*)
 * length_T: length of array T
 * a: carachter
 * Return pointer to the head of the linked list
 */
list *move(fa automata, int *T, int length_T, char a) {
    list *R = malloc(sizeof(list));
    *R = list_create();

    for (int i = 0; i < length_T; i++) {
        int s = T[i];

        //Look for the transitions that use s and a 
        for (int j = 0; j < automata.length; j++) {
            transition t = automata.transitions[j];
            if (t.start == s && t.symbol == a) {
                if (!belongs(*R, t.finish)) {
                    int *new_state = malloc(sizeof(int));
                    *new_state = t.finish;
                    list_push(R, new_state);
                }
            }
        }
    }
    return R;
}
