#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);  

        int raz = l;
        int cur = 0;
        int mas = 0;

        while (raz <= r) {
            raz += cur;
            cur++;
        }

        printf("%d\n", cur - 1);
    }

    return 0;
}