#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define d 64 // размер алфавита
#define prime 997 // простое число

int h_hash(int h, int m) {
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % prime;
    }
    return h;
}

void search(char pattern[], char text[])
{
    int m = strlen(pattern);
    int n = strlen(text);
    int i, j;
    int p_hash = 0; 
    int t_hash = 0; 
    int h = 1;

    // вычисляем значение h = d^(m-1) % prime
    h = h_hash(h, m);

    // вычисляем hash для pattern и text
    for (i = 0; i < m; i++) {
        p_hash = (d * p_hash + pattern[i]) % prime;
        t_hash = (d * t_hash + text[i]) % prime;
    }

    // проверяем на совпадение хеш-значений и символов
    for (i = 0; i <= n - m; i++) {
        if (p_hash == t_hash) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                printf("%d\n", i);
        }

        // вычисляем новое хеш-значение для text
        if (i < n - m) {
            t_hash = (d * (t_hash - text[i] * h) + text[i+m]) % prime;

            // если получилось отрицательное значение, то добавляем prime
            if (t_hash < 0)
                t_hash = (t_hash + prime);
        }
    }
}

int main()
{
    char* text = malloc(sizeof(char) * 5 * 10000);
    char* pattern = malloc(sizeof(char) * 5 * 10000);
    scanf("%s", text);
    scanf("%s", pattern);

    search(pattern, text);

    return 0;
}