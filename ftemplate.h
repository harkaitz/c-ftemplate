#ifndef FTEMPLATE_H
#define FTEMPLATE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

static __attribute__((unused))
bool ftemplate(FILE *_o, FILE *_i, const char _start[], const char _end[], size_t _keysz, char _key[_keysz]) {
    int    start_match     = 0;
    int    end_match       = 0;
    bool   is_inside_block = false;
    size_t key_position    = 0;
    int    res             = 0;
    for (;;) {
        int character_int = fgetc(_i);
        if (character_int == EOF) {
            return false;
        }
        char character = character_int;
        /* Inside a block. */
        if (is_inside_block) {
            if (character != _end[end_match++]) {
                _key[key_position++] = character;
                if (key_position==_keysz/*err*/) return false;
                end_match = 0;
            } else if (_end[end_match] == '\0') {
                _key[key_position] = '\0';
                return true;
            }
        }
        /* Outside a block. */
        else if (character != _start[start_match++]) {
            start_match--;
            if (_o) {
                for(int j=0; j<start_match; j++) {
                    res = fputc(_start[j], _o);
                    if (res==EOF/*err*/) return false;
                }
                res = fputc(character, _o);
                if (res==EOF/*err*/) return false;
            }
            start_match = 0;
        } else if (_start[start_match] == '\0') {
            is_inside_block = true;
        }
    }
    return false;
}
#endif
/**l*
 * This software is free to use and modify.
 * 
 * Bug reports, feature requests to gemini|https://harkadev.com/oss
 * Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **l*/
