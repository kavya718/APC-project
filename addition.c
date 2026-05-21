#include "head.h"


Node* add_lists(Node *h1, Node *t1, Node *h2, Node *t2, Node **rtail)
{
    Node *rh = NULL, *rt = NULL;    // result head & tail
    int carry = 0;                  // carry digit

    // continue until both numbers end and no carry remains
    while (t1 || t2 || carry)
    {
        int d1 = t1 ? t1->data : 0; // digit from number 1
        int d2 = t2 ? t2->data : 0; // digit from number 2

        int sum = d1 + d2 + carry;  // total
        carry = sum / 10;           // new carry

        insert_first(&rh, &rt, sum % 10); // store unit digit

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    *rtail = rt;
    return rh; // return result head
}

