#include<stdio.h>

#define MEMORY_BUFFER_SIZE 30000

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

#define SUCCESS 0

void help();

void parse(FILE *f_input, FILE *f_output);

void output_header(FILE *f_output);
void output_left(FILE *f_output);
void output_right(FILE *f_output);
void output_plus(FILE *f_output);
void output_minus(FILE *f_output);
void output_loopstart(FILE *f_output);
void output_loopend(FILE *f_output);
void output_comma(FILE *f_output);
void output_dot(FILE *f_output);
void output_footer(FILE * f_output);

int main(int argc, char **argv) {
    if (argc <= 1) {
        help();

        return SUCCESS;
    } else if (argc > 2) {
        printf("Ignoring extra arguments.\n");
    }

    FILE *f_input = fopen(argv[1], "r");
    FILE *f_output = fopen("bf.out.c", "w");

    parse(f_input, f_output);

    fclose(f_input);
    fclose(f_output);

    return SUCCESS;
}

void help() {
    printf("Marko's BrainFuck Compiler, v%d.%d.%d\n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    printf("Usage: mbfc <input-file>\n");
}


void parse(FILE *f_input, FILE *f_output) {
    output_header(f_output);

    int c;
    while ((c = fgetc(f_input)) != EOF) {
        switch (c) {
        case '<':
            output_left(f_output);
            break;
        case '>':
            output_right(f_output);
            break;
        case '+':
            output_plus(f_output);
            break;
        case '-':
            output_minus(f_output);
            break;
        case '[':
            output_loopstart(f_output);
            break;
        case ']':
            output_loopend(f_output);
            break;
        case ',':
            output_comma(f_output);
            break;
        case '.':
            output_dot(f_output);
            break;
        }
    }

    output_footer(f_output);
}

void output_header(FILE *f_output) {
    fprintf(f_output,
            "#include<stdio.h>\n"
            "unsigned char memory[%d];\n"
            "unsigned int p = 0;\n"
            "int main() {\n",
            MEMORY_BUFFER_SIZE);
}

void output_footer(FILE *f_output) {
    fprintf(f_output,
            "return 0;\n"
            "}\n");
}

// what if p <= 0?
void output_left(FILE *f_output) {
    fprintf(f_output,
            "p--;\n");
}

void output_right(FILE *f_output) {
    fprintf(f_output,
            "p++;\n");
}

// TODO: add bounds check
void output_plus(FILE *f_output) {
    fprintf(f_output,
            "memory[p]++;\n");
}

// TODO: add bounds check
void output_minus(FILE *f_output) {
    fprintf(f_output,
            "memory[p]--;\n");
}

void output_loopstart(FILE *f_output) {
    fprintf(f_output,
            "do {\n");
}

// TODO: maybe perform bounds check?
void output_loopend(FILE *f_output) {
    fprintf(f_output,
            "} while (memory[p] > 0);\n");
}

void output_comma(FILE *f_output) {
    fprintf(f_output,
            "int c = getchar();\n"
            "memory[p] = (unsigned char) c;\n");
}

void output_dot(FILE *f_output) {
    fprintf(f_output,
            "putchar(memory[p]);\n");
}


