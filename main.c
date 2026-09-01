#include <stdio.h>
#include <stdlib.h>

#include "strbuf.h"

void test_strbuf()
{
    printf("--- BEGIN: TEST STRBUF ---\n");

    strbuf_t sb1;
    sb_init(&sb1, 100);
    sb_print_safe_stdout(&sb1);

    strbuf_t sb2;
    sb_init_str(&sb2, "test-strbuf", strlen("test-strbuf"));
    //sb_print_safe_stdout(&sb2);
    sb_println_safe_stdout(&sb2);

    printf("--- END: TEST STRBUF ---\n");
}

int main()
{
    test_strbuf();
    return 0;
}
