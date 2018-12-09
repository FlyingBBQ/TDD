#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "cbuf.h"

/* global testing variables */
cbuf_t cbuf;
uint8_t buffer[32];

/* test functions */
static void test_cbuf_init(void **state) {
    cbuf_init(&cbuf, buffer, sizeof(buffer));
    assert_int_equal(sizeof(buffer), 32);
    assert_ptr_equal(cbuf.head, buffer);
    assert_ptr_equal(cbuf.tail, buffer);
}

static void test_cbuf_put(void **state) {
    cbuf_init(&cbuf, buffer, sizeof(buffer));
    assert_ptr_equal(cbuf.head, buffer);

    cbuf_put(&cbuf, 6);
    assert_int_equal((&buffer[0] - cbuf.head), 2);
    assert_ptr_equal(cbuf.head, &buffer[0]);
    assert_int_equal(buffer[0], 6);
    cbuf_put(&cbuf, 3);
    assert_int_equal(buffer[1], 3);
    assert_ptr_equal(cbuf.head, &buffer[1]);
}

/* run the test functions */
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_cbuf_init),
        cmocka_unit_test(test_cbuf_put),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
