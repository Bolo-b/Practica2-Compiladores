#include <stdio.h>
#include <stdlib.h>

#include "fa.h"

int main(void) {

    fa automata;

    automata.start = 0;

    automata.length_accept_states = 1;
    automata.accept_states = malloc(sizeof(int));
    automata.accept_states[0] = 2;

    automata.states = 5;

    automata.length = 5;
    automata.transitions = malloc(
        sizeof(transition) * automata.length
    );

    /*
     * NFA for (a|bc)
     */

    automata.transitions[0] =
        (transition){0, 1, EPSILON};

    automata.transitions[1] =
        (transition){0, 3, EPSILON};

    automata.transitions[2] =
        (transition){1, 2, 'a'};

    automata.transitions[3] =
        (transition){3, 4, 'b'};

    automata.transitions[4] =
        (transition){4, 2, 'c'};


    char alphabet[] = {'a', 'b', 'c'};
    int alphabet_size = 3;

    dfa *deterministic = nfa_to_dfa(
        &automata,
        alphabet,
        alphabet_size
    );

    print_dfa(deterministic);

    free_dfa(deterministic);

    free(automata.transitions);
    free(automata.accept_states);

    return 0;
}