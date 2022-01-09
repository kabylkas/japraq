/*
 * Copyright (c) 2021-2022 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef SYNAQ_H_
#define SYNAQ_H_

// C++ libraries.
#include <iostream>
#include <string>
#include <sstream>

namespace synaq
{
    class Synaq
    {
    public:
        template <typename F>
        void Run(F func, std::string id)
        {
            try
            {
                std::cerr << "Starting " << id << "..." << std::endl;
                func();
                std::cerr << id << " passed." << std::endl;
            }
            catch(const std::exception& e)
            {
                tests_failed_++;
                std::cerr << id << " failed." << std::endl;
            }
        }

        Synaq() = default;
        ~Synaq()
        {
            if (tests_failed_ > 0)
            {
                std::cerr << "Some tests failed." << std::endl;
            }
        }


    private:
        int tests_failed_ = 0;
    };

    template <typename T>
    void assert_equal(T a, T b, int line)
    {
        if (a != b)
        {
            std::stringstream stream;
            stream << "[!] Assertion on line " << line << "failed.";
            throw std::runtime_error(stream.str());
        }
        else
        {
            std::cerr << "Assertion on line " << line << " passed." << std::endl;
        }
    }
} // namespace synaq

#define RUN_TEST(tr, function) (tr.Run(function, #function))
#define MUST_BE_EQUAL(a, b) (synaq::assert_equal(a, b, __LINE__))
#define REQUIRE(a) (synaq::assert_equal(a, true, __LINE__))

#endif // SYNAQ_H_