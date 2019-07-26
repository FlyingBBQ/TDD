#include "gtest/gtest.h"

extern "C" {
#include "cbuf.h"
}

cbuf_t cbuf;
uint8_t buffer[32];

//extern void cbuf_init(cbuf_t *cbuf, uint8_t *buffer, size_t size);

TEST(buffer, init)
{
    cbuf_init(&cbuf, buffer, sizeof(buffer));
    ASSERT_EQ(cbuf.head, buffer);
}

#if 0
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
    assert_ptr_equal(cbuf.head, buffer);
    assert_ptr_equal(cbuf.tail, buffer);
    assert_int_equal(cbuf.size, sizeof(buffer));
}

static void test_cbuf_write(void **state) {
    cbuf_init(&cbuf, buffer, sizeof(buffer));
    assert_ptr_equal(cbuf.head, buffer);

    cbuf_write(&cbuf, 6);
    assert_int_equal(buffer[0], 6);
    assert_int_equal((cbuf.head - buffer), 1);
    assert_ptr_equal(cbuf.head, &buffer[0]+1);

    cbuf_write(&cbuf, 3);
    assert_int_equal(buffer[1], 3);
    assert_ptr_equal(cbuf.head, &buffer[1]+1);
}

static void test_cbuf_write_wrap(void **state) {
    cbuf_init(&cbuf, buffer, sizeof(buffer));

    for (int i=0; i < 33; i++) {
        cbuf_write(&cbuf, i);
    }

    assert_int_equal(buffer[0], 32);
    assert_ptr_equal(cbuf.head, &buffer[0]+1);
}

static void test_cbuf_ptrpos(void **state) {
    cbuf_init(&cbuf, buffer, sizeof(buffer));
    cbuf.head++;
    assert_int_equal(cbuf_ptrpos(&cbuf, cbuf.head), 1);

    cbuf.head += 10;
    assert_int_equal(cbuf_ptrpos(&cbuf, cbuf.head), 11);
}

static void test_cbuf_read(void **state) {
    cbuf_init(&cbuf, buffer, sizeof(buffer));
    cbuf_write(&cbuf, 8);
    cbuf_write(&cbuf, 16);

    assert_int_equal(cbuf_read(&cbuf), 8);
    assert_int_equal(cbuf_read(&cbuf), 16);

}

static void test_cbuf_read_wrap(void **state) {
    cbuf_init(&cbuf, buffer, sizeof(buffer));

    for (int i=0; i < 33; i++) {
        cbuf_write(&cbuf, i);
    }

    for (int i=0; i < 30; i++) {
        cbuf_read(&cbuf);
    }

    assert_int_equal(cbuf_read(&cbuf), 30);
    assert_int_equal(cbuf_read(&cbuf), 31);
    assert_int_equal(cbuf_read(&cbuf), 30);
}

/* run the test functions */
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_cbuf_init),
        cmocka_unit_test(test_cbuf_write),
        cmocka_unit_test(test_cbuf_ptrpos),
        cmocka_unit_test(test_cbuf_write_wrap),
        cmocka_unit_test(test_cbuf_read),
        cmocka_unit_test(test_cbuf_read_wrap),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
#endif
