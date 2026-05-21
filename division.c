#include "head.h"


Node* divide_lists(Node *h1, Node *t1, Node *h2, Node *t2)
{
    if (h2->data == 0 && !h2->next)   // divide by zero
        return NULL;

    Node *sum_h = NULL, *sum_t = NULL;
    insert_last(&sum_h, &sum_t, 0);   // sum = 0

    int count = 0;                    // quotient counter

    // keep adding divisor until >= dividend
    while (1)
    {
        Node *new_t = NULL;
        Node *new_sum = add_lists(sum_h, sum_t, h2, t2, &new_t);

        free_list(sum_h);
        free_list(sum_t);

        sum_h = new_sum;
        sum_t = new_t;

        count++;

        int cmp = compare_general(sum_h, h1);

        if (cmp == 1) {    // sum > dividend
            count--;
            break;
        }
        if (cmp == 0) {    // exact division
            break;
        }
    }

    free_list(sum_h);
    free_list(sum_t);

    char buf[25];
    sprintf(buf, "%d", count);   // convert quotient to string

    Node *qh = NULL, *qt = NULL;
    for (int i = 0; buf[i]; i++)
        insert_last(&qh, &qt, buf[i] - '0');

    return qh;
}
