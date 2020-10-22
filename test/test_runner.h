#pragma once
#include <iostream>
#include <string>

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

#define RUN_TEST(tr, function) (tr.run(function, #function))