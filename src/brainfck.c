#include "brainfck.h"

int main( void ) {
	struct sbuilder* sb = {0};
	struct lexer* l = {0};
	int res,c;

	// Read the file in full.
	// The usage of a double pointer for sbuilder is done on purpose
	// for memory efficiency in order to defer allocation of memory
	// to the point of file reading. 
	res = freadfull("./brainfck.txt", &sb);

	// Check for any failures
	if (res != 0) {
		printf("Error reading 'brainfck.txt'\n");
		freesb(sb);
		return 1;
	}
	
	// Print the file contents, this is a debug step
	printf("File contents:\n\n");
	printf("%s\n", sb->sp);

	l = createlexer(sb);
	printf("\n\nLexer:\n");
	while((c = next(l))) printf("token: %c\n", c);


	printf("\n\nStack:\n");
	for(size_t i = 0; i < l->stksize; i++) {
		printf("cell: #c%lu\n", i);
		printf("value: %d\n", l->stk[i]);
	}

	// Free the memory of the string builder
	freesb(sb);
	freel(l);

	return 0;
}
