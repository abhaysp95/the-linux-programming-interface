// main file

#include <stdio.h>

extern char** environ;

int main(int argc, char **argv) {
	for(char** ep = environ; *ep != NULL; ep++) puts(*ep);
	return 0;
}

/*int main(int argc, char** argv, char** envp) {*/
	/*for(char** ep = envp; *ep != NULL; ep++) puts(*ep);*/
/*}*/