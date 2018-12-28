#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdint.h>
#include <limits.h>

/* functions to test */
extern uint8_t crc_main(uint8_t);
extern uint8_t shift_left(uint8_t);
extern uint8_t xor(uint8_t, uint8_t);
extern int divisor_size_check(int, size_t);

/* tests */
static void test_crc_main_return(void **state) {
    assert_int_equal(crc_main(0x2), 0x7);
}

static void test_shift_left(void **state) {
    assert_int_equal(shift_left(0x1), 0x2);
}

static void test_xor(void **state) {
    assert_int_equal(xor(0x2, 0x1), 0x3);
}

static void test_divisor_size(void **state) {
    assert_true(divisor_size_check(0xFE, UCHAR_MAX));
    //assert_in_range(0xFFF, 0, UCHAR_MAX);
}

/* main to run tests */
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_crc_main_return),
        cmocka_unit_test(test_shift_left),
        cmocka_unit_test(test_xor),
        cmocka_unit_test(test_divisor_size),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
