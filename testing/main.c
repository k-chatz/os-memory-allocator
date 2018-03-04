#include <stdio.h>
#include "../malloc.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

void separate();

int main() {
    int i;
    char * p[8];


    for (i = 0; i < 8; ++i) {
        p[i] = (char *) mymalloc(512);
        printPointer(p[i]);
    }

    printf("free\n\n");
    myfree( p[3]);
    printPointer(p[3]);


    printf("free\n\n");
    myfree( p[5]);
    printPointer(p[5]);

    printf("malloc again\n\n");
    p[5] = (char *) mymalloc(512);

    printPointer(p[5]);





    return 0;
}

void separate() {
    int col;
    /*The following code is from:
	* http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
	*/
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    col = w.ws_col;
    int i = 1;
    for (; i <= col; i++) {
        if (i == 1 || i == col)
            printf("+");
        else
            printf("-");
    }
}
