//binary tree
#include <stdlib.h>
#include <stdio.h>

struct Elm
{
    int x;
    struct Elm *left, *right;
};

typedef struct Elm Elm;
Elm *root;
int count = 0, max = 0, min = 100000;
Elm *search(int x)
{
    Elm *p = root;
    while (p != NULL)
    {
        if (p->x == x)
            break;
        else if (p->x < x)
            p = p->right;
        else
            p = p->left;
    }
    return p;
}

Elm *minValue(Elm *p)
{

    while (p && p->left != NULL)
        p = p->left;

    return p;
}

Elm *deleteVal(Elm *p, int x)
{

    if (p == NULL)
        return p;

    if (x < p->x)
        p->left = deleteVal(p->left, x);
    else if (x > p->x)
        p->right = deleteVal(p->right, x);
    else
    {

        if (p->left == NULL)
        {
            Elm *temp = p->right;
            free(p);
            return temp;
        }
        else if (p->right == NULL)
        {
            Elm *temp = p->left;
            free(p);
            return temp;
        }

        Elm *temp = minValue(p->right);

        p->x = temp->x;

        p->right = deleteVal(p->right, temp->x);
    }
}

Elm *minDelete(Elm *p)
{

    Elm *temp = minValue(p);

    p = deleteVal(p, temp->x);

    return p;
}

void inorder(struct Elm *p)
{

    if (p != NULL)
    {
        inorder(p->left);
        printf("%d ", p->x);
        inorder(p->right);
    }
}

Elm *rank(int x)
{

    Elm *p = root;
    while (p != NULL)
    {
        count++;
        if (p->x == x)
            break;
        else if (p->x < x)
            p = p->right;
        else
            p = p->left;
        ;
    }

    return p;
}

int _size(Elm *p)
{

    if (p == NULL)
    {

        return 0;
    }
    else
        return (_size(p->left) + 1 + _size(p->right));
}

int size(int x)
{

    return _size(search(x));
}

int rank(int x, Elm *p)
{

    if (p == NULL)
        return 0;
    if (x < p->x)
        return rank(x, p->left);
    else if (x > p->x)
        return 1 + _size(p->left) + rank(x, p->right);
    else
        return _size(p->left);
}

void floor(struct Elm *p, int x)
{

    if (p != NULL)
    {
        floor(p->left, x);
        if (p->x < x && p->x > max)
        {

            max = p->x;
        }
        floor(p->right, x);
    }
}

void ceiling(struct Elm *p, int x)
{

    if (p != NULL)
    {
        ceiling(p->left, x);
        if (p->x > x && p->x < min)
        {

            min = p->x;
        }
        ceiling(p->right, x);
    }
}

Elm *insert1(Elm *p, int x)
{
    if (p == NULL)
    {
        p = (Elm *)malloc(sizeof(Elm));
        p->x = x;
        p->left = p->right = NULL;
        return p;
    }
    else if (p->x < x)
        p->right = insert1(p->right, x);
    else
        p->left = insert1(p->left, x);
    return p;
}

void insert2(Elm *p, int x, Elm *pr)
{
    if (p == NULL)
    {
        p = (Elm *)malloc(sizeof(Elm));
        if (pr == NULL)
            root = p;
        else
        {
            if (pr->x < x)
                pr->right = p;
            else
                pr->left = p;
        }
        p->x = x;
        p->left = p->right = NULL;
        return;
    }
    else if (p->x < x)
        insert2(p->right, x, p);
    else
        insert2(p->left, x, p);
}

int main()
{
    root = insert1(root, 1);
    root = insert1(root, 2);
    root = insert1(root, 3);
    root = insert1(root, 7);
    root = insert1(root, 5);
    root = insert1(root, 12);
    root = insert1(root, 9);
    root = insert1(root, 6);
    inorder(root);
    printf("\n");

    printf("3 Hayag : ");
    printf("%d\n", search(3));

    printf("Del 3: ");
    deleteVal(root, 3);

    inorder(root);
    printf("\n");

    printf("Del 7: ");
    deleteVal(root, 7);

    inorder(root);
    printf("\n");

    printf("Del min: ");
    root = minDelete(root);
    inorder(root);
    printf("\n");

    printf("Size 2: ");
    printf("%d\n", size(2));

    printf("Rank 9: ");
    printf("%d\n", rank(9, root));

    printf("floor 9: ");
    floor(root, 9);
    printf("%d\n", max);
    max = 0;

    printf("ceiling 5: ");
    ceiling(root, 5);
    printf("%d\n", min);
    min = 10000;

    /*

    3
    / \
    1 7
    \ /
    2 5
    */
    return 0;
}