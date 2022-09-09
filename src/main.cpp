
#include <iostream>
#include <vector>

#include "tbe/extract.hpp"
#include "tbe/store.hpp"
#include "tbe/utils.hpp"

int main(int argc, char* argv[]) {
    int m_x = 0;
    std::vector<int> m_y = {2,1,0};
    auto m = utils::match(m_x, m_y);
    if (m != 2) {
        std::printf("utils::match broken\n");
    }
    std::printf("hello world!\n");
    return(0);
}
