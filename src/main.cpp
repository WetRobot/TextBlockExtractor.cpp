
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

    extract::StringRegexPair srp = extract::StringRegexPair("wat");
    std::cout << srp.s << "\n";
    return(0);
}
