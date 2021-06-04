#pragma once

// Std
#include <exception>
#include <functional>
#include <iostream>
#include <unordered_map>

// Catch2


namespace utils {

//! Creating my own testCase class was insightful and fun, especially regarding c++ templates
//! But the solution ended up more complex than I'd like, so I settled on using Catch2 unittest framework instead.
// enum TestResult : int
// {
//     FAILED,
//     SUCCESS,
//     EXCEPTION,
//     BAD_FUNC
// };

// const std::unordered_map<TestResult, std::string> TestResultNames {
//     {FAILED     , "Failed"},
//     {SUCCESS    , "Success"},
//     {EXCEPTION  , "Exception"},
//     {BAD_FUNC   , "Bad function call"}
// };

// template <typename InputType, typename ResultType>
// class MyTestCase {
//   public:
//     explicit MyTestCase( std::function<ResultType(InputType)> func, const InputType& input, const ResultType& result )
//       : _input(input), _expectedResult(result), _func( func ) {}
//     ~MyTestCase() {}

//     TestResult verify() {
//         try {
//             if( _func( _input ) == _expectedResult) {
// 		        return SUCCESS;
// 	        } else {
// 		        return FAILED;
// 	        }
//         }
//         catch( const std::bad_function_call& e ){
//             std::cout << e.what() << std::endl;
//             return BAD_FUNC;
//         }
//         catch( const std::exception& e ) {
// 	        std::cout << e.what() << std::endl;
// 	        return EXCEPTION;
// 	    }
//         catch(...) {
//             // This scenario should never happen, so print what we were doing when it did. 
// 		    std::cout << "Encountered severe error in testcase:" << std::endl
//                  << "\t" << typeid(this).name() << std::endl;
//             throw;
// 	    }
//     };

//   protected:
//     InputType _input;
//     std::function<ResultType(InputType)> _func;
//     ResultType _expectedResult;
// };

}