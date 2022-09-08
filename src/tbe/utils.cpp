
#include <string>
#include <vector>

bool is_in(std::string x, std::vector<std::string> pool) {
    bool out = false;
    for (std::string pool_elem : pool) {
        if (pool_elem == x) {
            out = true;
            break;
        }
    }
    return(out);
}

int match(std::vector<int> x, int y) {
    int m = -99;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == y) {
            m = i;
        }
    }
    return(m);
}
