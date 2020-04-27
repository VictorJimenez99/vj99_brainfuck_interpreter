#ifndef DEFS_H
#define DEFS_H

typedef struct list_node
{
    int content;
    struct list_node *next_node;
    struct list_node *prev_node;
} cell;

#endif