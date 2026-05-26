#include <stdio.h>
#include <string.h>

#define NUM_TOKEN 1
#define PLUS_TOKEN 2
#define LEFTPAREN_TOKEN 3
#define REFTPAREN_TOKEN 4
#define EOF_TOKEN 5
#define ERROR_TOKEN 6

char input[1000];
char lexeme[100];
int pos = 0;
int token;

int is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

int is_whitespace(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t';
}

int scanner() {
    int i = 0;

    while (is_whitespace(input[pos])) {
        pos++;
    }

    if (input[pos] == '\0') {
        strcpy(lexeme, "EOF");
        return EOF_TOKEN;
    }

    if (is_digit(input[pos])) {
        while (is_digit(input[pos])) {
            lexeme[i] = input[pos];
            i++;
            pos++;
        }
        lexeme[i] = '\0';
        return NUM_TOKEN;
    }

    if (input[pos] == '+') {
        lexeme[0] = input[pos];
        lexeme[1] = '\0';
        pos++;
        return PLUS_TOKEN;
    }

    if (input[pos] == '(') {
        lexeme[0] = input[pos];
        lexeme[1] = '\0';
        pos++;
        return LEFTPAREN_TOKEN;
    }

    if (input[pos] == ')') {
        lexeme[0] = input[pos];
        lexeme[1] = '\0';
        pos++;
        return REFTPAREN_TOKEN;
    }

    lexeme[0] = input[pos];
    lexeme[1] = '\0';
    pos++;
    return ERROR_TOKEN;
}

void nextToken() {
    token = scanner();
}

void parse_error() {
    printf("Parse Error\n");
}

int parse_S();
int parse_S_prime();
int parse_E();

int parse_S() {
    printf("S -> E S'\n");

    if (token == NUM_TOKEN || token == LEFTPAREN_TOKEN) {
        if (!parse_E()) {
            return 0;
        }

        if (!parse_S_prime()) {
            return 0;
        }

        return 1;
    }

    return 0;
}

int parse_S_prime() {
    if (token == PLUS_TOKEN) {
        printf("S' -> + S\n");

        nextToken();

        if (!parse_S()) {
            return 0;
        }

        return 1;
    }

    if (token == REFTPAREN_TOKEN || token == EOF_TOKEN) {
        printf("S' -> epsilon\n");
        return 1;
    }

    return 0;
}

int parse_E() {
    if (token == NUM_TOKEN) {
        printf("E -> num\n");
        printf("%s\n", lexeme);

        nextToken();
        return 1;
    }

    if (token == LEFTPAREN_TOKEN) {
        printf("E -> ( S )\n");

        nextToken();

        if (!parse_S()) {
            return 0;
        }

        if (token != REFTPAREN_TOKEN) {
            return 0;
        }

        nextToken();
        return 1;
    }

    return 0;
}

int main() {
    printf("Input: ");
    scanf("%s", input);

    nextToken();

    if (parse_S() && token == EOF_TOKEN) {
        printf("Accept\n");
    }
    else {
        parse_error();
    }

    return 0;
}
