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

#define BUFLEN_GROWTH_FACTOR   2

static int realloc_buf(strbuf_t *sb, size_t new_cap)
{
    char *temp = realloc(sb->data, new_cap);
    SB_RET_ERR_ON_NULL(temp, "failed to reallocate memory");
    sb->data = temp;    
    sb->cap = new_cap;
    return 0;
}

static int alloc_buf_zero(strbuf_t *sb, size_t cap)
{
    sb->data = calloc(cap, sizeof(*sb->data));
    SB_RET_ERR_ON_NULL(sb->data, "failed to alloc memory");
    sb->cap = cap;
    return 0;
}

static int alloc_buf(strbuf_t *sb, size_t cap)
{
    sb->data = malloc(cap * sizeof(*sb->data));
    SB_RET_ERR_ON_NULL(sb->data, "failed to alloc memory");
    sb->cap = cap;
    return 0;
}

int sb_init(strbuf_t *sb, size_t cap)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    sb->len = 0;
    return alloc_buf_zero(sb, cap); 
}

int sb_init_str(strbuf_t *sb, const char *str, size_t slen)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    sb->len = slen;
    if (alloc_buf(sb, slen) < 0)
        return -1;
    strcpy(sb->data, str);
    return 0;
}

int sb_from_cstr(strbuf_t *sb, const char *cstr)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    SB_RET_ERR_ON_NULL(sb->data, "string buffer *data is null");
    size_t len = strlen(cstr);
    if (sb->cap <= len) {
        if (realloc_buf(sb, sb->cap * BUFLEN_GROWTH_FACTOR + len) < 0)
            return -1;
    }
    strcpy(sb->data, cstr);
    sb->len = strlen(cstr);
    return 0;
}

void sb_bzero(strbuf_t *sb)
{
    if(!sb) {
        fprintf(stderr, "strbuf_t* cannot be null\n");
        return;
    }
    if (!sb->data)
        return;
    memset(sb->data, '\0', sb->cap);
}

void sb_free(strbuf_t *sb)
{
    if (!sb) {
        fprintf(stderr, "strbuf_t* cannot be null\n");
        return;
    }
    if (!sb->data) {
        free(sb->data);
        sb->data = NULL;
        sb->len = 0;
    }
}

int sb_reserve(strbuf_t *sb, size_t required)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    if (sb->cap <= required)
        return realloc_buf(sb, required);
    return 0;
}

int sb_append_cstr(strbuf_t *sb, char *cstr)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    SB_RET_ERR_ON_NULL(cstr, "c string pointer cannot be null");
    size_t len = strlen(cstr);
    size_t tot_len = sb->len + len;
    if (sb->cap <= tot_len) {
        if (realloc_buf(sb, sb->cap * BUFLEN_GROWTH_FACTOR + tot_len) < 0)
            return -1;
    }
    strcat(sb->data, cstr);
    sb->len = tot_len;
    return 0;
}

int sb_append_char(strbuf_t *sb, char c)
{
    SB_RET_ERR_ON_NULL(sb, "strbuf_t* cannot be null");
    size_t tot_len = sb->len + 1;
    if (sb->cap <= tot_len) {
        if (realloc_buf(sb, sb->cap * BUFLEN_GROWTH_FACTOR + tot_len))
            return -1;
    }
    sb->data[sb->len++] = c;
    sb->data[sb->len] = '\0';
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
