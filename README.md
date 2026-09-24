<img src="img/logo-strbuf.png" alt="logo strbuf" width="250">

StrBuf is a lightweight C library for working with mutable strings.
It was created as a personal project and includes a small set of
string operations that I commonly need in C programs.

The library has not been extensively tested and may not be suitable
for production-critical applications.

`strbuf_t` owns and manages its underlying memory, allowing operations
such as append, insert, remove, replace, and resize.

StrBuf can also be used together with [`strview_t`](https://github.com/airtoncomp/strview).
While `strbuf_t` is mutable and owns the string memory, `strview_t`
provides a non-owning, read-only view for operations such as search,
comparison, parsing, and slicing.

Both libraries can therefore be used together depending on whether
the string needs to be modified or only inspected.

```
cc -DDEBUG -std=gnu11 -Wall -Wpedantic -Wextra -Werror -g -o strbuf main.c strbuf.c && ./strbuf
```

## Usage examples

Create string buffer from c-string:

```
strbuf_t sb; 

sb_init_str(&sb, "test-strbuf", strlen("test-strbuf"));

sb_println_safe_stdout(&sb);

sb_free(&sb);
```

Append c-string to string buffer:

```
strbuf_t sb;

/* Init with 1 byte space */
sb_init(&sb, 1);

/* Creates string buffer from c-string by reallocating memory. */
sb_from_cstr(&sb, "test");

sb_append_cstr(&sb, "in");
sb_append_char(&sb, 'g');

sb_println_safe_stdout(&sb);

sb_free(&sb);
```

Insert c-string in string buffer:

```
strbuf_t sb;

/* Init string buffer with 10 bytes in memory space */
sb_init(&sb, 10);

sb_from_cstr(&sb, "test");

/* Insert new c-string at position 2 */
sb_insert_at(&sb, 2, "xy");

sb_println_safe_stdout(&sb);

sb_free(&sb);
```
