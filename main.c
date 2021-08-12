#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 30000
#define LOOP_SIZE 30

void skip_loop(FILE *fp);

typedef struct {
    fpos_t begin;
    char *cell;
} Loop;

int main(int argc, char *argv[]) {
    char tape[TAPE_SIZE] = {0};
    Loop loops[LOOP_SIZE];
    char *p = &tape[0];
    char c;
    char *cinp = NULL;
    Loop *lp = &loops[0];
    FILE *fp;

    if (argc < 2) {
        printf("No file provided!\n");
        return EXIT_FAILURE;
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("%s not found!\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (argc > 2)
        cinp = &argv[2][0];

    while ((c = fgetc(fp)) != EOF) {
        switch (c) {
            case '>':
                p++;
                break;
            case '<':
                p--;
                break;
            case '+':
                (*p)++;
                break;
            case '-':
                (*p)--;
                break;
            case '.':
                printf("%c", *p);
                break;
            case ',':
                if (cinp)
                    *p = *(cinp++);
                else
                    *p = 0;
                break;
            case '[':
                if (*p) {
                    fgetpos(fp, &(lp->begin));
                    lp->cell = p;
                    lp++;
                } else
                    skip_loop(fp);
                break;
            case ']':
                lp--;
                if (*(lp->cell)) {
                    fsetpos(fp, &(lp->begin));
                    lp++;
                }
                break;
        }
    }


    printf("\n");
    return EXIT_SUCCESS;
}

void skip_loop(FILE *fp) {
    int n = 1;
    char c;
    while (n > 0 && (c = fgetc(fp)) != EOF) {
        switch (c) {
            case '[':
                n++;
                break;
            case ']':
                n--;
                break;
        }
    }
}
