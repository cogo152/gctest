#ifndef GCTEST_CORE_SOURCE_LOCATION_HPP
#define GCTEST_CORE_SOURCE_LOCATION_HPP

#include <cstdint>

namespace std
{
    struct source_location
    {
    public:
        static constexpr source_location current(const char *fileName = __builtin_FILE(),
                                                 const char *functionName = __builtin_FUNCTION(),
                                                 const uint_least32_t lineNumber = __builtin_LINE(),
                                                 const uint_least32_t columnOffset = 0) noexcept
        {
            return source_location(fileName, functionName, lineNumber, columnOffset);
        }

        source_location(const source_location &) = default;
        source_location(source_location &&) = default;

        constexpr const char *file_name() const noexcept
        {
            return fileName;
        }

        constexpr const char *function_name() const noexcept
        {
            return functionName;
        }

        constexpr uint_least32_t line() const noexcept
        {
            return lineNumber;
        }

        constexpr std::uint_least32_t column() const noexcept
        {
            return columnOffset;
        }

    private:
        constexpr source_location(const char *fileName, const char *functionName, const uint_least32_t lineNumber,
                                  const uint_least32_t columnOffset) noexcept
            : fileName(fileName), functionName(functionName), lineNumber(lineNumber), columnOffset(columnOffset)
        {
        }

        const char *fileName;
        const char *functionName;
        const std::uint_least32_t lineNumber;
        const std::uint_least32_t columnOffset;
    };

}

#endif