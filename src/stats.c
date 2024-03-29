/**
 * @file stats.c
 * @author Javier Chavez
 * @date January 22, 2016
 * @brief Statistics implementation.
 *
 */

#include <ctype.h>
#include "stats.h"


void read(FILE* in, List* list)
{
    List* current = list;
    int c = 0;
    int prev = 0;
    
    while ( 1 )
    {
        c = fgetc( in );
        if (c == EOF)
        {
            break;
        }

        /* Paragraph is defined as /n/n */
        if (prev == 10 && c == 10)
        {
            /* create a new node and add to list */
            current = create_empty_node();
            add_last(list, current);
            continue;
        }

        if (c < ASCII_MAX)
        {
            /* increment a given char */
            current->occurrences[c] += 1;
        }
        prev = c;
    }
    
}


void print_stats(List* list)
{
    int i = 1;
    List* current = list;
    
    printf("Paragraphs%2s %d\n\n",":", length(list));
    
    while(list != NULL)
    {
        /* poll the list (remove first) */
        current = poll(&list);
        print(current->occurrences, i);
        /* remove the node from mem */
        free(current);
        i++;
    }

}


void print(unsigned long count[], int current_element)
{
    
    int i = 0;
    unsigned long total=0;
    unsigned long readable_total=0;
    
    for ( i = 0 ; i < ASCII_MAX ; i++ )
    {
        if( count[i] > 0 )
        {
            /* sum all chars */
            total += count[i];
            
            if (i >= 32 && i <= 126)
            {
                /* sum all the readables */
                readable_total += count[i];
            }
        }
    }

    /* output to stdout with new stats */
    printf("Paragraph #%d: %lu %lu %lu\n",
           current_element,
           count[10],
           count[32]+1,
           total);
}
