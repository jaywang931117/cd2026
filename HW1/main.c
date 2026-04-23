#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_letter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int is_digit(char ch) {
    return (ch >= '0' && ch <= '9');
}

int is_whitespace(char ch) {
    return (ch == ' ' || ch == '\n' || ch == '\t');
}

int main() {
    int ch, next_ch, i;
    char token[100];

    FILE *fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file!\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        if (is_whitespace((char)ch)) continue;

        /* ===== ID / KEYWORD ===== */
        if (is_letter((char)ch)) {
            i = 0;
            token[i++] = (char)ch;

            while ((next_ch = fgetc(fp)) != EOF) {
                if (is_letter((char)next_ch) || is_digit((char)next_ch) || next_ch == '_') {
                    token[i++] = (char)next_ch;
                } else {
                    ungetc(next_ch, fp);
                    break;
                }
            }
            token[i] = '\0';

            if (strcmp(token, "int") == 0)
                printf("int: TYPE_TOKEN\n");
            else if (strcmp(token, "main") == 0)
                printf("main: MAIN_TOKEN\n");
            else if (strcmp(token, "if") == 0)
                printf("if: IF_TOKEN\n");
            else if (strcmp(token, "else") == 0)
                printf("else: ELSE_TOKEN\n");
            else if (strcmp(token, "while") == 0)
                printf("while: WHILE_TOKEN\n");
            else
                printf("%s: ID_TOKEN\n", token);
        }

        /* ===== NUMBER ===== */
        else if (is_digit((char)ch)) {
            i = 0;
            token[i++] = (char)ch;

            while ((next_ch = fgetc(fp)) != EOF) {
                if (is_digit((char)next_ch)) {
                    token[i++] = (char)next_ch;
                } else {
                    ungetc(next_ch, fp);
                    break;
                }
            }
            token[i] = '\0';
            printf("%s: LITERAL_TOKEN\n", token);
        }

        /* ===== SYMBOL / OPERATOR ===== */
        else {
            if (ch == '(') {
                printf("(: LEFTPAREN_TOKEN\n");
            }
            else if (ch == ')') {
                printf("): REFTPAREN_TOKEN\n");   // ← 改成老師版本
            }
            else if (ch == '{') {
                printf("{: LEFTBRACE_TOKEN\n");
            }
            else if (ch == '}') {
                printf("}: REFTBRACE_TOKEN\n");   // ← 改成老師版本
            }
            else if (ch == ';') {
                printf(";: SEMICOLON_TOKEN\n");
            }
            else if (ch == '+') {
                printf("+: PLUS_TOKEN\n");
            }
            else if (ch == '-') {
                printf("-: MINUS_TOKEN\n");
            }
            else if (ch == '=') {
                next_ch = fgetc(fp);
                if (next_ch == '=') {
                    printf("==: EQUAL_TOKEN\n");
                } else {
                    printf("=: ASSIGN_TOKEN\n");
                    if (next_ch != EOF) ungetc(next_ch, fp);
                }
            }
            else if (ch == '>') {
                next_ch = fgetc(fp);
                if (next_ch == '=') {
                    printf(">=: GREATEREQUAL_TOKEN\n");
                } else {
                    printf(">: GREATER_TOKEN\n");
                    if (next_ch != EOF) ungetc(next_ch, fp);
                }
            }
            else if (ch == '<') {
                next_ch = fgetc(fp);
                if (next_ch == '=') {
                    printf("<=: LESSEQUAL_TOKEN\n");
                } else {
                    printf("<: LESS_TOKEN\n");
                    if (next_ch != EOF) ungetc(next_ch, fp);
                }
            }
        }
    }

    fclose(fp);
    return 0;
}
