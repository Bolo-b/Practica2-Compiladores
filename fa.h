#include "LinkedList.h"
#define EPSILON '\0'

//Diferent states are represented just as a positive integer 
typedef struct transition {
    int start;
    int finish;
    char symbol; //the symbol needed to travel between states
} transition;

//We will represent the nfa as a list of transitions
typedef struct fa {
    transition *transitions;
    int start;
    int *accept_states;
    int length_accept_states;
    int length; //Length of the transition list
    int states;
} fa;

list *move(fa automata, int *T, int length_T, char a);
int epsilon_closure(const fa *automata, const int *current_states, int current_count, int *out_closure, int max_states);
