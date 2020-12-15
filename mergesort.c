#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ð½Ð¸Ð¹Ð»Ò¯Ò¯Ð»ÑÐ½ ÑÑ€ÑÐ¼Ð±ÑÐ»ÑÑ… Ð°Ñ€Ð³Ñ‹Ð½ Ñ†Ð°Ð°Ñˆ Ñ…ÑƒÐ²Ð°Ð°Ð³Ð´Ð°Ñ… Ñ‘ÑÐ³Ò¯Ð¹ Ñ…ÑÐ¼Ð¶ÑÑ
 */
#define CUTOFF 10
struct Student
{
    char name[20];
    int age;
    float gpa;
};
typedef struct Student Student;
/*
  a, b Ñ…Ð°ÑÐ³Ð°Ð½Ð´ Ñ…Ð°Ð´Ð³Ð°Ð»Ð°Ð³Ð´ÑÐ°Ð½ ÑÑƒÑ€Ð°Ð³Ñ‡Ð´Ñ‹Ð³ Ð½ÑÑ€ÑÑÑ€ Ð¶Ð¸ÑˆÐ¸Ñ… Ñ„ÑƒÐ½ÐºÑ†
 */
int nereer(const Student *a, const Student *b)
{
    return strcmp(a->name, b->name) < 0;
}

/*
  a, b Ñ…Ð°ÑÐ³Ð°Ð½Ð´ Ñ…Ð°Ð´Ð³Ð°Ð»Ð°Ð³Ð´ÑÐ°Ð½ ÑÑƒÑ€Ð°Ð³Ñ‡Ð´Ñ‹Ð³ Ð½Ð°ÑÐ°Ð°Ñ€ Ð½ÑŒ Ð¶Ð¸ÑˆÐ¸Ñ… Ñ„ÑƒÐ½ÐºÑ†
 */
int nasaar(const Student *a, const Student *b)
{
    /* Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¹Ð³ Ð³Ò¯Ð¹Ñ†ÑÑ */
    return a->age < b->age;
}

/*
  a, b Ñ…Ð°ÑÐ³Ð°Ð½Ð´ Ñ…Ð°Ð´Ð³Ð°Ð»Ð°Ð³Ð´ÑÐ°Ð½ ÑÑƒÑ€Ð°Ð³Ñ‡Ð´Ñ‹Ð³ Ð³Ð¾Ð»Ñ‡Ð¾Ð¾Ñ€  Ð½ÑŒ Ð¶Ð¸ÑˆÐ¸Ñ… Ñ„ÑƒÐ½ÐºÑ†
 */
int golchoor(const Student *a, const Student *b)
{
    /* Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¹Ð³ Ð³Ò¯Ð¹Ñ†ÑÑ */
    return a->gpa < b->gpa;
}

/*
  ÐžÑ€ÑƒÑƒÐ»Ð°Ð½ ÑÑ€ÑÐ¼Ð±ÑÐ»ÑÑ… Ñ„ÑƒÐ½ÐºÑ†.
  Ð–Ð¸ÑˆÐ¸Ñ… Ò¯Ð¹Ð»Ð´Ð»Ð¸Ð¹Ð³ less Ñ„ÑƒÐ½ÐºÑ†ÑÐ½ Ð·Ð°Ð°Ð³Ñ‡Ð¸Ð¹Ð³ Ð°ÑˆÐ¸Ð³Ð»Ð°Ð½ Ñ…Ð¸Ð¹Ð½Ñ.
 */

void swap(Student *A, Student *B)
{
    struct Student temp = *A;
    *A = *B;
    *B = temp;
}

void insertion_sort(Student a[],
                    int lo,
                    int hi,
                    int (*less)(const Student *, const Student *))
{
    struct Student *temp;
    for (int i = lo; i <= hi; i++)
    {

        for (int j = i + 1; j <= hi; j++)
        {

            if (less(&a[i], &a[j]))
            {
            }
            else
            {

                swap(&a[i], &a[j]);
            }
        }
    }
}

/*
  ÐÐ¸Ð¹Ð»Ò¯Ò¯Ð»ÑÑÐ½ ÑÑ€ÑÐ¼Ð±ÑÐ»ÑÑ… Ð°Ñ€Ð³Ñ‹Ð½ mege Ò¯Ð¹Ð»Ð´ÑÐ»
 */
void merge(Student a[],
           Student aux[],
           int lo,
           int mi,
           int hi,
           int (*less)(const Student *, const Student *))
{

    for (int k = lo; k <= hi; k++)
    {

        aux[k] = a[k];
    }

    int i = lo, j = mi + 1;

    for (int k = lo; k <= hi; k++)
    {

        if (i > mi)
        {

            a[k] = aux[j++];
        }
        else if (j > hi)
        {

            a[k] = aux[i++];
        }
        else if (less(&aux[j], &aux[i]))
        {

            a[k] = aux[j++];
        }
        else
        {

            a[k] = aux[i++];
        }
    }
}

/*
  ÐÐ¸Ð¹Ð»Ò¯Ò¯Ð»ÑÑÐ½ ÑÑ€ÑÐ¼Ð±ÑÐ»ÑÑ… Ñ„ÑƒÐ½ÐºÑ†.
  hi - lo <= CUTOFF Ð±Ð¾Ð» Ð¾Ñ€ÑƒÑƒÐ»Ð°Ð½ ÑÑ€ÑÐ¼Ð±ÑÐ»ÑÑ… Ð°Ñ€Ð³Ñ‹Ð³ Ñ…ÑÑ€ÑÐ³Ð»ÑÐ½Ñ.
  Ð–Ð¸ÑˆÐ¸Ñ… Ò¯Ð¹Ð»Ð´Ð»Ð¸Ð¹Ð³ less Ñ„ÑƒÐ½ÐºÑ†ÑÐ½ Ð·Ð°Ð°Ð³Ñ‡Ð¸Ð¹Ð³ Ð°ÑˆÐ¸Ð³Ð»Ð°Ð½ Ñ…Ð¸Ð¹Ð½Ñ.
 */
void mergesort(Student a[],
               Student aux[],
               int lo,
               int hi,
               int (*less)(const Student *, const Student *))
{

    if (hi - lo <= CUTOFF)
    {

        insertion_sort(a, lo, hi, less);
    }
    else if (hi > lo)
    {

        int mi = lo + (hi - lo) / 2;
        mergesort(a, aux, lo, mi, less);
        mergesort(a, aux, mi + 1, hi, less);
        merge(a, aux, lo, mi, hi, less);
    }
}

int main()
{
    FILE *fin = NULL;
    fin = fopen("info2.txt", "r");
    if (!fin)
    {
        printf("info.txt file error!\n");
        exit(-1);
    }
    int i, n;
    fscanf(fin, "%d", &n);
    Student *a, *aux;
    a = (Student *)malloc(sizeof(Student) * n);
    aux = (Student *)malloc(sizeof(Student) * n);
    for (i = 0; i < n; i++)
    {
        fscanf(fin, "%s%d%f", a[i].name, &a[i].age, &a[i].gpa);
        aux[i] = a[i];
    }
    fclose(fin);

    for (i = 0; i < n; i++)
        printf("%s %d %f\n", a[i].name, a[i].age, a[i].gpa);

    int t;
    while (1)
    {
        printf("1. Nereer erembelex, 2. Nasaar, 3. Gochoor\n");
        scanf("%d", &t);
        switch (t)
        {
        case 1:
            mergesort(a, aux, 0, n - 1, nereer);
            break;
        case 2:
            mergesort(a, aux, 0, n - 1, nasaar);
            break;
        case 3:
            mergesort(a, aux, 0, n - 1, golchoor);
            break;
        default:
            printf("Buruu songolt!");
            break;
        }
        for (i = 0; i < n; i++)
            printf("%s %d %f\n", a[i].name, a[i].age, a[i].gpa);
    }
    return 0;
}