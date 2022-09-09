
#include <string>
#include <functional>

std::function<void(std::string line, std::string key)> store_line_to_filesystem_factory(
    std::string output_dir_path
);

std::function<void(int line_no, std::string key)> store_line_no_to_filesystem_factory(
    std::string output_dir_path
);
