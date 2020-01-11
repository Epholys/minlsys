#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char byte;
static byte rules[256][256] = {0};

void lsys(int n, byte c)
{
    int i = 0;     /* General index counter     */
    byte succ = 0; /* Successor in current rule */

    /* End of iteration or identity rule */
    if (n<=0 || !*rules[c]) {
        putc(c, stdout);
        return;
    }

    /* Iterate on each successor */
    while((succ = rules[c][i]) != 0) {
        lsys(n-1, succ);
        i++;
    }
}

int main()
{
    byte axiom[256] = {0}; /* Axiom of the L-System        */
    int iter = 0;           /* Number of iterations         */
    int i = 0;              /* General index counter        */
    int stdin_c = 0;        /* To be read by getchar()      */
    byte pred = 0;          /* Predicate (index of 'rules') */

    /* Read the number of iterations */
    if(scanf("%d", &iter) != 1
        || iter < 0) {
        fputs("Fatal error: can't read or wrong iter.\n", stderr);
        return -1;
    }

    /* Go to next line */
    while((stdin_c = getchar()) != EOF
          && stdin_c != '\n');

    /* Read axiom */
    while((stdin_c = getchar()) != EOF
          && stdin_c != '\n' /* until next line */
          && i<256) {        /* no more than its size */
        axiom[i++] = (byte)stdin_c;
    }

    while(1) {
        /* Ignore empty lines */
        while((stdin_c = getchar()) != EOF
              && stdin_c == '\n');

        if (stdin_c == EOF){
            break;
        }

        /* Get predicate of the L-System rule */
        pred = (byte)stdin_c;

        /* Ignore second character */
        getchar();

        /* Read the successor of this rule */
        i=0;
        while((stdin_c = getchar()) != EOF
              && stdin_c != '\n'
              && i<256) {
            rules[pred][i++] = (byte)stdin_c;
        }
    }

    /* Compute derivation */
    i=0;
    for (i=0; axiom[i]; i++) {
        lsys(iter, axiom[i]);
    }

    return 0;
}
