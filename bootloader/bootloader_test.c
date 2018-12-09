#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "bootloader.h"

/* external functions to test ---------------------------------------------- */
extern int bootloader(void);
extern int read_last_bootcode(void);

/* mock functions ---------------------------------------------------------- */
static int mock_read_last_bootcode(void) {
    return (int)mock();
}

/* test cases -------------------------------------------------------------- */
static void test_bootloader_succes(void **state) {
    assert_int_equal(bootloader(), BOOT_SUCCESS);
}

static void test_last_bootcode_success(void **state) {
    will_return(mock_read_last_bootcode, BOOT_HOI);
    assert_true(mock_read_last_bootcode() == BOOT_SUCCESS);
}

static void test_last_bootcode_fail(void **state) {
    will_return(mock_read_last_bootcode, BOOT_FAIL);
    assert_true(mock_read_last_bootcode() == BOOT_FAIL);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_bootloader_succes),
        cmocka_unit_test(test_last_bootcode_success),
        cmocka_unit_test(test_last_bootcode_fail),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
