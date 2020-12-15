//stack
#include <stdio.h>
#include <stdlib.h>

struct Elm
{
    int x;
    struct Elm *next;
};
struct Elm *top;
int error = 0;
const char error_msg[][50] = {
    "",
    "Stack duuren!",
    "Stack xooson!"};

void init()
{
    top = NULL;
}

/* p-Ð¸Ð¹Ð½ Ð·Ð°Ð°Ð¶ Ð±ÑƒÐ¹ Stack Ñ…Ð¾Ð¾ÑÐ¾Ð½ Ð±Ð¾Ð» 1 Ò¯Ð³Ò¯Ð¹ Ð±Ð¾Ð» 0-Ð¸Ð¹Ð³ Ð±ÑƒÑ†Ð°Ð°Ð½Ð° */
int empty()
{
    /* Ð­Ð½Ð´ Ñ…Ð¾Ð¾ÑÐ¾Ð½ ÑÑÑÑ…Ð¸Ð¹Ð³ ÑˆÐ°Ð»Ð³Ð°Ñ… Ò¯Ð¹Ð»Ð´Ð»Ð¸Ð¹Ð³ Ñ…Ð¸Ð¹Ð½Ñ */
    if (top == NULL)
        error = 2;
}

/* p-Ð¸Ð¹Ð½ Ð·Ð°Ð°Ð¶ Ð±ÑƒÐ¹ Stack-Ð´ x ÑƒÑ‚Ð³Ñ‹Ð³ Ñ…Ð¸Ð¹Ð½Ñ */
void push(int x)
{
    /* Ð­Ð½Ð´ Ð¾Ñ€ÑƒÑƒÐ»Ð°Ñ… Ò¯Ð¹Ð»Ð´Ð»Ð¸Ð¹Ð³ Ñ…Ð¸Ð¹Ð½Ñ Ò¯Ò¯ */
    struct Elm *p = malloc(sizeof(struct Elm));

    p->x = x;
    p->next = top;
    top = p;
}

/* p-Ð¸Ð¹Ð½ Ð·Ð°Ð°Ð¶ Ð±ÑƒÐ¹ Stack-Ñ Ð³Ð°Ñ€Ð³Ð°Ð½ Ð±ÑƒÑ†Ð°Ð°Ð½Ð° */
int pop()
{
    /* Ð­Ð½Ð´ Ð³Ð°Ñ€Ð³Ð°Ñ… Ò¯Ð¹Ð»Ð´Ð»Ð¸Ð¹Ð³ Ñ…Ð¸Ð¹Ð½Ñ Ò¯Ò¯ */

    int x;

    struct ELm *p;

    p = top;
    x = top->x;

    top = top->next;
    free(p);

    return x;
}

/* p-Ð¸Ð¹Ð½ Ð·Ð°Ð°Ð¶ Ð±ÑƒÐ¹ Stack-Ð½ ÑƒÑ‚Ð³ÑƒÑƒÐ´Ñ‹Ð³ Ñ…ÑÐ²Ð»ÑÐ½Ñ */
void print()
{
    /* Ð­Ð½Ð´ Ñ…ÑÐ²Ð»ÑÑ… Ò¯Ð¹Ð»Ð´Ð»Ð¸Ð¹Ð³ Ñ…Ð¸Ð¹Ð½Ñ Ò¯Ò¯ */
    struct Elm *p = top;

    for (p = top; p != NULL; p = p->next)
        printf("%d\n", p->x);
}

void release()
{
    while (empty())
        pop();
}

int main()
{
    /* Stack ÑÑ…Ð»Ò¯Ò¯Ð»ÑÑ… */
    init();
    int t, x;

    while (1)
    {
        printf("1: push, 2: pop, 3: print, 4: empty, 5: exit\n");
        scanf("%d", &t);
        error = 0;

        switch (t)
        {
        case 1:
            scanf("%d", &x);
            push(x);
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga orloo\n", x);
            break;
        case 2:
            x = pop();
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga garlaa\n", x);
            break;
        case 3:
            print();
            break;
        case 4:
            if (empty())
                printf("Stack xooson\n");
            else
                printf("Stack xooson bish\n");
            break;
        default:
            exit(0);
        }
    }
    /* Stack-Ð¸Ð¹Ð½ ÑÐ·ÑÐ¼ÑˆÑÑÐ½ Ð½Ó©Ó©Ñ†Ð¸Ð¹Ð³ Ñ‡Ó©Ð»Ó©Ó©Ð»Ó©Ñ… */
    release();
    return 0;
}