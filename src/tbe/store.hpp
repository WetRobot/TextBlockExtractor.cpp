
#include <string>

void store_line_to_filesystem(
    std::string line,
    std::string key
);

void store_line_no_to_filesystem(
    int line_no,
    std::string key,
    bool is_end
);
