#include "head.h"


static Node* multiply_single_digit(Node *h1, Node *t1, int d, Node **rtail)
{
    int carry = 0;
    Node *rh = NULL, *rt = NULL;

    // multiply each digit with d
    while (t1)
    {
        int prod = t1->data * d + carry;
        carry = prod / 10;
        insert_first(&rh, &rt, prod % 10);
        t1 = t1->prev;
    }

    if (carry) insert_first(&rh, &rt, carry);

    *rtail = rt;
    return rh;
}

// Add zeros at end (place shift)
static Node* append_zeros(Node *h, Node **tail, int zeros)
{
    while (zeros--)
        insert_last(&h, tail, 0);
    return h;
}

// Multiply two NON-NEGATIVE big integers
Node* multiply_lists(Node *h1, Node *t1, Node *h2, Node *t2, Node **rtail)
{
    Node *final_h = NULL, *final_t = NULL;
    int shift = 0;

    // multiply h1 with each digit of h2 (from right to left)
    while (t2)
    {
        Node *row_tail = NULL;
        Node *row = multiply_single_digit(h1, t1, t2->data, &row_tail);

        row = append_zeros(row, &row_tail, shift); // shift position

        if (!final_h) {             // first row
            final_h = row;
            final_t = row_tail;
        }
        else {
            Node *temp_tail = NULL;

            Node *new_sum = add_lists(final_h, final_t, row, row_tail, &temp_tail);

            free_list(final_h);
            free_list(final_t);
            free_list(row);
            free_list(row_tail);

            final_h = new_sum;
            final_t = temp_tail;
        }

        shift++;
        t2 = t2->prev;
    }

    *rtail = final_t;
    return final_h;
}

