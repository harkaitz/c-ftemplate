#define _POSIX_C_SOURCE 201000L
#include "../ftemplate.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>

#define PROGNAME "ftemplate"
#define COPYRIGHT_LINE \
    "Bug reports, feature requests to gemini|https://harkadev.com/oss" "\n" \
    "Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com" "\n" \
    ""

int main (int _argc, char *_argv[]) {

    int         opt               = 0;
    int         res               = 0;
    int         retval            = 1;
    char       *found_keys_s[100] = {0};
    long        found_keys_c[100] = {0};
    int         found_keysz       = 0;
    char        current_key[512]  = {0};
    char       *known_keys[_argc*2+1];
    bool        list_keys_p       = false;
    bool        failed            = false;
    const char *start = "{{";
    const char *end   = "}}";
    int         i;
    size_t      j;
    char       *s1,*s2;
    int       (*compare) (const char *s1, const char *s2) = strcasecmp;
    
    /* Print help. */
    if (_argc > 1 && (!strcmp(_argv[1], "-h") || !strcmp(_argv[1], "--help"))) {
        printf("Usage: " PROGNAME " [-s TSTART][-e TEND][-l|KEY=VAL][...]"  "\n"
               ""                                                           "\n"
               "Replace (or list `-l`) tags with {{KEY}} format from "      "\n"
               "standard input. You can change start/end strings with "     "\n"
               "`-s` and `-e`."                                             "\n"
               ""                                                           "\n"
               COPYRIGHT_LINE);
        return 0;
    }

    /* Parse command line arguments. */
    while ((opt = getopt (_argc, _argv, "ls:e:")) != -1) {
        switch (opt) {
        case 'l': list_keys_p = true; break;
        case 's': start = optarg; break;
        case 'e': end   = optarg; break;
        case '?':
        default:  return 1;
        }
    }

    /* Split arguments (when needed). */
    known_keys[0] = NULL;
    for (i=optind,j=0; !list_keys_p && i<_argc; i++) {
        s1 = _argv[i];
        if ((s2 = strchr(s1, '='))) *(s2++) = '\0'; else s2 = "";
        known_keys[j++] = s1;
        known_keys[j++] = s2;
        known_keys[j]   = NULL;
    }
    
    /* Read/write loop. */
    while (ftemplate((list_keys_p)?NULL:stdout, stdin, start, end, sizeof(current_key), current_key)) {
        if (list_keys_p) {
            for(i=0; i<found_keysz; i++) {
                if (!compare(current_key, found_keys_s[i])) {
                    found_keys_c[i]++;
                    break;
                }
            }
            if (found_keysz==100/*err*/) goto cleanup_key_max;
            if (i==found_keysz) {
                found_keys_s[found_keysz] = strdup(current_key);
                if (!found_keys_s[found_keysz]/*err*/) goto cleanup_errno;
                found_keys_c[found_keysz]++;
                found_keysz++;
            }
        } else {
            s1 = NULL;
            for(i=0; known_keys[i]; i+=2) {
                if (!compare(current_key, known_keys[i])) {
                    s1 = known_keys[i+1];
                }
            }
            if (s1) {
                res = fputs(s1, stdout);
                if (res==EOF/*err*/) goto cleanup_errno;
            } else {
                fprintf(stderr, "%s: Key '%s' not defined.\n", PROGNAME, current_key);
                failed = true;
            }
        }
    }

    /* Print list. */
    if (list_keys_p) {
        for(i=0; i<found_keysz; i++) {
            res = printf("%-20s %li\n", found_keys_s[i], found_keys_c[i]);
            if (res<EOF/*err*/) goto cleanup_errno;
        }
    }
    
    /* Cleanup. */
    retval = (failed)?2:0;
    goto cleanup;
 cleanup_key_max:
    fprintf(stderr, "%s: Too much different keys, maximun is 100.\n", PROGNAME);
    goto cleanup;
 cleanup_errno:
    fprintf(stderr, "%s: %s\n", PROGNAME, strerror(errno));
    goto cleanup;
 cleanup:
    for(i=0; i<found_keysz; i++) {
        free(found_keys_s[i]);
    }
    return retval;
}
