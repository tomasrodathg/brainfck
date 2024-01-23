#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct sbuilder {
	char *sp;
	size_t len;
};

void freesb(struct sbuilder* sb);
int freadfull(char *fname, struct sbuilder** sb);
