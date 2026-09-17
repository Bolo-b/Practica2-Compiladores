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

    print_automata(&automata);
    
    /////////////////////////
    // Test move {0,1} with 'a'
    /////////////////////////
    int *T = malloc(3 * sizeof(int));
    T[0] = 0; //Ignores the Espsilon transition
    T[1] = 1; //Moves to 2 reading a
    T[2] = 3; //Ignores b
    list *result = move(automata,T,3,'a');
    //Print the linked list
    printf("\nTest Move\n");
    printf("move({0,1,3},'a') = { ");
    node *actual = result->head;
    while (actual != NULL) {
        printf("%d ", *(int *)actual->data);
        actual = actual->next;
    }
    printf("}\n"); //Expected {2}
    
    list_free(result);
    free(result);
    free(T);

    /////////////////////////
    // Test Epsilon-closure with the sample automata from initial state
    /////////////////////////
    int initial_set[] = {0};
    int closure[5];
    int count = epsilon_closure(&automata, initial_set, 1, closure, automata.states);
    printf("\nTest Epsilon-closure\n");
    printf("%s: { ", "epsilon-closure({0})");
    for (int i = 0; i < count; i++) {
        printf("%d%s", closure[i], (i + 1 < count) ? ", " : " ");
    } printf("}\n");
    /////////////////////////
    // Test Epsilon cycles test
    /////////////////////////
    printf("\nTest Epsilon Cycles\n");
    fa test_fa;
    test_fa.start = 0;
    test_fa.length_accept_states = 0;
    test_fa.accept_states = NULL;
    test_fa.states = 4;
    test_fa.length = 3;
    test_fa.transitions = malloc(sizeof(transition) * test_fa.length);
    test_fa.transitions[0] = (transition){0, 1, EPSILON};
    test_fa.transitions[1] = (transition){1, 2, EPSILON};
    test_fa.transitions[2] = (transition){2, 1, EPSILON}; // Cycle
    int test_closure[4];
    int test_count = epsilon_closure(&test_fa, initial_set, 1, test_closure, test_fa.states);
    printf("%s: { ", "Result obtained for epsilon-closure({0})");
    for (int i = 0; i < test_count; i++) {
        printf("%d%s", test_closure[i], (i + 1 < test_count) ? ", " : " ");
    }
    printf("}\n");
    printf("Expected result: { 0, 1, 2 }\n");
    free(test_fa.transitions);

    /////////////////////////
    // Test NFA to DFA
    /////////////////////////
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