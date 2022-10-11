#ifndef STORE
#define STORE

#include <string>
#include <vector>
#include <fstream>

namespace store{
auto factory_store_line_to_filesystem(std::string output_dir_path) {
    return [&](std::string &line, std::string &key) -> void 
    {
        std::string output_file_path = output_dir_path + key + ".txt";
        std::fstream file_conn;
        file_conn.open(output_file_path, std::ios_base::app | std::ios_base::in);
        if (file_conn.is_open()) {
            file_conn << line << std::endl;
        }
    };
}

auto factory_store_line_no_to_filesystem(std::string output_dir_path) {
    return [&](int &line_no, std::string &key, bool &is_end) 
    {
        std::string output_file_path = output_dir_path + key + ".txt";
        std::fstream file_conn;
        file_conn.open(output_file_path, std::ios_base::app | std::ios_base::in);
        if (file_conn.is_open()) {
            file_conn << line_no << std::endl;
        }
    };
}
}
#endif
