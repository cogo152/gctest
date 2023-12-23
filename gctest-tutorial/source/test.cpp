#include <gctest/core/test.hpp>

#include <string>

/*
 * This is a class for test purpose.
 */
class exceptional
{
public:
    static void static_throw_or_not(bool fail)
    {
        if (fail)
        {
            throw 1;
        }
    }

    void member_throw_or_not(bool fail)
    {
        if (fail)
        {
            throw 1;
        }
    }
};

/*
 * This is a global instance of the class exceptional for test purpose.
 */
exceptional excp;

/*
 * Sets test suit's name
 */
GCTEST_SUIT_NAME(gctest tutorial);

/*
 * Sets test suit's multithreading behaviour. By default single executor executes test cases.
 * If it is set to true then optimum executors are created.
 * It is user responsibility to synchronize global shared variables in the test cases.
 */
GCTEST_SUIT_MULTITHREADED(GCTEST_TRUE);

/*
 * This macro is a test case macro.
 * The argument is test case name.
 */
GCTEST_CASE(test_case_full_implementation)
{

    /*
     * This macro is a test case configuration macro and only valid in a GCTEST_CASE macro.
     * The first argument is test case name and it should be the same as in the GCTEST_CASE macro.
     * The second argument is test case execution priority.
     * THIS MACRO IS MANDATORY in the GCTEST_CASE macro.
     */
    gctest_case_config_priority(test_case_full_implementation, 0);

    /*
     * This macro sets test case description and only valid in a GCTEST_CASE macro.
     * The argument is test case description.
     * THIS MACRO IS OPTIONAL in the GCTEST_CASE macro.
     */
    gctest_case_description("test case full implementation successful");

    /*
     * This macro sets sleep time before the test execution and only valid in a GCTEST_CASE macro.
     * The argument is sleep time. See also the same macros _nanosecond(), _microsecond(), _millisecond().
     * THIS MACRO IS OPTIONAL in the GCTEST_CASE macro.
     */
    gctest_case_sleep_before_second(1);

    /*
     * This macro sets sleep time after the test execution and only valid in a GCTEST_CASE macro.
     * The argument is sleep time. See also the same macros _nanosecond(), _microsecond(), _millisecond().
     * THIS MACRO IS OPTIONAL in the GCTEST_CASE macro.
     */
    gctest_case_sleep_after_second(1);

    /*
     * You can define and initialize variables.
     * All the variables defined in the GCTEST_CASE macro are private members and can be reachable from gctest_case test execution macros.
     * These macros are forexample gctest_case_before, gctest_case_now, gctest_case_after.
     */
    int *ptr = nullptr;
    const char *c_str = "gctest";
    const std::string cpp_str{"gctest"};

    /*
     * This macro is executed before the test execution and only valid in a GCTEST_CASE macro.
     * You can allocate and assign variables, or acquire locks if you are in multithreaded mode, etc.
     * You can assume that this macro is a constructor of a class.
     * THIS MACRO IS OPTIONAL in the GCTEST_CASE macro.
     */
    gctest_case_before
    {
        ptr = new int;
        *ptr = 1;
    };

    /*
     * This macro is test execution and only valid in a GCTEST_CASE macro.
     * You can assert the condition in this macro.
     * THIS MACRO IS MANDATORY in the GCTEST_CASE macro.
     */
    gctest_case_now
    {
        assert_true(*ptr == 1);
        assert_false(*ptr == 2);

        assert_equal(*ptr, 1);
        assert_equal(c_str, "gctest");
        assert_equal(cpp_str, std::string("gctest"));

        assert_not_equal(*ptr, 2);
        assert_not_equal(c_str, "not gctest");
        assert_not_equal(cpp_str, std::string("not gctest"));

        assert_greater(*ptr, 0);
        assert_greater_or_equal(*ptr, 0);
        assert_greater_or_equal(*ptr, 1);

        assert_lesser(*ptr, 2);
        assert_lesser_or_equal(*ptr, 1);
        assert_lesser_or_equal(*ptr, 2);

        /*
         * This function asserts if any exception is thrown. Otherwise test case fails.
         * The first argument is pointer of the static class or non-class functions.
         * The second argument is parameter list of the function. You should insert arguments with commas(,).
         */
        assert_nonmember_throws(&exceptional::static_throw_or_not, true);

        /*
         * This function asserts if any exception is not thrown. Otherwise test case fails.
         * The first argument is pointer of the static class or non-class functions.
         * The second argument is parameter list of the function. You should insert arguments with commas(,).
         */
        assert_nonmember_not_throws(&exceptional::static_throw_or_not, false);

        /*
         * This function asserts if any exception is thrown. Otherwise test case fails.
         * The first argument is pointer of the class instance.
         * The second argument is pointer of the instance method.
         * The third argument is parameter list of the function. You should insert arguments with commas(,).
         */
        assert_member_throws(&excp, &exceptional::member_throw_or_not, true);

        /*
         * This function asserts if any exception is not thrown. Otherwise test case fails.
         * The first argument is pointer of the class instance.
         * The second argument is pointer of the instance method.
         * The third argument is parameter list of the function. You should insert arguments with commas(,).
         */
        assert_member_not_throws(&excp, &exceptional::member_throw_or_not, false);
    };

    /*
     * This macro is executed after the test execution and only valid in a GCTEST_CASE macro.
     * You can nullify or release variables, or release locks if you are in multithreaded mode, etc.
     * You can assume that this macro is a destructor of a class.
     * THIS MACRO IS OPTIONAL in the GCTEST_CASE macro.
     */
    gctest_case_after
    {
        delete ptr;
    }
};

GCTEST_CASE(fail_on_error)
{
    // comes after prior test cases
    gctest_case_config_default(fail_on_error);

    gctest_case_now
    {
        int *ptr = nullptr;
        *ptr = 1;
    }
};

GCTEST_CASE(fail_on_std_exception)
{
    gctest_case_config_priority(fail_on_std_exception, 2);

    gctest_case_now
    {
        throw std::invalid_argument("std exception");
    }
};

GCTEST_CASE(fail_on_generic_exception)
{
    gctest_case_config_priority(fail_on_generic_exception, 3);

    gctest_case_now
    {
        throw 1;
    }
};

GCTEST_CASE(fail_on_assertion_true)
{
    gctest_case_config_priority(fail_on_assertion_true, 4);

    gctest_case_now
    {
        assert_true(1 + 1 == 3);
    }
};

GCTEST_CASE(fail_on_assertion_false)
{
    gctest_case_config_priority(fail_on_assertion_false, 5);

    gctest_case_now
    {
        assert_false(1 + 1 == 2);
    }
};

GCTEST_CASE(fail_on_assertion_equal)
{
    gctest_case_config_priority(fail_on_assertion_equal, 6);

    gctest_case_now
    {
        assert_equal(1, 2);
    }
};

GCTEST_CASE(fail_on_assertion_not_equal)
{
    gctest_case_config_priority(fail_on_assertion_not_equal, 7);

    gctest_case_now
    {
        assert_not_equal(1, 1);
    }
};

GCTEST_CASE(fail_on_assertion_greater)
{
    gctest_case_config_priority(fail_on_assertion_greater, 8);

    gctest_case_now
    {
        assert_greater(2, 2);
    }
};

GCTEST_CASE(fail_on_assertion_greater_or_equal)
{
    gctest_case_config_priority(fail_on_assertion_greater_or_equal, 9);

    gctest_case_now
    {
        assert_greater_or_equal(1, 2);
    }
};

GCTEST_CASE(fail_on_assertion_lesser)
{
    gctest_case_config_priority(fail_on_assertion_lesser, 10);

    gctest_case_now
    {
        assert_lesser(2, 2);
    }
};

GCTEST_CASE(fail_on_assertion_lesser_or_equal)
{
    gctest_case_config_priority(fail_on_assertion_lesser_or_equal, 11);

    gctest_case_now
    {
        assert_lesser_or_equal(2, 1);
    }
};

GCTEST_CASE(fail_on_assertion_nonmember_throws)
{
    gctest_case_config_priority(fail_on_assertion_nonmember_throws, 12);

    gctest_case_now
    {
        assert_nonmember_throws(&exceptional::static_throw_or_not, false);
    }
};

GCTEST_CASE(fail_on_assertion_nonmember_not_throws)
{
    gctest_case_config_priority(fail_on_assertion_nonmember_not_throws, 13);

    gctest_case_now
    {
        assert_nonmember_not_throws(&exceptional::static_throw_or_not, true);
    }
};

GCTEST_CASE(fail_on_assertion_member_throws)
{
    gctest_case_config_priority(fail_on_assertion_member_throws, 14);

    gctest_case_now
    {
        assert_member_throws(&excp, &exceptional::member_throw_or_not, false);
    }
};

GCTEST_CASE(fail_on_assertion_member_not_throws)
{
    gctest_case_config_priority(fail_on_assertion_member_not_throws, 15);

    gctest_case_now
    {
        assert_member_not_throws(&excp, &exceptional::member_throw_or_not, true);
    }
};