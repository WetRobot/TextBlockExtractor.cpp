
#include <iostream>
#include <vector>

#include "tse/extract.hpp"
#include "tse/store.hpp"
#include "tse/utils.hpp"

int main(int argc, char* argv[]) {
    int m_x = 0;
    std::vector<int> m_y(3);
    m_y[0] = 2;
    m_y[1] = 1;
    m_y[2] = 0;
    auto m = utils::match(m_x, m_y);
    if (m != 2) {
        std::printf("utils::match broken\n");
    } else {
        std::printf("utils::match worked\n");
    }
    if (!utils::is_in(m_x, m_y)) {
        std::printf("utils::is_in broken\n");
    } else {
        std::printf("utils::is_in worked\n");
    }
    // TODO: need to implement block vs chunk section end detection.
    // block: end when the same key is found for the second time.
    // chunk: end when 
    extract_bl_ch_with_re_into_fs(
        "examples/input1.cpp",
        std::regex("[ ]*//"),
        std::regex("[ ]*//"),
        std::regex("(^[ ]*//[ ]*@[a-z]+[ ]+)(.+)($)"),
        std::regex("(^[ ]*//[ ]*)(.+)($)"),
        "./out/"
    )
    return(0);
}
