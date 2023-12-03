#include <gctest/core/gctest.hpp>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

namespace nonmember
{
    void global_throw_void(void)
    {
        throw 1;
    }

    static void static_throw_void(void)
    {
        throw 1;
    }

    void global_not_throw_void(void)
    {
    }

    static void static_not_throw_void(void)
    {
    }

    void global_throw_or_not_argument(int a, int *b, int &c)
    {
        int d = a + *b + c;
        if (d == 3)
        {
            throw 1;
        }
    }

    static void static_throw_or_not_argument(int a, int *b, int &c)
    {
        int d = a + *b + c;
        if (d == 3)
        {
            throw 1;
        }
    }
}

namespace member_or_nonmember
{
    class member_or_nonmember
    {
    public:
        void throw_void(void)
        {
            nonmember::global_throw_void();
        }

        static void static_throw_void(void)
        {
            nonmember::static_throw_void();
        }

        void not_throw_void(void)
        {
            nonmember::global_not_throw_void();
        }

        static void static_not_throw_void(void)
        {
            nonmember::static_not_throw_void();
        }

        void throw_or_not_argument(int a, int *b, int &c)
        {
            nonmember::global_throw_or_not_argument(a, b, c);
        }

        static void static_throw_or_not_argument(int a, int *b, int &c)
        {
            nonmember::static_throw_or_not_argument(a, b, c);
        }
    };
}

int a = 1;
int *b = &a;
int &c = a;
member_or_nonmember::member_or_nonmember member;

GCTEST_CASE(test_assertion_success)
{
    gctest_case_priority(test_assertion_success, 200);

    gctest_now
    {
        assert_true(true);
        assert_true(1 + 1 == 2);

        assert_false(false);
        assert_false(1 + 1 == 3);

        assert_equal(true, true);
        assert_equal(1, 1);
        assert_equal(std::string("ab"), std::string("ab"));
        assert_equal("ab", "ab");

        assert_not_equal(true, false);
        assert_not_equal(1, 0);
        assert_not_equal(std::string("ab"), std::string("ac"));
        assert_not_equal("ab", "ac");

        assert_greater(2, 1);
        assert_greater_or_equal(2, 1);
        assert_greater_or_equal(2, 2);

        assert_lesser(1, 2);
        assert_lesser_or_equal(1, 2);
        assert_lesser_or_equal(2, 2);

        assert_nonmember_throws(&nonmember::global_throw_void);
        assert_nonmember_throws(&nonmember::static_throw_void);
        assert_nonmember_throws(&member_or_nonmember::member_or_nonmember::static_throw_void);
        assert_nonmember_throws(&nonmember::global_throw_or_not_argument, a, b, c);
        assert_nonmember_throws(&nonmember::static_throw_or_not_argument, a, b, c);
        assert_nonmember_throws(&member_or_nonmember::member_or_nonmember::static_throw_or_not_argument, a, b, c);

        assert_nonmember_not_throws(&nonmember::global_not_throw_void);
        assert_nonmember_not_throws(&nonmember::static_not_throw_void);
        assert_nonmember_not_throws(&member_or_nonmember::member_or_nonmember::static_not_throw_void);
        assert_nonmember_not_throws(&nonmember::global_throw_or_not_argument, 2, b, c);
        assert_nonmember_not_throws(&nonmember::static_throw_or_not_argument, 2, b, c);
        assert_nonmember_not_throws(&member_or_nonmember::member_or_nonmember::static_throw_or_not_argument, 2, b, c);

        assert_member_throws(&member, &member_or_nonmember::member_or_nonmember::throw_void);
        assert_member_throws(&member, &member_or_nonmember::member_or_nonmember::throw_or_not_argument, a, b, c);

        assert_member_not_throws(&member, &member_or_nonmember::member_or_nonmember::not_throw_void);
        assert_member_not_throws(&member, &member_or_nonmember::member_or_nonmember::throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_1)
{
    gctest_case_priority(test_assertion_fail_1, 201);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_true(false);
    }
};

GCTEST_CASE(test_assertion_fail_2)
{
    gctest_case_priority(test_assertion_fail_2, 202);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_false(true);
    }
};

GCTEST_CASE(test_assertion_fail_3)
{
    gctest_case_priority(test_assertion_fail_3, 203);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_equal(1, 0);
    }
};

GCTEST_CASE(test_assertion_fail_4)
{
    gctest_case_priority(test_assertion_fail_4, 204);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_equal(std::string("ab"), std::string("ac"));
    }
};

GCTEST_CASE(test_assertion_fail_5)
{
    gctest_case_priority(test_assertion_fail_5, 205);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_equal("ab", "ac");
    }
};

GCTEST_CASE(test_assertion_fail_6)
{
    gctest_case_priority(test_assertion_fail_6, 206);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_not_equal(1, 1);
    }
};

GCTEST_CASE(test_assertion_fail_7)
{
    gctest_case_priority(test_assertion_fail_7, 207);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_not_equal(std::string("ab"), std::string("ab"));
    }
};

GCTEST_CASE(test_assertion_fail_8)
{
    gctest_case_priority(test_assertion_fail_8, 208);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_not_equal("ab", "ab");
    }
};

GCTEST_CASE(test_assertion_fail_9)
{
    gctest_case_priority(test_assertion_fail_9, 209);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_greater(1, 2);
    }
};

GCTEST_CASE(test_assertion_fail_10)
{
    gctest_case_priority(test_assertion_fail_10, 210);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_greater_or_equal(1, 2);
    }
};

GCTEST_CASE(test_assertion_fail_11)
{
    gctest_case_priority(test_assertion_fail_11, 211);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_lesser(2, 1);
    }
};

GCTEST_CASE(test_assertion_fail_12)
{
    gctest_case_priority(test_assertion_fail_12, 212);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_lesser_or_equal(2, 1);
    }
};

GCTEST_CASE(test_assertion_fail_13)
{
    gctest_case_priority(test_assertion_fail_13, 213);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::global_not_throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_14)
{
    gctest_case_priority(test_assertion_fail_14, 214);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::static_not_throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_15)
{
    gctest_case_priority(test_assertion_fail_15, 215);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&member_or_nonmember::member_or_nonmember::static_not_throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_16)
{
    gctest_case_priority(test_assertion_fail_16, 216);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::global_throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_17)
{
    gctest_case_priority(test_assertion_fail_17, 217);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::static_throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_18)
{
    gctest_case_priority(test_assertion_fail_18, 218);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&member_or_nonmember::member_or_nonmember::static_throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_19)
{
    gctest_case_priority(test_assertion_fail_19, 219);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::global_throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_20)
{
    gctest_case_priority(test_assertion_fail_20, 220);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::static_throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_21)
{
    gctest_case_priority(test_assertion_fail_21, 221);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&member_or_nonmember::member_or_nonmember::static_throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_22)
{
    gctest_case_priority(test_assertion_fail_22, 222);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::global_throw_or_not_argument, a, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_23)
{
    gctest_case_priority(test_assertion_fail_23, 223);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::static_throw_or_not_argument, a, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_24)
{
    gctest_case_priority(test_assertion_fail_24, 224);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&member_or_nonmember::member_or_nonmember::static_throw_or_not_argument, a, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_25)
{
    gctest_case_priority(test_assertion_fail_25, 225);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_member_throws(&member, &member_or_nonmember::member_or_nonmember::not_throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_26)
{
    gctest_case_priority(test_assertion_fail_26, 226);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_member_throws(&member, &member_or_nonmember::member_or_nonmember::throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(test_assertion_fail_27)
{
    gctest_case_priority(test_assertion_fail_27, 227);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_member_not_throws(&member, &member_or_nonmember::member_or_nonmember::throw_void);
    }
};

GCTEST_CASE(test_assertion_fail_28)
{
    gctest_case_priority(test_assertion_fail_28, 228);

    gctest_now
    {
        unsuccessfulTestCase++;

        assert_member_not_throws(&member, &member_or_nonmember::member_or_nonmember::throw_or_not_argument, a, b, c);
    }
};
