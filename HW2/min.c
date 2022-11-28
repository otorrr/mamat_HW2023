#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRADE 100


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
	int min=MAX_GRADE;

      while(1){
	retval=fscanf(f, "%d", &grade);
	if (retval==EOF) {
		break; /*Finished*/
	} else if (retval !=1) {
	/*Error*/
	    fprintf(stderr, "Error not a number\n");
    	    exit(1);
	}
	if(grade<min) {
	min=grade;
	}
      }
      printf("%d\n", min);
}      

