#include "head.h"

// Subtract two NON-NEGATIVE integers: returns |h1 - h2|
Node* subtract_lists(Node *h1, Node *t1, Node *h2, Node *t2, Node **rtail)
{
    Node *rh = NULL, *rt = NULL;  // result
    int borrow = 0;               // borrow flag

    int len1 = length(h1);
    int len2 = length(h2);

    // Ensure h1 >= h2 in absolute value
    if (len1 < len2 || (len1 == len2 && compare_lists(h1, h2) == 2))
    {
        Node *th = h1; h1 = h2; h2 = th;   // swap heads
        Node *tt = t1; t1 = t2; t2 = tt;   // swap tails
    }

    // Digit-by-digit subtraction
    while (t1 || t2)
    {
        int d1 = t1 ? t1->data : 0;
        int d2 = t2 ? t2->data : 0;

        d1 -= borrow;          // apply previous borrow
        borrow = 0;

        if (d1 < d2) {         // need borrow
            d1 += 10;
            borrow = 1;
        }

        insert_first(&rh, &rt, d1 - d2);  // store result digit

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    return normalize_list(rh);   // remove leading zeros
}

