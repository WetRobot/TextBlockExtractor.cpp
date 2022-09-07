
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <regex>


// using regexes ---------------------------------------------------------------
std::string __COMMENT_LINE_CPP_PREFIX = "[ ]*[/]{2,}[ ]*";
std::regex __COMMENT_LINE_CPP_PREFIX_REGEX = std::regex(__COMMENT_LINE_CPP_PREFIX);
std::string __COMMENT_LINE_CPP_CONTENT = ".*$";
std::regex __COMMENT_LINE_CPP_CONTENT_REGEX = std::regex(__COMMENT_LINE_CPP_CONTENT);
std::regex __COMMENT_LINE_CPP_REGEX = std::regex(
    "^(" + __COMMENT_LINE_CPP_PREFIX + ")(" + __COMMENT_LINE_CPP_CONTENT + ")"
);
bool detect_comment_line_cpp(std::string line) {
    return(std::regex_match(line, __COMMENT_LINE_CPP_REGEX));
}
std::string clean_comment_line_cpp(std::string line) {
    return(std::regex_replace(line, __COMMENT_LINE_CPP_PREFIX_REGEX, ""));
}
std::string __KEY_PREFIX_CPP = __COMMENT_LINE_CPP_PREFIX + "@codedoc_comment_block[ ]+";
std::regex __KEY_PREFIX_CPP_REGEX = std::regex(__KEY_PREFIX_CPP);
std::string extract_key_cpp(std::string line) {
    return(std::regex_replace(line, __KEY_PREFIX_CPP_REGEX, ""));
}
void store_line_to_console(std::string line, std::string key) {
    std::cout << "key = " << key << "; line = " << line << "\n";
}
void extract_keyed_comment_blocks_using_regexes(
    std::string file_path
) {
    extract_keyed_comment_blocks(
        file_path,
        detect_comment_line_cpp,
        clean_comment_line_cpp,
        extract_key_cpp,
        store_line_to_console
    );
}

int main() { 
    extract_keyed_comment_blocks_using_regexes("examples/input1.cpp");    
    return(0);
}
