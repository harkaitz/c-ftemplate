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

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**OPEN_MEMSTREAM(3)**, **FMEMOPEN(3)**

