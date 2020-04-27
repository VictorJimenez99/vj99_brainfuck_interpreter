#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "defs.h"

cell *run_code(cell *pointer, FILE *code, unsigned long int code_position);
cell *center;
unsigned char debug = 0;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("Not enough arguments: arguments should be name of files");
        exit(EXIT_FAILURE);
    }
    if (argc == 3)
    {
        if (argv[2][0] == '-')
            debug = 1;
    }

    cell *tape = new_node();
    cell *pointer = tape;

    center = tape;

    unsigned long int code_position = 0;

    FILE *code = fopen(argv[1], "r");

    if (code == NULL)
    {
        perror("CANNOT open file");
        return (EXIT_FAILURE);
    }
    fflush(stdout);

    pointer = run_code(pointer, code, code_position);
}

cell *run_code(cell *pointer, FILE *code, unsigned long int code_position)
{
    //inside new block of instruccions
    unsigned long int loop_position = code_position;
    fseek(code, loop_position, SEEK_SET); //put the position at the beginning of the loop
    //printf("new set of instruccions");
    char instruction;
    do
    {
        instruction = fgetc(code);
        loop_position++;
        if (feof(code))
        {
            printf("\nEnd of file\n");

            //getchar();
            break;
        }
        fflush(stdout);
        //printf("\nreading: %c at instruccion %lu", instruction, loop_position);
        fflush(stdout);

        switch (instruction)
        {
        case '>':
            if (pointer->next_node == NULL)
                add_cell_right(pointer);
            pointer = move_tape(1, pointer);
            break;
        case '<':
            if (pointer->prev_node == NULL)
                add_cell_left(pointer);
            pointer = move_tape(-1, pointer);
            break;
        case '+':
            pointer->content++;
            break;
        case '-':
            pointer->content--;
            break;
        case ',':
            pointer->content = (int)getchar();
            break;
        case '.':
            //if (pointer->content <= 255)
            //  printf("%c", (char)pointer->content);
            //else
            printf("%4d,", pointer->content);
        case '[':
            //loop_position++;
            //loop_position = code_position;
            while (pointer->content != 0)
            {
                fseek(code, loop_position, SEEK_SET);
                //printf("entering a new frame with position %lu\n", loop_position);
                pointer = run_code(pointer, code, loop_position);
            }
            //printf("0 found at pointer, left loop with success");
            fseek(code, loop_position, SEEK_SET);
            int stack = 1;
            char cur;
            //printf("\nbeginning to move to pairing bracket, skipping this loop\n");
            while (1)
            {
                cur = fgetc(code);
                loop_position++;
                //printf("%c", cur);
                if (feof(code))
                {
                    perror("unbalanced brackets");
                    exit(0);
                }
                if (cur == ']')
                {
                    stack--;
                    if (stack == 0)
                        break;
                }
                else if (cur == '[')
                    stack++;
            }
            //code_position++;
            fseek(code, loop_position, SEEK_SET);
            break;
        case ']':
            //returning from stack frame
            //printf(" end of a loop");
            //fseek(code, loop_position, SEEK_SET);
            return pointer;
            break;
        default:
            continue;
            break;
        }
        if (debug)
            print_tape(pointer, center);
        //print_tape(pointer, center);
        //getchar();
        code_position++;

    } while (1);
    if (debug)
        print_tape(pointer, center);
    fclose(code);
    delete_tape(center);
    exit(0);
}
