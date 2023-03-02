#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100005

/**
 * @brief function to check if a character is a valid opening bracket
 * 
 * @param c 
 * @return bool: True or False
 */
bool is_opening(char c) {
    return (c == '(' || c == '[' || c == '{');
}

/**
 * @brief function to check if a character is a valid closing bracket
 * 
 * @param c 
 * @return bool: True or False
 */
bool is_closing(char c) {
    return (c == ')' || c == ']' || c == '}');
}

/**
 * @brief function to check if a pair of brackets is valid
 * 
 * @param a 
 * @param b 
 * @return bool: True or False
 */
bool is_valid_pair(char a, char b) {
    if (a == '(' && b == ')') return true;
    if (a == '[' && b == ']') return true;
    if (a == '{' && b == '}') return true;
    return false;
}

/**
 * @brief function to check if a string of brackets is valid
 * 
 * @param str 
 * @return bool: True or False
 */
bool is_valid_sequence(char *str) {
    int len = strlen(str);
    char stack[MAX_LENGTH];
    int top = -1;
    for (int i = 0; i < len; i++) {
        if (is_opening(str[i])) {
            stack[++top] = str[i];
        } else if (is_closing(str[i])) {
            if (top == -1 || !is_valid_pair(stack[top], str[i])) {
                return false;
            }
            top--;
        }
    }
    return (top == -1);
}

int main() {
    char str[MAX_LENGTH];
    if (scanf("%s", str) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (is_valid_sequence(str)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
