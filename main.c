#include <stdio.h>
#include <stdlib.h>
#include "fa.h"

/*
 * Print the transitions of a finite automata (fa).
 * Shows start, finish and character needed to transition between states
 */
void print_automata(fa *automata) {
    printf("Automata:\n");
    printf(" Start: %d", automata->start);
    printf(" States of acceptance:\n");
    for (int i = 0; i < automata->length_accept_states; i++) {
        int a = automata->accept_states[i];
        printf("%d ", a);
    }
    printf("Transiciones:\n");
    for (int i = 0; i < automata->length; i++) {
        transition t = automata->transitions[i];

        if (t.symbol == EPSILON) {
            printf("  %d --(eps)--> %d\n", t.start, t.finish);
        } else {
            printf("  %d --(%c)--> %d\n", t.start, t.symbol, t.finish);
        }
    }
}

int main(void) {
    fa automata;

    //Declaration of params
    automata.start = 0;
    automata.length_accept_states = 1;
    automata.accept_states = malloc(sizeof(int) * automata.length_accept_states);
    automata.accept_states[0] = 2; // The final state
    automata.states = 5;
    automata.length = 5; 
    automata.transitions = malloc(sizeof(transition) * automata.length);

    //Creation of transitions
    automata.transitions[0] = (transition){0, 1, EPSILON}; // 0 -> 1
    automata.transitions[1] = (transition){0, 3, EPSILON}; // 0 -> 3
    automata.transitions[2] = (transition){1, 2, 'a'};     // 1 -a-> 2
    automata.transitions[3] = (transition){3, 4, 'b'};     // 3 -b-> 4
    automata.transitions[4] = (transition){4, 2, 'c'};     // 4 -c-> 2

    print_automata(&automata);

    free(automata.transitions);
    free(automata.accept_states);

    return 0;
}