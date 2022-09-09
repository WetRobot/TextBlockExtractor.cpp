#include <string>
#include <functional>

namespace extract{
void extract(
    std::string                                             &file_path,
    std::function<bool(std::string)>                        &doc_begins,
    std::function<bool(std::string)>                        &doc_includes,
    std::function<bool(std::string line, std::string key)>  &doc_ends,
    std::function<bool(std::string)>                        &doc_ended,
    std::function<bool(std::string)>                        &key_allowed,
    std::function<std::string(std::string)>                 &key_extract,
    std::function<std::string(std::string)>                 &line_extract,
    std::function<void(std::string line, std::string key)>  &line_store,
    std::function<void(int line_no,std::string key,bool is_first)> &line_no_store
);
}