#include <gctest/core/assertion.hpp>

namespace gctest
{
    namespace core
    {
        namespace assertion
        {
            void case_fail(const std::source_location &sourceLocation)
            {
                std::stringstream stream;
                stream << "Assertion\t: Actual value = "
                       << "Statetment failed"
                       << " <case_fail> "
                       << "Expected value = "
                       << "Statetment successful"
                       << "," << std::endl
                       << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                       << "\t\tLine\t\t: " << sourceLocation.line();

                throw gctest::core::exception::TestCaseException(stream.str());
            }

            void suit_fail(const std::source_location &sourceLocation)
            {
                std::stringstream stream;
                stream << "Assertion\t: Actual value = "
                       << "Statetment failed"
                       << " <suit_fail> "
                       << "Expected value = "
                       << "Statetment successful"
                       << "," << std::endl
                       << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                       << "\t\tLine\t\t: " << sourceLocation.line();

                throw gctest::core::exception::TestSuitException(stream.str());
            }
        }

    }

}