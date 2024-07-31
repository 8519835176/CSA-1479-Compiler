#include <stdio.h>
#include <ctype.h>

const char* input;  // Global input pointer
char lookahead;     // Current character

// Function prototypes
void expr();
void term();
void factor();
void match(char expected);
void error(const char* msg);

// Utility functions
void error(const char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

void match(char expected) {
    if (lookahead == expected) {
        lookahead = *input++;
    } else {
        error("Unexpected character");
    }
}

// Parsing functions
void expr() {
    term();
    while (lookahead == '+' || lookahead == '-') {
        match(lookahead);
        term();
    }
}

void term() {
    factor();
    while (lookahead == '*' || lookahead == '/') {
        match(lookahead);
        factor();
    }
}

void factor() {
    if (isdigit(lookahead)) {
        while (isdigit(lookahead)) {
            match(lookahead);
        }
    } else if (lookahead == '(') {
        match('(');
        expr();
        match(')');
    } else {
        error("Unexpected character in factor");
    }
}

int main() {
    char buffer[256];

    printf("Enter an expression: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        error("Error reading input");
    }

    input = buffer;
    lookahead = *input++;
    
    expr();
    
    if (lookahead != '\0') {
        error("Extra characters after end of expression");
    }
    
    printf("Expression parsed successfully.\n");
    return 0;
}









