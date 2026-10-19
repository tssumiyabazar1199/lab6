#include "DS.h"

static void swim(Heap *p, int k);
static void sink(Heap *p, int k);

/* 
  b нь илүү чухал бол 1, бусад үед 0-ийг буцаана (a < b үйлдэл).
  - Priority бага бол илүү чухал.
  - Priority тэнцүү бол Time бага (түрүүлж орж ирсэн) нь илүү чухал.
*/
int less(const Msg *a, const Msg *b)
{
    if (a->priority != b->priority) {
        return b->priority < a->priority;
    }
    return b->time < a->time;
}

/* Heap-д шинэ элемент оруулах */
void insert(Heap *p, const Msg x)
{
    if (p->h_len < 100000) {
        p->h_len++;
        p->h_arr[p->h_len] = x;
        swim(p, p->h_len);
    }
}

/* Элементийг дээш нь дээшлүүлэх (Swim) */
static void swim(Heap *p, int k)
{
    while (k > 1 && less(&p->h_arr[k / 2], &p->h_arr[k])) {
        Msg temp = p->h_arr[k];
        p->h_arr[k] = p->h_arr[k / 2];
        p->h_arr[k / 2] = temp;
        k = k / 2;
    }
}

/* Элементийг доош нь доошлуулах (Sink) */
static void sink(Heap *p, int k)
{
    while (2 * k <= p->h_len) {
        int j = 2 * k;
        // Хэрэв баруун хүүхэд нь илүү чухал байвал баруун хүүхдийг сонгоно
        if (j < p->h_len && less(&p->h_arr[j], &p->h_arr[j + 1])) {
            j++;
        }
        // Эцэг элемент нь хүүхдээсээ илүү чухал эсвэл тэнцүү байвал зогсоно
        if (!less(&p->h_arr[k], &p->h_arr[j])) {
            break;
        }
        Msg temp = p->h_arr[k];
        p->h_arr[k] = p->h_arr[j];
        p->h_arr[j] = temp;
        k = j;
    }
}

/* Оройн (хамгийн чухал) элементийг гаргаж аваад буцаах */
Msg delMin(Heap *p)
{
    Msg minVal = p->h_arr[1];
    p->h_arr[1] = p->h_arr[p->h_len];
    p->h_len--;
    sink(p, 1);
    return minVal;
}