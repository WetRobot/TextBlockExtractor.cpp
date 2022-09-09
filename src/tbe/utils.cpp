
#include <string>
#include <vector>

namespace utils{
template<typename T, typename Allocator>
int match(T &x, std::vector<T, Allocator> &y) {
    int m = -999;
    for (int i = 0; i < y.size(); i++) {
        if (x == y[i]) {
            m = i;
            break;
        }
    }
    return(m);
} 

template<typename T, typename Allocator>
bool is_in(T &x, std::vector<T, Allocator> &y) {
    int m = match(x, y);
    bool out = m != -999;
    return(out);
}
}

// int main() {
//     int m_x = 0;
//     std::vector<int> m_y = {2,1,0};
//     auto m = utils::match(m_x, m_y);
//     if (m != 2) {
//         std::printf("utils::match broken\n");
//     } else {
//         std::printf("utils::match worked\n");
//     }
//     return(0);
// }
