#include <gctest/core/gctest_registery.hpp>

#include <cstddef>
#include <cstdlib>

namespace gctest
{
    namespace registery
    {

        const std::size_t FunctionTestRegistery::_capacityVector = 50;

        FunctionTestRegistery::FunctionTestRegistery() : _capacity(_capacityVector), _size(0), _functionTestInfos(nullptr)
        {
            _functionTestInfos = new FunctionTestInfo[_capacity];
        }

        FunctionTestRegistery::~FunctionTestRegistery()
        {
            if (_functionTestInfos != nullptr)
            {
                delete[] _functionTestInfos;
            }
        }

        std::size_t FunctionTestRegistery::size() const
        {
            return _size;
        }

        void FunctionTestRegistery::add_step(gctest::type::function_test_t functionTest, std::string functionName)
        {
            if (_size == _capacity)
            {
                _capacity += _capacityVector;

                FunctionTestInfo *_temp = _functionTestInfos;

                _functionTestInfos = new FunctionTestInfo[_capacity];

                for (std::size_t i = 0; i < _size; i++)
                {
                    _functionTestInfos[i] = _temp[i];
                }

                delete[] _temp;
            }

            (_functionTestInfos + _size)->functionTest = functionTest;
            (_functionTestInfos + _size)->functionTestName = functionName;

            _size++;
        }

        void FunctionTestRegistery::add_result(std::size_t index, std::string functionTestResult)
        {
            (_functionTestInfos + index)->functionTestResult = functionTestResult;
        }

        const FunctionTestInfo &FunctionTestRegistery::get(std::size_t index) const
        {
            return *(_functionTestInfos + index);
        }

        FunctionTestRegistery *functionTestRegistery = nullptr;

    }

}
