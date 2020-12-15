#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct message
{
    char code[30];
    int priority;
};

struct Tree
{
    int len;
    int size;
    message *dat;
};

void init(struct Tree *p, int n)
{
    p->len = n;
    p->size = 0;
    p->dat = (message *)malloc(sizeof(message) * n);
}

void release(struct Tree *p)
{
    free(p->dat);
    p->dat = NULL;
}

void swap(message *a, message *b)
{
    struct message temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swim(struct Tree *p, int k)
{
    while (k >= 0 && p->dat[k / 2].priority > p->dat[k].priority)
    {
        swap(&p->dat[k], &p->dat[k / 2]);
        k = k / 2;
    }
}

void sink(struct Tree *p, int k)
{
    while (2 * k + 1 < p->size)
    {
        int j = 2 * k;
        if (j < p->size - 1 && p->dat[j].priority > p->dat[j + 1].priority)
            j++;
        if (!p->dat[k].priority > p->dat[j].priority)
            break;
        swap(&p->dat[k], &p->dat[j]);
        k = j;
    }
}

message q_get(struct Tree *p)
{
    message max = p->dat[0];
    swap(&p->dat[0], &p->dat[p->size - 1]);
    p->size--;
    sink(p, 0);

    return max;
}

void q_put(struct Tree *p, message a)
{
    int i = p->size;
    p->dat[p->size] = a;
    p->size++;
    swim(p, i);
}

void preorder(struct Tree *p, int idx)
{
    if (idx < p->size)
    {
        printf("%d ", p->dat[idx].priority);
        preorder(p, idx + 1);
    }
}

int main()
{

    FILE *fin = NULL;
    FILE *fout = fopen("output_eg.txt", "w+");
    fin = fopen("input.txt", "r");
    if (!fin)
    {
        printf("input.txt file error!\n");
        exit(-1);
    }
    struct message ms;
    struct Tree tr;
    init(&tr, 60000);
    int i, n;
    char method[4];
    fscanf(fin, "%d", &n);

    for (i = 0; i < n; i++)
    {
        fscanf(fin, "%s", &method);
        if (strcmp("GET", method) == 0)
        {

            fprintf(fout, "%s\n", q_get(&tr).code);
        }
        else
        {
            fscanf(fin, "%s%d", &ms.code, &ms.priority);
            q_put(&tr, ms);
        }
    }
    fclose(fin);
    fclose(fout);

    release(&tr);
    return 0;
}
