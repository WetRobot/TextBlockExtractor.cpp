#include <string>
#include <vector>
#include <fstream>

void store_line_to_filesystem(
    std::string line,
    std::string key
) {
    std::string output_file_path = "./output/" + key + ".txt";
    std::fstream file_conn;
    file_conn.open(output_file_path, std::ios_base::app | std::ios_base::in);
    if (file_conn.is_open()) {
        file_conn << line << std::endl;
    }
}

void store_line_no_to_filesystem(
    int line_no,
    std::string key,
    bool is_end
) {
    std::string output_file_path = "./output/" + key + ".txt";
    std::fstream file_conn;
    file_conn.open(output_file_path, std::ios_base::app | std::ios_base::in);
    if (file_conn.is_open()) {
        file_conn << line_no << std::endl;
    }
}
