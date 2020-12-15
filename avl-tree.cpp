//avl tree
#include <stdlib.h>
#include <stdio.h>

struct Elm
{
    int x;
    struct Elm *left, *right;
    int height;
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

int height(struct Elm *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int maxim(int a, int b)
{
    return (a > b) ? a : b;
}

struct Elm *newNode(int key)
{
    struct Elm *node = (struct Elm *)
        malloc(sizeof(struct Elm));
    node->x = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

struct Elm *rightRotate(struct Elm *y)
{
    struct Elm *x = y->left;
    struct Elm *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxim(height(y->left), height(y->right)) + 1;
    x->height = maxim(height(x->left), height(x->right)) + 1;

    return x;
}

struct Elm *leftRotate(struct Elm *x)
{
    struct Elm *y = x->right;
    struct Elm *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxim(height(x->left), height(x->right)) + 1;
    y->height = maxim(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Elm *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Elm *insert(struct Elm *node, int key)
{
    if (node == NULL)
        return (newNode(key));

    if (key < node->x)
        node->left = insert(node->left, key);
    else if (key > node->x)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + maxim(height(node->left),
                             height(node->right));

    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->x)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->x)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->x)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->x)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

void preOrder(struct Elm *root)
{
    if (root != NULL)
    {
        printf("%d ", root->x);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    printf("\n");
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    inorder(root);
    printf("\n");
    preOrder(root);
    printf("\n");

    printf("3 Hayag : ");
    printf("%d\n", search(20));

    printf("Del 3: ");
    deleteVal(root, 30);

    inorder(root);
    printf("\n");

    printf("Del 7: ");
    deleteVal(root, 50);

    inorder(root);
    printf("\n");

    printf("Del min: ");
    root = minDelete(root);
    inorder(root);
    printf("\n");

    printf("Size 40: ");
    printf("%d\n", size(40));

    printf("Rank 40: ");
    printf("%d\n", rank(40, root));

    printf("floor 40: ");
    floor(root, 40);
    printf("%d\n", max);
    max = 0;

    printf("ceiling 20: ");
    ceiling(root, 20);
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