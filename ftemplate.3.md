# NAME

ftemplate

# SYNOPSIS

    #include <ftemplate.h>
    bool
    ftemplate(FILE      *_o,
              FILE      *_i,
              const char _start[],
              const char _end[],
              size_t     _keysz,
              char       _key[_keysz]);

# DESCRIPTION

The simplest implementation of a templating mechanism in C. The *ftemplate* function reads
from *_i* and if not null writes to *_o*. When it finds a tag enclossured between *_start*
and *_end* then it returns *true* with the tag in *_key*.

After receiving an EOF from *_i* or failing to write to *_o* it returns false. You can use
this function in a while loop. If there's no space in b to store a tag returns false.


    while (ftemplate(stdout, stdin, "{{", "}}", sizeof(b), b)) {
        if (!strcmp(b, "key1")) {
            fputs("val1", stdout);
        } else {
            /* Unknown key. */
        }
    }

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

# SEE ALSO

**OPEN_MEMSTREAM(3)**, **FMEMOPEN(3)**

