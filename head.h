#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node structure for doubly linked list
typedef struct Node {
    int data;            // stores one digit
    struct Node *prev;   // pointer to previous digit
    struct Node *next;   // pointer to next digit
} Node;

// Function declarations (implemented in respective .c files)
Node* add_lists(Node *h1, Node *t1, Node *h2, Node *t2, Node **rtail);
Node* subtract_lists(Node *h1, Node *t1, Node *h2, Node *t2, Node **rtail);
Node* multiply_lists(Node *h1, Node *t1, Node *h2, Node *t2, Node **rtail);
Node* divide_lists(Node *h1, Node *t1, Node *h2, Node *t2);

// Create new node
static Node* create_node(int data)
{
    Node *new = malloc(sizeof(Node));    // allocate memory
    new->data = data;                    // store digit
    new->prev = new->next = NULL;        // initialize links
    return new;
}

// Insert node at beginning
static void insert_first(Node **head, Node **tail, int data)
{
    Node *new = create_node(data);       // create new digit
    if (*head == NULL) // list empty
    {                 
        *head = *tail = new;
        return;
    }
    new->next = *head;                   // attach in front
    (*head)->prev = new;
    *head = new;
}

// Insert node at end
static void insert_last(Node **head, Node **tail, int data)
{
    Node *new = create_node(data);       // create digit
    if (*head == NULL) // empty list
    {                 
        *head = *tail = new;
        return;
    }
    (*tail)->next = new;                 // append at tail
    new->prev = *tail;
    *tail = new;
}

// Print full number with sign
static void print_number(Node *head, int sign)
{
    if (!head) 
    { 
        printf("0\n"); 
        return; 
    }

    // skip leading zeros
    Node *p = head;
    while (p->data == 0 && p->next) p = p->next;

    // print negative sign only if non-zero
    if (sign && p->data != 0) printf("-");

    // print digits
    for (; p; p = p->next)
    {

        printf("%d", p->data);
    }
    printf("\n");
}

// Free all nodes
static void free_list(Node *h)
{
    while (h) {
        Node *n = h->next;
        free(h);
        h = n;
    }
}

// Count digits
static int length(Node *h)
{
    int count = 0;       
    while (h) 
    { 
        count++; 
        h = h->next; 
    }
    return count;
}

// Compare lists of equal length (1=h1>h2, 2=h1<h2, 0=equal)
static int compare_lists(Node *h1, Node *h2)
{
    while (h1 && h2) {
        if (h1->data > h2->data) return 1;
        if (h1->data < h2->data) return 2;
        h1 = h1->next;
        h2 = h2->next;
    }
    return 0;
}

// Compare absolute values (length first)
static int compare_general(Node *a, Node *b)
{
    int la = length(a);
    int lb = length(b);

    if (la > lb) 
        return 1;
    if (la < lb) 
        return 2;
    return compare_lists(a, b);
}

// Build linked list from digits
static Node* create_list_from_digits(const char *num, Node **tail)
{
    Node *head = NULL;
    *tail = NULL;
    while (*num)
        insert_last(&head, tail, *num++ - '0');
    return head;
}

// Skip leading zero digits
static Node* normalize_list(Node *h)
{
    while (h->data == 0 && h->next)
        h = h->next;
    return h;
}

// Validate signed integer format
static int is_valid_signed_integer(const char *s)
{
    if (*s == '+' || *s == '-') s++;     // allow sign
    if (!*s) return 0;                   // no digits
    while (*s)
        if (!isdigit(*s++)) return 0;    // invalid char
    return 1;
}

// Extract sign ---> 0 positive, 1 negative
static int extract_sign_and_digits(const char *s, const char **digits_out)
{
    if (*s == '+') 
    { 
        *digits_out = s + 1; 
        return 0; 
    }
    if (*s == '-') 
    { 
        *digits_out = s + 1; 
        return 1; 
    }
    *digits_out = s;
    return 0;
}

#endif

