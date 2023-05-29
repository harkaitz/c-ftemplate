#define _POSIX_C_SOURCE 200809L
#include "../ftemplate.h"
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#define PROGNAME "envsubs"
#define COPYRIGHT_LINE \
    "Copyright (c) 2023 Harkaitz Agirre, harkaitz.aguirre@gmail.com" "\n" \
    ""

int main (int _argc, char *_argv[]) {

    int         opt        = 0;
    const char *start      = "{{";
    const char *end        = "}}";
    const char *help[100]  = {NULL};
    size_t      helpsz     = 0;
    char       *fkeys[100] = {NULL};
    char       *fkeyv[100] = {NULL};
    size_t      fkeysz     = 0;
    bool        opt_l      = false;
    FILE       *bfp        = NULL;
    char       *b          = NULL;
    size_t      bsz        = 0;
    char        key[512];

    /* Print help. */
    if (_argc > 1 && (!strcmp(_argv[1], "-h") || !strcmp(_argv[1], "--help"))) {
        printf("Usage: " PROGNAME " [-s TSTART][-e TEND][-l][-a ENV=HELP]"   "\n"
               ""                                                            "\n"
               "Replace {{KEY}} tags with environment variable values."      "\n"
               ""                                                            "\n"
               "(1) It fails when an environment variable is lacking, and"   "\n"
               "    prints a help string if found."                          "\n"
               "(2) It prints nothing when failing."                         "\n"
               "(3) With -l it lists the KEYs with the help."                "\n"
               ""                                                            "\n"
               COPYRIGHT_LINE);
        return 0;
    }

    /* Parse command line arguments. */
    while ((opt = getopt (_argc, _argv, "s:e:la:")) != -1) {
        switch (opt) {
        case 's': start = optarg; break;
        case 'e': end   = optarg; break;
        case 'l': opt_l = true;   break;
        case 'a':
            help[helpsz] = strtok(optarg, "=");
            if (!help[helpsz]) break;
            help[helpsz+1] = strtok(NULL, "");
            if (!help[helpsz+1]) help[helpsz+1] = ""; 
            helpsz+=2;
            break;
        }
    }

    /* Open buffer. */
    bfp = open_memstream(&b, &bsz);
    assert(bfp);

    /* Read/write loop. */
    while (ftemplate(bfp, stdin, start, end, sizeof(key), key)) {
        /* Search environment variable. */
        char *val = getenv(key);
        
        /* Replace when set. */
        if (!opt_l && val) {
            fputs(val, bfp);
            continue;
        }

        /* Add to the list if not found. */
        size_t i;
        for (i=0; i<fkeysz; i++) {
            if (!strcmp(key, fkeys[i])) {
                break;
            }
        }
        if (i == fkeysz) {
            assert(fkeysz < 100);
            fkeys[fkeysz] = strdup(key);
            fkeyv[fkeysz] = (val)?strdup(val):NULL;
            assert(fkeys[fkeysz]);
            fkeysz++;
        }
    }

    /* Return on success case. */
    if (!opt_l && fkeysz==0) {
        assert(fflush(bfp)==0);
        fwrite(b, 1, bsz, stdout);
        return 0;
    }

    /* Print help. */
    for (size_t i=0; i<fkeysz; i++) {
        char const *hlp = "";
        for (size_t j=0; j<helpsz; j+=2) {
            if (!strcmp(fkeys[i], help[j])) {
                hlp = help[j+1];
                break;
            }
        }
        fprintf(stderr, "%-20s : (%s) %s\n",
                fkeys[i],
                fkeyv[i]? "s"      : " ",
                fkeyv[i]? fkeyv[i] : hlp);
    }

    /* Print error message. */
    if (!opt_l) {
        fprintf(stderr, "Please set the above variables.\n");
        fflush(stderr);
        return 1;
    } else {
        fflush(stderr);
    }
    
    return 0;
}
