//list
#include <stdio.h>
#include <stdlib.h>
struct Elm
{
    int x;
    struct Elm *next;
    struct Elm *prev;
};
struct Elm *head;
struct Elm *tail;
int error = 0;
const char error_msg[][50] = {
    "",
    "List duuren!",
    "List xooson!",
    "Bairlald oruulax bolomjgui!",
    "Bairlaas gargax bolomjgui!"};

void init()
{
    head = NULL;
    tail = NULL;
}

/* p-ийн зааж буй List хоосон бол 1 үгүй бол 0-ийг буцаана */
int empty()
{
    /* Энд хоосон эсэхийг шалгах үйлдлийг хийнэ */
    if (head == NULL)
        return 1;
    else
        return 0;
}

/* p-ийн зааж буй List-д x утгыг төгсгөлд хийнэ */
void push_back(int x)
{
    /* Энд оруулах үйлдлийг хийнэ үү */
    struct Elm *p = malloc(sizeof(struct Elm));

    if (p == NULL)
    {
        error = 2;
        return;
    }

    p->x = x;
    p->prev = tail;
    p->next = NULL;

    if (head == NULL)
        head = tail = p;
    else
    {
        tail->next = p;
        tail = p;
    }
}

/* p-ийн зааж буй List-д x утгыг эхэнд  хийнэ */
void push_front(int x)
{
    /* Энд оруулах үйлдлийг хийнэ үү */
    struct Elm *p = malloc(sizeof(struct Elm));

    if (p == NULL)
    {
        error = 2;
        return;
    }

    p->x = x;
    p->prev = NULL;

    if (head == NULL)
    {
        head = tail = p;
        p->next = NULL;
    }
    else
    {
        head->prev = p;
        p->next = head;
        head = p;
    }
}

/* p-ийн зааж буй List-д x утгыг pos байрлалд хийнэ
   pos болон түүнээс хойшхи элементүүд нэг байрлал ухарна.
 */
void insert(int x, int pos)
{
    /* Энд оруулах үйлдлийг хийнэ үү */

    int count = 0;

    struct Elm *p, *d;

    for (p = head; p != NULL; p = p->next)
    {
        count++;
        if (count == pos)
        {

            d = malloc(sizeof(struct Elm));

            if (d == NULL)
            {
                error = 2;
                return;
            }

            d->prev = p->prev;
            p->prev = d;
            d->next = p;
            d->x = x;
            d->prev->next = d;
            return;
        }
    }

    error = 4;
}

/* p-ийн зааж буй List-н эхлэлээс гарган буцаана */
int pop_front()
{
    /* Энд гаргах үйлдлийг хийнэ үү */
    struct Elm *p;
    int x;

    p = head;
    x = head->x;

    if (head == tail)
    {

        free(p);
        head = tail = NULL;
        return x;
    }

    head = head->next;
    head->prev = NULL;
    free(p);

    return x;
}

/* p-ийн зааж буй List-н төгсгөлөөс гарган буцаана */
int pop_back()
{
    /* Энд гаргах үйлдлийг хийнэ үү */
    int x;

    struct ELm *p;

    p = tail;
    x = tail->x;

    if (head == tail)
    {

        free(p);
        head = tail = NULL;
        return x;
    }

    tail = tail->prev;
    tail->next = NULL;

    free(p);

    return x;
}

/* p-ийн зааж буй List-н pos байралаас гарган буцаана.
   pos болон түүнээс хойшхи элементүүд нэг байрлал урагшилна.
 */
int erase(int pos)
{
    /* Энд гаргах үйлдлийг хийнэ үү */

    int count = 0, x;

    struct Elm *p, *d;

    for (p = head; p != NULL; p = p->next)
    {
        count++;
        if (count == pos)
        {

            x = p->x;

            p->prev->next = p->next;
            free(p);

            return x;
        }
    }

    error = 5;
}

/* p-ийн зааж буй List-н утгуудыг хэвлэнэ */
void print()
{
    /* Энд хэвлэх үйлдлийг хийнэ үү */
    struct Elm *p;
    for (p = head; p != NULL; p = p->next)
        printf("%d\n", p->x);
}

/* p-ийн зааж буй List-н хамгийн эхний элементийн утгыг буцаана.
   Гаргах үйлдэл хийхгүй.
 */
int front()
{
    return head->x;
}
/* p-ийн зааж буй List-н хамгийн сүүлийн элементийн утгыг буцаана.
   List-д өөрчлөлт оруулахгүй.
 */
int back()
{
    return tail->x;
}
/* p-ийн зааж буй List-д хэдэн элемент байгааг буцаана.
   List-д өөрчлөлт оруулахгүй.
 */
int size()
{
    struct Elm *p;

    int count = 0;

    for (p = head; p != NULL; p = p->next)
        count++;

    return count;
}

/* p-ийн зааж буй List-с x тоог хайн олдсон байрлалаыг буцаана.
   Олдохгүй бол -1 утгыг буцаана.
 */
int search(int x)
{
    struct Elm *p;

    int count = 0;

    for (p = head; p != NULL; p = p->next)
    {
        count++;
        if (p->x == x)
            break;
    }

    return count;
}

void release()
{
    while (empty() == 0)
        pop_front();
}

int main()
{
    /* List эхлүүлэх */
    init();
    int t, x, pos;

    while (1)
    {
        printf("1: push_front, 2: push_back, 3: insert, 4: pop_front, 5: pop_back,"
               "6: erase, 7: front, 8: back, 9: size, 10: empty, 11: search, 12: print,"
               "13: exit\n");
        scanf("%d", &t);
        error = 0;

        switch (t)
        {
        case 1:
            printf("Exend oruulax utga: ");
            scanf("%d", &x);
            push_front(x);
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga exend orloo\n", x);
            break;
        case 2:
            printf("Suuld oruulax utga: ");
            scanf("%d", &x);
            push_back(x);
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga suuld orloo\n", x);

            break;
        case 3:
            printf("Oruulax utga: ");
            scanf("%d", &x);
            printf("Oruulax bairlal: ");
            scanf("%d", &pos);
            insert(x, pos);
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga %d-d orloo\n", x, pos);

            break;
        case 4:
            x = pop_front();
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utgiig exlelees gargalaa\n", x);
            break;
        case 5:
            x = pop_back();
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utgiig suulees gargalaa\n", x);
            break;
        case 6:
            printf("gargax bairlal: ");
            scanf("%d", &pos);
            x = erase(pos);
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utgiig %d bairlalaas gargalaa\n", x, pos);
            break;
        case 7:
            x = front();
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga xamgiin exend bna\n", x);
            break;
        case 8:
            x = back();
            if (error)
                printf("Aldaa: %s\n", error_msg[error]);
            else
                printf("%d utga xamgiin suuld bna\n", x);
            break;
        case 9:
            x = size();
            printf("List-d %d shirxeg element bna\n", x);
            break;
        case 10:
            if (empty())
                printf("List xooson\n");
            else
                printf("List xooson bish\n");
            break;
        case 11:
            printf("Xaix toog oruul: ");
            scanf("%d", &x);
            pos = search(x);
            if (pos == -1)
                printf("%d utga oldsongui\n", x);
            else
                printf("%d utga %d bairlald oldloo\n", x, pos);
            break;
        case 12:
            print();
            break;
        default:
            exit(0);
        }
    }
    /* List-ийн эзэмшсэн нөөцийг чөлөөлөх */
    release();
    return 0;
}
