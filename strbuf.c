/**
 * Copyright 2026, Airton Ishimori
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "strbuf.h"

#ifdef DEBUG

#define SB_LOG(...) do {                                                \
            fprintf(stdout, "[DEBUG] %s:%d: ", __FILE__, __LINE__);     \
            fprintf(stdout, __VA_ARGS__);                               \
        } while(0)

#define SB_LOGE(...) do {                                               \
            fprintf(stderr, "[DEBUG] %s:%d: ", __FILE__, __LINE__);     \
            fprintf(stderr, __VA_ARGS__);                               \
        } while(0)

#else

#define SB_LOG(stdout, ...)                 ((void)0)
#define SB_LOGE(stderr, ...)                ((void)0)

#endif

#define SB_RET_ERR_ON_NULL(x, fmt, ...) do {                         \
            if (x == NULL) {                                         \
                fprintf(stderr, "FAIL: " fmt"\n", ##__VA_ARGS__);    \
                return -1;                                           \
            }                                                        \
        } while(0)

#define SB_RET_ERR_ON_TRUE(x, fmt, ...) do {                         \
            if (x) {                                                 \
                fprintf(stderr, "FAIL: " fmt"\n", ##__VA_ARGS__);    \
                return -1;                                           \
            }                                                        \
        } while(0)

#define SB_RET_NULL_ON_TRUE(x, fmt, ...) do {                       \
            if (x) {                                                \
                fprintf(stderr, fmt"\n", ##__VA_ARGS__);            \
                return NULL;                                        \
            }                                                       \
        } while(0)                                          

int sb_init(strbuf_t *sb, size_t cap)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    sb->data = calloc(cap, sizeof(*sb->data));
    sb->len = 0;
    sb->cap = cap;
    return 0;
}

int sb_init_str(strbuf_t *sb, const char *str, size_t len)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    sb->data = calloc(len, sizeof(*sb->data));
    memcpy(sb->data, str, len);
    sb->len = len;
    sb->cap = len;
    return 0;
}

void sb_print_safe_stdout(const strbuf_t *sb)
{
    if (!sb) {
        fprintf(stderr, "strbuf_t* cannot be null");
        return;
    }
    if (!sb->data) { 
        fprintf(stderr, "string buffer *data cannot be null");
        return;
    }
    printf("%.*s", (int) sb->len, sb->data);
}

void sb_println_safe_stdout(const strbuf_t *sb)
{
    if (!sb) {
        fprintf(stderr, "strbuf_t* cannot be null");
        return;
    }
    if (!sb->data) { 
        fprintf(stderr, "string buffer *data cannot be null");
        return;
    }
    printf("%.*s\n", (int) sb->len, sb->data);
}
