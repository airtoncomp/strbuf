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

    strbuf_t sb2; sb_init_str(&sb2, "test-strbuf", strlen("test-strbuf"));
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

    strbuf_t sb5;
    sb_init(&sb5, 10);
    sb_from_cstr(&sb5, "test");
    sb_insert_at(&sb5, 2, "xy");
    sb_println_safe_stdout(&sb5);
    sb_free(&sb5);

    strbuf_t sb6;
    sb_init(&sb6, 10);
    sb_from_cstr(&sb6, "test-remove");
    sb_remove(&sb6, 4, 7);
    sb_println_safe_stdout(&sb6);
    sb_free(&sb6);

    strbuf_t sb7;
    sb_init(&sb7, 20);
    sb_from_cstr(&sb7, "test-remove");
    sb_remove(&sb7, 4, 1);
    sb_println_safe_stdout(&sb7);
    sb_free(&sb7);

    strbuf_t sb8;
    sb_init_str(&sb8, "test-remove", strlen("test-remove"));
    sb_remove_slice(&sb8, 4, 10);
    sb_println_safe_stdout(&sb8);
    sb_free(&sb8);

    strbuf_t sb9;
    sb_init_str(&sb9, "test-remove", strlen("test-remove"));
    sb_remove_slice(&sb9, 4, 4);
    sb_println_safe_stdout(&sb9);
    sb_free(&sb9);

    strbuf_t sb10;
    sb_init_str(&sb10, "test-my-lib-strbuf", strlen("test-my-lib-strbuf"));
    sb_replace(&sb10, 4, 3, "ing-c");
    sb_println_safe_stdout(&sb10);
    sb_free(&sb10);
 
    printf("--- END: TEST STRBUF ---\n");
}

int main()
{
    test_strbuf();
    return 0;
}
