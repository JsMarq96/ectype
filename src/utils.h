#pragma once

#include <iostream>
#include <cassert>

inline void assert_msg(const bool is_true, const char* msg) {
    if (is_true) {
        std::cout << "ASSERT FAILED: " << msg << std::endl;
        assert(false);
    }
}