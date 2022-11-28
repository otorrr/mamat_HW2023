#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void operate (FILE *f);

int main(int argc, char **argv) {
	FILE *f;

	if (argc==1 || !strcmp("-", argv[1])) {
		f=stdin;
	} else {
		f=fopen(argv[1], "r");
	}
	/* Must check for errors */
	if (!f) {
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
		return 1;
	}

	operate(f);
}


void operate (FILE *f) {
    int grade;
    int retval;
    int line_n = 0;
    int n;
    int* a = (int*)malloc(n * sizeof(int));
    int median;
    while(1){
        retval=fscanf(f, "%d", &grade);
        if (retval==EOF) {
            break; /*Finished*/
        } else if (retval !=1 || retval < 1 || retval > 100) {
            /*Error*/
            fprintf(stderr, "Error not a grade\n");
            exit(1);
        }

        a[line_n] = grade;
        line_n++;
    }
    median = (line_n + 1)/2;
    printf("%d", a[median-1]);
}