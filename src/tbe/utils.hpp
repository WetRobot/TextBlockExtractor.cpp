#ifndef UTILS
#define UTILS
#include <string>
#include <vector>

namespace utils{
template<typename T>
int match(T &x, std::vector<T> &y) {
    int m = -999;
    int i = -1;
    for (T y_elem : y) {
        i += 1;
        if (x == y_elem) {
            m = i;
            break;
        }
    }
    return(m);
} 

template<typename T>
bool is_in(T &x, std::vector<T> &y) {
    return(match(x, y) != -999);
}
}

#endif // UTILS