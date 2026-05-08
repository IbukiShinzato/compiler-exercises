#include <stdio.h>

#include "lex.h"
#include "syntax.h"
#include "token.h"

#define BUFSIZE 4096

int main(int argc, char** argv)
{
    char buf[BUFSIZE];

    for (;;)
    {
        fputs("> ", stdout);
        fflush(stdout);

        if (fgets(buf, BUFSIZE, stdin) == NULL)
        {
            break;
        }

        if (lex_analysis(buf) < 0)
        {
            fprintf(stderr, "Unkown symbols included\n");
            delete_token_all();
            continue;
        }
        syntax_analysis();
    }

    return 0;
}
