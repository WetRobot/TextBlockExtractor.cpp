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

template<typename T>
std::vector<T> vector_subset(
    std::vector<T> &x, 
    std::vector<int> &keep_indices
) {
    std::vector<T> x_subset(keep_indices.size());
    for (int i = 0; i < keep_indices.size(); i++) {
        int keep_idx = keep_indices[i];
        x_subset[i] = x[keep_idx];
    }
    return(x_subset);
}
}

#endif // UTILS