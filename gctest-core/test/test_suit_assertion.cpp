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

GCTEST_CASE(success_all_assertions)
{
    gctest_case_config(success_all_assertions, 200);
    gctest_case_description("gctest should success all valid assertions");

    gctest_case_now
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

GCTEST_CASE(fail_assert_true)
{
    gctest_case_config(fail_assert_true, 201);
    gctest_case_description("gctest should fail if assertion is false");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_true(false);
    }
};

GCTEST_CASE(fail_assert_false)
{
    gctest_case_config(fail_assert_false, 202);
    gctest_case_description("gctest should fail if assertion is true");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_false(true);
    }
};

GCTEST_CASE(fail_assert_equal_1)
{
    gctest_case_config(fail_assert_equal_1, 203);
    gctest_case_description("gctest should fail if assertion is not equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_equal(1, 0);
    }
};

GCTEST_CASE(fail_assert_equal_2)
{
    gctest_case_config(fail_assert_equal_2, 204);
    gctest_case_description("gctest should fail if assertion is not equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_equal(std::string("ab"), std::string("ac"));
    }
};

GCTEST_CASE(fail_assert_equal_3)
{
    gctest_case_config(fail_assert_equal_3, 205);
    gctest_case_description("gctest should fail if assertion is not equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_equal("ab", "ac");
    }
};

GCTEST_CASE(fail_assert_not_equal_1)
{
    gctest_case_config(fail_assert_not_equal_1, 206);
    gctest_case_description("gctest should fail if assertion is equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_not_equal(1, 1);
    }
};

GCTEST_CASE(fail_assert_not_equal_2)
{
    gctest_case_config(fail_assert_not_equal_2, 207);
    gctest_case_description("gctest should fail if assertion is equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_not_equal(std::string("ab"), std::string("ab"));
    }
};

GCTEST_CASE(fail_assert_not_equal_3)
{
    gctest_case_config(fail_assert_not_equal_3, 208);
    gctest_case_description("gctest should fail if assertion is equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_not_equal("ab", "ab");
    }
};

GCTEST_CASE(fail_assert_greater_1)
{
    gctest_case_config(fail_assert_greater_1, 209);
    gctest_case_description("gctest should fail if assertion is equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_greater(2, 2);
    }
};

GCTEST_CASE(fail_assert_greater_2)
{
    gctest_case_config(fail_assert_greater_2, 210);
    gctest_case_description("gctest should fail if assertion is lesser");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_greater(1, 2);
    }
};

GCTEST_CASE(fail_assert_greater_or_equal)
{
    gctest_case_config(fail_assert_greater_or_equal, 211);
    gctest_case_description("gctest should fail if assertion is lesser");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_greater_or_equal(1, 2);
    }
};

GCTEST_CASE(fail_assert_lesser_1)
{
    gctest_case_config(fail_assert_lesser_1, 212);
    gctest_case_description("gctest should fail if assertion is equal");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_lesser(2, 2);
    }
};

GCTEST_CASE(fail_assert_lesser_2)
{
    gctest_case_config(fail_assert_lesser_2, 213);
    gctest_case_description("gctest should fail if assertion is greater");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_lesser(2, 1);
    }
};

GCTEST_CASE(fail_assert_lesser_or_equal)
{
    gctest_case_config(fail_assert_lesser_or_equal, 214);
    gctest_case_description("gctest should fail if assertion is greater");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_lesser_or_equal(2, 1);
    }
};

GCTEST_CASE(fail_assert_nonmember_throws_1)
{
    gctest_case_config(fail_assert_nonmember_throws_1, 215);
    gctest_case_description("gctest should fail if assertion does not throws from global void function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::global_not_throw_void);
    }
};

GCTEST_CASE(fail_assert_nonmember_throws_2)
{
    gctest_case_config(fail_assert_nonmember_throws_2, 216);
    gctest_case_description("gctest should fail if assertion does not throws from static void function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::static_not_throw_void);
    }
};

GCTEST_CASE(fail_assert_nonmember_throws_3)
{
    gctest_case_config(fail_assert_nonmember_throws_3, 217);
    gctest_case_description("gctest should fail if assertion does not throws from static class void function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&member_or_nonmember::member_or_nonmember::static_not_throw_void);
    }
};

GCTEST_CASE(fail_assert_nonmember_throws_4)
{
    gctest_case_config(fail_assert_nonmember_throws_4, 218);
    gctest_case_description("gctest should fail if assertion does not throws from global parametered function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::global_throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(fail_assert_nonmember_throws_5)
{
    gctest_case_config(fail_assert_nonmember_throws_5, 219);
    gctest_case_description("gctest should fail if assertion does not throws from static parametered function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&nonmember::static_throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(fail_assert_nonmember_throws_6)
{
    gctest_case_config(fail_assert_nonmember_throws_6, 220);
    gctest_case_description("gctest should fail if assertion does not throws from static class parametered function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_throws(&member_or_nonmember::member_or_nonmember::static_throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(fail_assert_nonmember_not_throws_1)
{
    gctest_case_config(fail_assert_nonmember_not_throws_1, 221);
    gctest_case_description("gctest should fail if assertion throws from global void function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::global_throw_void);
    }
};

GCTEST_CASE(fail_assert_nonmember_not_throws_2)
{
    gctest_case_config(fail_assert_nonmember_not_throws_2, 222);
    gctest_case_description("gctest should fail if assertion throws from static void function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::static_throw_void);
    }
};

GCTEST_CASE(fail_assert_nonmember_not_throws_3)
{
    gctest_case_config(fail_assert_nonmember_not_throws_3, 223);
    gctest_case_description("gctest should fail if assertion throws from static class void function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&member_or_nonmember::member_or_nonmember::static_throw_void);
    }
};

GCTEST_CASE(fail_assert_nonmember_not_throws_4)
{
    gctest_case_config(fail_assert_nonmember_not_throws_4, 224);
    gctest_case_description("gctest should fail if assertion throws from global parametered function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::global_throw_or_not_argument, 1, b, c);
    }
};

GCTEST_CASE(fail_assert_nonmember_not_throws_5)
{
    gctest_case_config(fail_assert_nonmember_not_throws_5, 225);
    gctest_case_description("gctest should fail if assertion throws from static parametered function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&nonmember::static_throw_or_not_argument, 1, b, c);
    }
};

GCTEST_CASE(fail_assert_nonmember_not_throws_6)
{
    gctest_case_config(fail_assert_nonmember_not_throws_6, 226);
    gctest_case_description("gctest should fail if assertion throws from static class parametered function");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_nonmember_not_throws(&member_or_nonmember::member_or_nonmember::static_throw_or_not_argument, 1, b, c);
    }
};

GCTEST_CASE(fail_assert_member_throws_1)
{
    gctest_case_config(fail_assert_member_throws_1, 227);
    gctest_case_description("gctest should fail if assertion not throws from public instance void method");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_member_throws(&member, &member_or_nonmember::member_or_nonmember::not_throw_void);
    }
};

GCTEST_CASE(fail_assert_member_throws_2)
{
    gctest_case_config(fail_assert_member_throws_2, 228);
    gctest_case_description("gctest should fail if assertion not throws from public instance parametered method");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_member_throws(&member, &member_or_nonmember::member_or_nonmember::throw_or_not_argument, 2, b, c);
    }
};

GCTEST_CASE(fail_assert_member_not_throws_1)
{
    gctest_case_config(fail_assert_member_not_throws_1, 229);
    gctest_case_description("gctest should fail if assertion throws from public instance void method");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_member_not_throws(&member, &member_or_nonmember::member_or_nonmember::throw_void);
    }
};

GCTEST_CASE(fail_assert_member_not_throws_2)
{
    gctest_case_config(fail_assert_member_not_throws_2, 230);
    gctest_case_description("gctest should fail if assertion throws from public instance parametered method");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        assert_member_not_throws(&member, &member_or_nonmember::member_or_nonmember::throw_or_not_argument, 1, b, c);
    }
};
