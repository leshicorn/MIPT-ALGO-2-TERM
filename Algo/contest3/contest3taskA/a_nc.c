#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 64
#define PRIME 997

/**
 * @brief функция, считающая значение h. Она равна d^(m-1), где d - размер алфавита, а m - длина шаблона. 
 * 
 * @param h 
 * @param m 
 * @return int 
 */
int h_hash(int h, int m) {
    for (int i = 0; i < m - 1; i++) {
        h = (h * ALPHABET_SIZE) % PRIME;
    }
    return h;
}

/**
 * @brief функция, которая ищет все вхождения pattern в text
 * 
 * @param pattern - строка, вхождения которой ищутся в text
 * @param text - текст, в котором ищутся вхождения
 */
void search(char* pattern, char* text)
{
    int m = strlen(pattern);
    int n = strlen(text);
    int i, j;
    int p_hash = 0; 
    int t_hash = 0; 
    int h = 1;

    h = h_hash(h, m);

    for (i = 0; i < m; i++) {
        p_hash = (ALPHABET_SIZE * p_hash + pattern[i]) % PRIME;
        t_hash = (ALPHABET_SIZE * t_hash + text[i]) % PRIME;
    }

    for (i = 0; i <= n - m; i++) {
        if (p_hash == t_hash) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                printf("%d\n", i);
        }

        if (i < n - m) {
            t_hash = (ALPHABET_SIZE * (t_hash - text[i] * h) + text[i+m]) % PRIME;

            if (t_hash < 0)
                t_hash = (t_hash + PRIME);
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