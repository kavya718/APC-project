/*
NAME : KAVYA P
DESCRIPTION : This project implements a Big Integer Calculator using Doubly Linked Lists in C.
Unlike normal integer operations that are limited by system data types, this project allows performing 
arithmetic on very large numbers (hundreds or thousands of digits) that cannot fit in standard int or long long 
variables.

The calculator supports:

Addition

Subtraction

Multiplication

Division

Handling of positive and negative numbers

Full input validation for incorrect operators, invalid digits, missing arguments, and division by zero.

Each digit of the number is stored as a node in a doubly linked list, enabling efficient forward 
and backward traversal for arithmetic operations. The project is modular, with separate C files for
 each operation, improving clarity and maintainability.

DATE : 10/12/2025
SAMPLE INPUT AND OUTPUT
INPUT:-
./a.out 12345 + 67890
OUTPUT:-
Result = 80235
INPUT:-
./a.out -50 + 20
OUTPUT:-
Result = -30


*/



#include "head.h"

// Compare absolute values
static int compare_abs(Node *a, Node *b)
{
    return compare_general(a, b);
}

// Signed addition: handles + and - signs
static Node* add_signed(Node *h1, Node *t1, int s1,
                        Node *h2, Node *t2, int s2,
                        int *rsign, Node **rtail)
{
    // If same sign → normal addition
    if (s1 == s2)
    {
        Node *rh = add_lists(h1, t1, h2, t2, rtail);
        *rsign = s1;
        return normalize_list(rh);
    }

    // If different signs → do subtraction
    int cmp = compare_abs(h1, h2);

    if (cmp == 0) {                   // numbers equal
        Node *zero = NULL;
        insert_first(&zero, rtail, 0);
        *rsign = 0;
        return zero;
    }

    if (cmp == 1) {                   // |h1| > |h2|
        *rsign = s1;
        return normalize_list(subtract_lists(h1, t1, h2, t2, rtail));
    }

    *rsign = s2;                      // |h2| > |h1|
    return normalize_list(subtract_lists(h2, t2, h1, t1, rtail));
}

// Signed subtraction: a - b = a + (-b)
static Node* subtract_signed(Node *h1, Node *t1, int s1,
                             Node *h2, Node *t2, int s2,
                             int *rsign, Node **rtail)
{
    int neg_b = s2 ^ 1; // flip sign
    return add_signed(h1, t1, s1, h2, t2, neg_b, rsign, rtail);
}

// Signed multiplication
static Node* multiply_signed(Node *h1, Node *t1, int s1,
                             Node *h2, Node *t2, int s2,
                             int *rsign, Node **rtail)
{
    Node *rh = multiply_lists(h1, t1, h2, t2, rtail);
    *rsign = s1 ^ s2;         // XOR sign rule
    return normalize_list(rh);
}

// Signed division
static Node* divide_signed(Node *h1, Node *t1, int s1,
                           Node *h2, Node *t2, int s2,
                           int *rsign, Node **rtail)
{
    if (h2->data == 0 && !h2->next)
        return NULL;

    Node *rh = divide_lists(h1, t1, h2, t2);
    *rsign = s1 ^ s2;         // XOR sign rule
    return normalize_list(rh);
}

int main(int argc, char *argv[])
{
    // Validate number of arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <num1> <op> <num2>\n", argv[0]);
        return 1;
    }

    const char *a = argv[1];
    const char *opstr = argv[2];
    const char *b = argv[3];

    // Validate operator
    if (strlen(opstr) != 1 || strchr("+-xX/", opstr[0]) == NULL)
    {
        fprintf(stderr, "Error: invalid operator. Allowed: + - x X /\n");
        return 1;
    }

    char op = opstr[0];

    // Validate operands
    if (!is_valid_signed_integer(a) || !is_valid_signed_integer(b))
    {
        fprintf(stderr, "Error: invalid operand\n");
        return 1;
    }

    const char *adigits, *bdigits;
    int asign = extract_sign_and_digits(a, &adigits);
    int bsign = extract_sign_and_digits(b, &bdigits);

    // Remove leading zeros
    while 
    
    (*adigits == '0' && adigits[1]) adigits++;
    while (*bdigits == '0' && bdigits[1]) bdigits++;

    // Convert to list
    Node *h1 = NULL, *t1 = NULL, *h2 = NULL, *t2 = NULL;
    h1 = create_list_from_digits(adigits, &t1);
    h2 = create_list_from_digits(bdigits, &t2);

    h1 = normalize_list(h1);
    h2 = normalize_list(h2);

    Node *result = NULL;
    Node *rt = NULL;
    int rsign = 0;

    // Choose operation
    if (op == '+')
        result = add_signed(h1, t1, asign, h2, t2, bsign, &rsign, &rt);
    else if (op == '-')
        result = subtract_signed(h1, t1, asign, h2, t2, bsign, &rsign, &rt);
    else if (op == 'x' || op == 'X')
        result = multiply_signed(h1, t1, asign, h2, t2, bsign, &rsign, &rt);
    else
    {
        if (h2->data == 0 && !h2->next)
        {
            fprintf(stderr, "Error: division by zero\n");
            return 1;
        }
        result = divide_signed(h1, t1, asign, h2, t2, bsign, &rsign, &rt);
    }

    // Print result
    printf("Result = ");
    print_number(result, rsign);

    free_list(h1);
    free_list(h2);
    free_list(result);

    return 0;
}

