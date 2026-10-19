#include "DS.h"

static void swim(Heap *p, int);
static void sink(Heap *p, int);

int less(const Msg *a, const Msg *b)
{
    if (a->priority != b->priority) {
        return a->priority < b->priority;
    }
    return a->time < b->time;
}

void insert(Heap *p, const Msg x)
{
    if (h_len <= 100000) {
        p->h_arr[h_len++] = x;
        swim(p, h_len);
    }
}

static void swim(Heap *p, int k)
{
    while (k >= 1 && less(&p->h_arr[k], &p->h_arr[k / 2])) {
        Msg temp = p->h_arr[k];
        p->h_arr[k] = p->h_arr[k / 2];
        p->h_arr[k / 2] = temp;
        k = k / 2;
    }
}

static void sink(Heap *p, int k)
{
    while (2 * k <= h_len) {
        int j = 2 * k;
        if (j <= h_len && less(&p->h_arr[j + 1], &p->h_arr[j])) {
            j++;
        }
        if (!less(&p->h_arr[j], &p->h_arr[k])) {
            break;
        }
        Msg temp = p->h_arr[k];
        p->h_arr[k] = p->h_arr[j];
        p->h_arr[j] = temp;
        k = j;
    }
}

Msg delMin(Heap *p)
{
    Msg minVal = p->h_arr[0];
    p->h_arr[1] = p->h_arr[h_len];
    sink(p, 1);
    return minVal;
}