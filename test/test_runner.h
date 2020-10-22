#pragma once
#include <iostream>
#include <string>
#include <sstream>

#define VERBOSE 0

class test_runner {
    private:
        int tests_failed;

    public:
        test_runner() {
            this->tests_failed = 0;
        }

        ~test_runner() {
            if (this->tests_failed > 0) {
                std::cerr << "Opps! Tests failed!" << std::endl;
            }
        }

        template <typename F>
        void run(F func, std::string id) {
            try
            {
                func();
                std::cerr << id << " passed" << std::endl;
            }
            catch(const std::exception& e)
            {
                ++this->tests_failed;
                std::cerr << id << " failed" << std::endl;
            }
            
        }
};

std::ostream& operator<<(std::ostream& os, const row_ptrs_t s) {
    for (auto e : s) {
        os << e << ' ';
    }
    return os;
}

template <typename T>
void assert_equal(T a, T b, int line) {
    if (a != b) {
        std::stringstream ss;
        ss << "Assertion failed on line " << line;
        throw std::runtime_error(ss.str());
    } 
    #if VERBOSE
    else 
    {
        std::cerr << "Assertion on line " << line << " passed" << std::endl;
    }
    #endif
}

#define RUN_TEST(tr, function) (tr.run(function, #function))
#define MUST_BE_EQUAL(a, b) (assert_equal(a, b, __LINE__))