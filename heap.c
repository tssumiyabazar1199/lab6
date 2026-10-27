#include "DS.h"

static void swim(Heap *p, int k);
static void sink(Heap *p, int k);

int less(const Msg *a, const Msg *b)
{
        if (a->priority != b->priority) {
                return a->priority < b->priority;
        }
        return a->time < b->time;
}

void insert(Heap *p, const Msg x)
{
        if (p->h_len >= 100000) return;
        
        p->h_arr[++p->h_len] = x;
        swim(p, p->h_len);
}

static void swim(Heap *p, int k)
{
        while (k > 1 && less(&p->h_arr[k], &p->h_arr[k / 2])) {
                Msg temp = p->h_arr[k];
                p->h_arr[k] = p->h_arr[k / 2];
                p->h_arr[k / 2] = temp;
                k = k / 2;
        }
}

static void sink(Heap *p, int k)
{
        while (2 * k <= p->h_len) {
                int j = 2 * k;
                if (j < p->h_len && less(&p->h_arr[j + 1], &p->h_arr[j])) {
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
        if (p->h_len <= 0) {
                Msg empty = {0};
                return empty;
        }
        Msg min = p->h_arr[1];
        p->h_arr[1] = p->h_arr[p->h_len--];
        sink(p, 1);
        return min;
}