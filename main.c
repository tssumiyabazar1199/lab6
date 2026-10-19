#include <stdio.h>
#include <string.h>
#include "DS_2.h"

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Heap hp;
    hp.heap.len = 0; // Эсвэл h_len = 0;
    
    int time_counter = 0;

    for (int i = 0; i < n; i++) {
        char cmd[10];
        scanf("%s", cmd);

        if (strcmp(cmd, "PUT") == 0) {
            Msg m;
            scanf("%s %d", m.text, &m.priority);
            m.time = ++time_counter; // Орсон дарааллыг хадгалах хугацаа
            insert(&hp, m);
        } else if (strcmp(cmd, "GET") == 0) {
            Msg m = delMin(&hp);
            printf("%s\n", m.text);
        }
    }

    return 0;
}