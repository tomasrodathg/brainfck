#include "brainfck.h"

int main( void ) {
	struct sbuilder* sb = {0};
	int res;

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

	// Free the memory of the string builder
	freesb(sb);

	return 0;
}
