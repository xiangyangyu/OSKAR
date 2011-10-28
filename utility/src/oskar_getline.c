/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "utility/oskar_getline.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
#endif
int oskar_getline(char** lineptr, size_t* n, FILE* stream)
{
    // Check for sane inputs.
    if (lineptr == NULL || n == NULL || stream == NULL)
        return OSKAR_ERR_INVALID_ARGUMENT;

    // Check if buffer is empty.
    if (*n == 0 || *lineptr == NULL)
    {
        *n = 80;
        *lineptr = (char*)malloc(*n);
        if (*lineptr == NULL)
            return OSKAR_ERR_MEMORY_ALLOC_FAILURE;
    }

    // Initialise the byte counter.
    size_t size = 0;

    // Read in the line.
    for (;;)
    {
        // Get the character.
        int i;
        i = getc(stream);
        if (i == EOF)
            return OSKAR_ERR_EOF;

        // Allocate space for size+1 bytes (including NULL terminator).
        if (size + 1 >= *n)
        {
            void *t;

            // Double the length of the buffer.
            *n = 2 * *n + 1;
            t = realloc(*lineptr, *n);
            if (t == NULL)
                return OSKAR_ERR_MEMORY_ALLOC_FAILURE;
            *lineptr = (char*)t;
        }

        // Store the character.
        (*lineptr)[size++] = i;

        // Check if end-of-line reached.
        if (i == '\n')
            break;
    }

    // Add a NULL terminator.
    (*lineptr)[size] = '\0';

    // Return the number of characters read.
    return size;
}
