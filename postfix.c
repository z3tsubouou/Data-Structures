// postfix

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LIM 50

typedef struct stack
{
    int val[LIM];
    int top;
} stack;

int precedence(char);
void init(stack *);
int empty(stack *);
int full(stack *);
int pop(stack *);
void push(stack *, int);
int top(stack *);
int pos_calc(char pos[]);
void inf_to_pos(char inf[], char pos[]);

void inf_to_pos(char inf[], char pos[])
{
    stack s;
    char x, token;
    int i, j;
    init(&s);
    j = 0;

    for (i = 0; inf[i] != '\0'; i++)
    {
        token = inf[i];
        if (isalnum(token))
            pos[j++] = token;
        else if (token == '(')
            push(&s, '(');
        else if (token == ')')
            while ((x = pop(&s)) != '(')
                pos[j++] = x;
        else
        {
            while (precedence(token) <= precedence(top(&s)) && !empty(&s))
            {
                x = pop(&s);
                pos[j++] = x;
            }
            push(&s, token);
        }
    }

    while (!empty(&s))
    {
        x = pop(&s);
        pos[j++] = x;
    }

    pos[j] = '\0';
}

int precedence(char x)
{
    if (x == '(')
        return (0);
    if (x == '+' || x == '-')
        return (1);
    if (x == '*' || x == '/' || x == '%')
        return (2);

    return (3);
}

void init(stack *s)
{
    s->top = -1;
}

int empty(stack *s)
{
    if (s->top == -1)
        return (1);

    return (0);
}

int full(stack *s)
{
    if (s->top == LIM - 1)
        return (1);

    return (0);
}

void push(stack *s, int x)
{
    s->top = s->top + 1;
    s->val[s->top] = x;
}

int pop(stack *s)
{
    int x;
    x = s->val[s->top];
    s->top = s->top - 1;
    return (x);
}

int top(stack *p)
{
    return (p->val[p->top]);
}

int pos_calc(char pos[])
{
    char *e = pos;
    stack s;
    int n1, n2, n3, num;
    init(&s);

    while (*e != '\0')
    {
        if (isdigit(*e))
        {
            num = *e - 48;
            push(&s, num);
        }
        else
        {
            n1 = pop(&s);
            n2 = pop(&s);
            switch (*e)
            {
            case '+':
            {
                n3 = n1 + n2;
                break;
            }
            case '-':
            {
                n3 = n2 - n1;
                break;
            }
            case '*':
            {
                n3 = n1 * n2;
                break;
            }
            case '/':
            {
                n3 = n2 / n1;
                break;
            }
            }
            push(&s, n3);
        }
        e++;
    }

    int d = pop(&s);

    return d;
}

int main()
{
    char inf[30], pos[30];
    gets(inf);

    int i, k;

    for (i = 0; inf[i]; i++)
    {
        inf[i] = inf[i + k];

        if (inf[i] == ' ' || inf[i] == '\t')
        {
            k++;
            i--;
        }
    }

    inf_to_pos(inf, pos);
    printf("%s\n", pos);
    printf("%d\n", pos_calc(pos));
}