#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

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

/**TAPE
 *                  +-----------+   +-----------+   +-----------+
 *     prev_node<---|  content  |---|  content  |---|  content  |--->next_node
 *                  +-----------+   +-----------+   +-----------+
*/
cell *new_node()
{
    cell *new = (cell *)malloc(sizeof(struct list_node));
    new->content = 0;
    new->next_node = NULL;
    new->prev_node = NULL;
    return new;
}

void delete_tape(cell *tape)
{
    int max_left = -count_left(tape);
    max_left += 1;
    cell *aux = tape;

    aux = move_tape(max_left, aux);
    if (aux == NULL)
    {
        printf("Trying to free empty memory");
        return;
    }
    if (aux->next_node == NULL)
        free(aux);
    else
    {
        aux = next_node(aux);
        free(aux->prev_node);
        delete_tape(aux);
    }
}

void print_node_content(cell *current) { printf(" %5d\n", current->content); }

cell *next_node(cell *t) { return t->next_node; };
cell *prev_node(cell *t) { return t->prev_node; };

void print_tape(cell *current, cell *beginning)
{
    printf("\nTAPE\n cell     content\n\n");
    if (current == NULL || beginning == NULL)
    {
        printf("ERROR, maybe you're trying to print different tapes, or no tapes are being held by those pointers");
    }
    int max_left = -count_left(beginning);
    max_left += 1;
    cell *aux = beginning;
    aux = move_tape(max_left, aux);

    do
    {
        printf("[%4i]", max_left);
        if (aux == current)
            printf(" > ");
        else
            printf("   ");
        print_node_content(aux);
        aux = move_tape(1, aux);
        max_left++;
    } while (aux != NULL);
}

cell *move_tape(int units, cell *pointer)
{
    if (units < 0)
        for (int i = units; i != 0; i++)
        {
            pointer = prev_node(pointer); //Positions pointer on the far end of the tape)
        }
    else
        for (int i = units; i != 0; i--)
        {
            pointer = next_node(pointer);
        }
    return pointer;
}

int count_left(cell *tape)
{
    if (tape == NULL)
        return 0;
    else
        return 1 + count_left(prev_node(tape));
}

int count_right(cell *tape)
{
    if (tape == NULL)
        return 0;
    else
        return 1 + count_right(next_node(tape));
}

void print_debug_tape(cell *t, cell *current)
{
    static int counter;
    if (t == NULL)
    {
        counter = 0;
        return;
    }

    else if (t == current)
        printf(" > ");
    else
        printf("   ");
    printf("[%i]", counter++);
    print_node_content(t);
    print_debug_tape(next_node(t), current);
}

void add_cell_left(cell *tape)
{
    if (tape->prev_node == NULL)
    {
        tape->prev_node = new_node();
        tape->prev_node->next_node = tape;
    }
    else
    {
        cell *new = new_node();
        tape->prev_node->next_node = new;
        new->next_node = tape;
        new->prev_node = tape->prev_node;
        tape->prev_node = new;
    }
}

void add_cell_right(cell *tape)
{
    if (tape->next_node == NULL)
    {
        tape->next_node = new_node();
        tape->next_node->prev_node = tape;
    }
    else
    {
        cell *new = new_node();
        tape->next_node->prev_node = new;
        new->prev_node = tape;
        new->next_node = tape->next_node;
        tape->next_node = new;
    }
}
