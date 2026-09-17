#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fa.h"

/*
 * Print the transitions of a finite automata (fa).
 * Shows start, finish and character needed to transition between states
 */
void print_automata(fa *automata) {
    printf("Automata:\n");
    printf(" Start: %d\n", automata->start);
    printf(" States of acceptance: ");
    for (int i = 0; i < automata->length_accept_states; i++) {
        int a = automata->accept_states[i];
        printf("%d ", a);
    }
    printf("\nTransiciones:\n");
    for (int i = 0; i < automata->length; i++) {
        transition t = automata->transitions[i];

        if (t.symbol == EPSILON) {
            printf("  %d --(eps)--> %d\n", t.start, t.finish);
        } else {
            printf("  %d --(%c)--> %d\n", t.start, t.symbol, t.finish);
        }
    }
}

/*
 * Epsilon-closure
 * Computes the epsilon closure of a set of states T using a stack (DFS)
 * and a visited array to prevent infinite loops in epsilon cycles.
 */
int epsilon_closure(const fa *automata, const int *current_states, int current_count, int *out_closure, int max_states) {
    if (automata == NULL || current_states == NULL || current_count <= 0 ||
        out_closure == NULL || max_states <= 0) {
        return 0;
    }

    bool *visited = (bool *)calloc((size_t)max_states, sizeof(bool));
    if (visited == NULL) {
        return 0;
    }

    int *stack = (int *)malloc((size_t)max_states * sizeof(int));
    if (stack == NULL) {
        free(visited);
        return 0;
    }

    int top = -1;
    int closure_count = 0;

    
    for (int i = 0; i < current_count; i++) {
        int s = current_states[i];
        if (s >= 0 && s < max_states && !visited[s]) {
            visited[s] = true;
            out_closure[closure_count++] = s;
            stack[++top] = s;
        }
    }

    
    while (top >= 0) {
        int t = stack[top--]; 

      
        for (int i = 0; i < automata->length; i++) {
            if (automata->transitions[i].start == t && automata->transitions[i].symbol == EPSILON) {
                int u = automata->transitions[i].finish;
                
                if (u >= 0 && u < max_states && !visited[u]) {
                    visited[u] = true;
                    out_closure[closure_count++] = u; 
                    stack[++top] = u;                
                }
            }
        }
    }

    free(stack);
    free(visited);
    return closure_count; 
}

void print_state_set(const char *label, const int *states, int count) {
    printf("%s: { ", label);
    for (int i = 0; i < count; i++) {
        printf("%d%s", states[i], (i + 1 < count) ? ", " : " ");
    }
    printf("}\n");
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

    // Test epsilon-closure with the sample automata from initial state 
    int initial_set[] = {0};
    int closure[5];
    int count = epsilon_closure(&automata, initial_set, 1, closure, automata.states);
    print_state_set("epsilon-closure({0})", closure, count);

    free(automata.transitions);
    free(automata.accept_states);

    
    // Test from Lab Manual: Epsilon cycles test
    printf("\n=== Manual Test Epsilon Cycles ===\n");
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
    print_state_set("Result obtained for epsilon-closure({0})", test_closure, test_count);
    printf("Expected result: { 0, 1, 2 }\n");

    free(test_fa.transitions);

    return 0;
}
