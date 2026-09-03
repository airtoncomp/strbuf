#include <stdio.h>
#include <stdlib.h>

#include "strbuf.h"

void test_strbuf()
{
    printf("--- BEGIN: TEST STRBUF ---\n");

    strbuf_t sb1;
    sb_init(&sb1, 100);
    sb_print_safe_stdout(&sb1);
    sb_free(&sb1);

    strbuf_t sb2;
    sb_init_str(&sb2, "test-strbuf", strlen("test-strbuf"));
    //sb_print_safe_stdout(&sb2);
    sb_println_safe_stdout(&sb2);
    sb_free(&sb2);

    strbuf_t sb3;
    //sb_from_cstr(&sb3, "test must fail");
    sb_init(&sb3, 1);
    sb_from_cstr(&sb3, "test must pass");
    sb_println_safe_stdout(&sb3);
    sb_bzero(&sb3);
    printf("String buffer should be zeroed ('\\0'). Nothing should be printed here:");
    sb_println_safe_stdout(&sb3);
    sb_free(&sb3);

    strbuf_t sb4;
    sb_init(&sb4, 1);
    sb_from_cstr(&sb4, "test");
    sb_append_cstr(&sb4, "in");
    sb_append_char(&sb4, 'g');
    sb_println_safe_stdout(&sb4);
    sb_free(&sb4);

    printf("--- END: TEST STRBUF ---\n");
}

int main()
{
    test_strbuf();
    return 0;
}
