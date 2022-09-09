#include <string>
#include <vector>
#include <fstream>
#include <functional>

auto store_line_to_filesystem_factory(
    std::string output_dir_path
) {
    return [&](std::string line, std::string key) -> void 
    {
        std::string output_file_path = output_dir_path + key + ".txt";
        std::fstream file_conn;
        file_conn.open(output_file_path, std::ios_base::app | std::ios_base::in);
        if (file_conn.is_open()) {
            file_conn << line << std::endl;
        }
    };
}

auto store_line_no_to_filesystem_factory(
    std::string output_dir_path
) {
    return [&](int line_no, std::string key, bool is_end) 
    {
        std::string output_file_path = output_dir_path + key + ".txt";
        std::fstream file_conn;
        file_conn.open(output_file_path, std::ios_base::app | std::ios_base::in);
        if (file_conn.is_open()) {
            file_conn << line_no << std::endl;
        }
    };
}
