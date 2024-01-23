#include "brainfck.h"

int main( void ) {
	struct sbuilder* sb = {0};
	int res;

	// Read the file in full
	res = freadfull("./brainfck.txt", &sb);

	// Check for any failures
	if (res > 0) {
		printf("Error reading 'brainfck.txt'\n");
		freesb(sb);
		return 1;
	}
	
	// Print the file contents, this is a debug step
	printf("File contents: %s\n", sb->sp);

	// Free the memory of the string builder
	freesb(sb);

	return 0;
}
