// Queue

#include <stdio.h>
#include <stdlib.h>
struct Elm
{
    int x;
    struct Elm *next;
};

struct Elm *head, *tail;
int error = 0;
const char error_msg[][50] = {
    "",
    "Queue duuren!",
    "Queue xooson!"};

void init()
{
    head = tail = NULL;
}

/* p-ийн зааж буй Queue хоосон бол 1 үгүй бол 0-ийг буцаана */
int empty()
{
    /* Энд хоосон эсэхийг шалгах үйлдлийг хийнэ */
}

/* p-ийн зааж буй Queue-д x утгыг хийнэ */
void push_back(int x)
{
    /* Энд оруулах үйлдлийг хийнэ үү */

    struct Elm *p = malloc(sizeof(struct Elm));

    p->x = x;
    p->next = NULL;
    if (head == NULL)
        head = tail = p;
    else
    {
        tail->next = p;
        tail = p;
    }
}

/* p-ийн зааж буй Queue-с гарган буцаана */
int pop_front()
{
    /* Энд гаргах үйлдлийг хийнэ үү */
    struct Elm *p;
    int x;

    p = head;
    x = head->x;

    head = head->next;
    free(p);

    return x;
}

/* p-ийн зааж буй Queue-н утгуудыг хэвлэнэ */
void print()
{
    /* Энд хэвлэх үйлдлийг хийнэ үү */
    struct Elm *p;
    for (p = head; p != NULL; p = p->next)
        printf("%d\n", p->x);
}

/* p-ийн зааж буй Queue-н хамгийн эхний элементийн утгыг буцаана.
   Гаргах үйлдэл хийхгүй.
 */
int front()
{
    return head->x;
}
/* p-ийн зааж буй Queue-н хамгийн сүүлийн элементийн утгыг буцаана.
   Queue-д өөрчлөлт оруулахгүй.
 */
int back()
{
    return tail->x;
}
/* p-ийн зааж буй Queue-д хэдэн элемент байгааг буцаана.
   Queue-д өөрчлөлт оруулахгүй.
 */
int size()
{
    struct Elm *p;

    int count = 0;

    for (p = head; p != NULL; p = p->next)
        count++;

    return count;
}

void release()
{
    while (empty() == 0)
        pop_front();
}

int main()
{
    /* Queue эхлүүлэх */
    init();
    int t, x;

    while (1)
    {
        printf("1: push_back, 2: pop_front, 3: print, 4: empty, 5: front,"
               "6: back, 7: size, 8: exit\n");
        scanf("%d", &t);
        error = 0;

        switch (t)
        {
        case 1:
            scanf("%d", &x);
            push_back(x);
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga orloo\n", x);
            break;
        case 2:
            x = pop_front();
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
                printf("Queue xooson\n");
            else
                printf("Queue xooson bish\n");
            break;
        case 5:
            x = front();
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga xamgiin exend bna\n", x);
            break;
        case 6:
            x = back();
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga xamgiin suuld bna\n", x);
            break;
        case 7:
            x = size();
            printf("Queue-d %d shirxeg element bna\n", x);
            break;
        default:
            exit(0);
        }
    }
    /* Queue-ийн эзэмшсэн нөөцийг чөлөөлөх */
    release();
    return 0;
}
