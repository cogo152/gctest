#include <gctest/core/gctest.hpp>

#include <string>

using namespace gctest::assertion;

GCTEST_CONFIG_SET_MULTITHREADED(GCTEST_TRUE);

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

exceptional excp;

GCTEST_CASE(full_implementation)
{
    gctest_case_priority(full_implementation, 0);
    gctest_case_name("gctest full implementation");
    gctest_case_description("gctest full implementation");

    gctest_before_sleep_in_second(1);
    gctest_after_sleep_in_second(1);

    int *ptr = nullptr;
    const char *c_str = "gctest";
    const std::string cpp_str{"gctest"};

    gctest_before
    {
        ptr = new int;
        *ptr = 1;
    };

    gctest_now
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

        assert_nonmember_throws(exceptional::static_throw_or_not, true);
        assert_nonmember_not_throws(exceptional::static_throw_or_not, false);

        assert_member_throws(&excp, &exceptional::member_throw_or_not, true);
        assert_member_not_throws(&excp, &exceptional::member_throw_or_not, false);
    };

    gctest_after
    {
        delete ptr;
    }
};

GCTEST_CASE(fail_on_error)
{
    gctest_case_priority(fail_on_error, 1);

    gctest_now
    {
        int *ptr = nullptr;
        *ptr = 1;
    }
};

GCTEST_CASE(fail_on_std_exception)
{
    gctest_case_priority(fail_on_std_exception, 2);

    gctest_now
    {
        throw std::invalid_argument("std exception");
    }
};

GCTEST_CASE(fail_on_none_standart_exception)
{
    gctest_case_priority(fail_on_none_standart_exception, 3);

    gctest_now
    {
        throw 1;
    }
};

GCTEST_CASE(fail_on_assertion_true)
{
    gctest_case_priority(fail_on_assertion_true, 4);

    gctest_now
    {
        assert_true(1 + 1 == 3);
    }
};

GCTEST_CASE(fail_on_assertion_false)
{
    gctest_case_priority(fail_on_assertion_false, 5);

    gctest_now
    {
        assert_false(1 + 1 == 2);
    }
};

GCTEST_CASE(fail_on_assertion_equal)
{
    gctest_case_priority(fail_on_assertion_equal, 6);

    gctest_now
    {
        assert_equal(1, 2);
    }
};

GCTEST_CASE(fail_on_assertion_not_equal)
{
    gctest_case_priority(fail_on_assertion_not_equal, 7);

    gctest_now
    {
        assert_not_equal(1, 1);
    }
};

GCTEST_CASE(fail_on_assertion_nonmember_throws)
{
    gctest_case_priority(fail_on_assertion_nonmember_throws, 8);

    gctest_now
    {
        assert_nonmember_throws(exceptional::static_throw_or_not, false);
    }
};

GCTEST_CASE(fail_on_assertion_nonmember_not_throws)
{
    gctest_case_priority(fail_on_assertion_nonmember_not_throws, 9);

    gctest_now
    {
        assert_nonmember_not_throws(exceptional::static_throw_or_not, true);
    }
};

GCTEST_CASE(fail_on_assertion_member_throws)
{
    gctest_case_priority(fail_on_assertion_member_throws, 10);

    gctest_now
    {
        assert_member_throws(&excp, &exceptional::member_throw_or_not, false);
    }
};

GCTEST_CASE(fail_on_assertion_member_not_throws)
{
    gctest_case_priority(fail_on_assertion_member_not_throws, 11);

    gctest_now
    {
        assert_member_not_throws(&excp, &exceptional::member_throw_or_not, true);
    }
};