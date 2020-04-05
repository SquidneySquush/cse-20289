#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define MAX_NUMBERS (1<<10)

/* Functions */

size_t read_numbers(FILE *stream, int numbers[], size_t n) {
	 size_t i = 0;

	 while (i < n && scanf("%d", &numbers[i]) != EOF) {
			 i++;
	 }

	 return i;
}

int cmpNumb (const void *n1, const void *n2){
	return ( *(int*)n1 - *(int*)n2 );
}

/* Main Execution */

int main(int argc, char *argv[]) {
	int numbers[MAX_NUMBERS];
	int i;
	size_t nsize;

	nsize = read_numbers(stdin, numbers, MAX_NUMBERS);
	qsort(numbers, nsize , sizeof(int), cmpNumb);

	for ( i = 0; i < nsize; i++){
	 	printf("%d\n", numbers[i]);
	}

	 return EXIT_SUCCESS;
}
