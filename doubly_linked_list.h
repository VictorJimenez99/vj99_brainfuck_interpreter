#include "defs.h"

#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

cell *new_node();
void print_node_content();
cell *next_node(cell *t);
void print_tape(cell *current, cell *beginning);
void print_debug_tape(cell *t, cell *current);
void add_cell_left(cell *tape);
void add_cell_right(cell *tape);
cell *move_tape(int i, cell *pointer);
int count_left(cell *tape);
int count_right(cell *tape);

void delete_tape(cell *tape);

#endif