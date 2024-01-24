#include "brainfck.h"
#include <ctype.h>

#define COMMANDS "><+-.,[]"

// pushes tokens to the stack based on brainfck's rules
// the [] still need to be worked on as it's affecting the counts.
void push(struct lexer* l, int c) {
	switch (c) {
		case '>':
			if (l->stkp < l->stksize)
				l->stkp++;
			break;
		case '<':
			if (l->stkp >= 0)
				l->stkp--;
			break;
		case '+':
			l->stk[l->stkp]++;
			break;
		case '-':
			l->stk[l->stkp]--;
			break;
		case '.':
		case ',':
		case '[':
		case ']':
			break;
		default:
			printf("Invalid character %c\n", c);
			break;
	}
}

// allocates memory for the lexer
int allocl(char *s, struct lexer* l) {
	int c;
	size_t ssize = 0;
	size_t tokssize = 0;

	// this loop is not valid for the stack size, 
	// needs to cater for the JMP commands []
	while((c = *s++)) {
		if (strchr(COMMANDS, *s) != NULL)
			tokssize++;
		if (c == '>')
			ssize++;
		else if (c == '<')
			ssize--;
	}

	// allocate memory for the tokens, i.e. the IR
	l->toks = malloc(tokssize * sizeof(char));
	if (l->toks == NULL) {
		printf("Failed to allocate memory for tokens\n");
		return -1;
	}
	l->tokssize = tokssize;

	// allocate memory for the stack
	l->stk = malloc(ssize * sizeof(int));
	if (l->stk == NULL) {
		printf("failed to allocate memory for stack\n");
		return -1;
	}
	for(size_t i = 0; i < ssize ; i++)
		l->stk[i] = 0;
	l->stksize = ssize;

	return 0;
}

// creates the IR for the lexer containing only the valid tokens for Brainfck and the '\0'
int createtoks(char *s, struct lexer *l) {
	// if any of the pointers is null, return an error
	if (s == NULL || l == NULL) {
		printf("Failed to build tokens\n");
		return -1;
	}

	// while the program is not empty and the characters match one of
	// brainfck's valid commands, add to the token array in the lexer
	size_t toki = 0;
	while(*s++ && !isspace(*s) && strchr(COMMANDS, *s) != NULL)
		l->toks[toki++] = *s;
	return 0;
}

struct lexer *createlexer(struct sbuilder *sb) {
	if (sb != NULL) {
		struct lexer *l = malloc(1 * sizeof(struct lexer));
		if (l != NULL) {
			// allocate memory for the lexer's contents. 
			// if it fails, it returns a negative value
			int n = allocl(sb->sp, l);
			if (n != 0) {
				return NULL;
			}

			// create the IR
			if(createtoks(sb->sp, l) != 0) return NULL;

			// initial position for the token array and stack as 0
			// may not need the token array position
			l->stkp = 0;
			l->toksp = 0;
		}
		return l;
	}

	return NULL;
}

// frees the memory for the lexer and its contents
void freel(struct lexer *l) {
	if(l != NULL) {
		free(l->toks);
		free(l->stk);
		free(l);
	}
}

// go through the tokens in the lexer and add values to the stack.
// right now this is returning the tokens, mostly just for debugging purposes,
// but it's really a 'run' call. 
int next(struct lexer* l) {
	int c = l->toks[l->toksp++];
	push(l, c); // this will attempt to push '\0'

	return c;
}
