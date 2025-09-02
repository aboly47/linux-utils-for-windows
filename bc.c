#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *input;

double expr(); // forward declaration

// Skip whitespace
void skip() {
    while(*input && (*input==' ' || *input=='\t')) input++;
}

// Parse numbers
double number() {
    skip();
    double val = 0;
    if(*input=='(') {
        input++; 
        val = expr();
        if(*input==')') input++;
    } else {
        while(isdigit(*input)) {
            val = val*10 + (*input-'0');
            input++;
        }
        if(*input=='.') {
            input++;
            double frac=0.1;
            while(isdigit(*input)) {
                val += (*input-'0')*frac;
                frac *= 0.1;
                input++;
            }
        }
    }
    return val;
}

// Parse factors: number or parenthesis
double factor() {
    return number();
}

// Parse term: factor * / factor
double term() {
    double val = factor();
    skip();
    while(*input=='*' || *input=='/') {
        char op = *input; input++; skip();
        double f = factor();
        if(op=='*') val *= f;
        else if(op=='/') val /= f;
    }
    return val;
}

// Parse expression: term + / - term
double expr() {
    double val = term();
    skip();
    while(*input=='+' || *input=='-') {
        char op = *input; input++; skip();
        double t = term();
        if(op=='+') val += t;
        else val -= t;
    }
    return val;
}

int main() {
    char line[256];
    printf("Simple BC (supports + - * / and parentheses)\n");
    while(1) {
        printf("> "); fflush(stdout);
        if(!fgets(line,sizeof(line),stdin)) break;
        input = line;
        double result = expr();
        printf("%g\n", result);
    }
    return 0;
}
