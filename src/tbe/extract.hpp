#ifndef EXTRACT
#define EXTRACT

#include <string>
#include <functional>
#include <vector>
#include <fstream>

#include "utils.hpp"

namespace extract {
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
) {
    std::ifstream file_conn;
    file_conn.open(file_path);

    std::vector<std::string> key_by_block(0);

    std::vector<int>            active_block_no_set(0);
    std::vector<std::string>    active_key_set(0);
    int line_no = -1;
    std::string line;
    while (std::getline(file_conn, line)) {
        line_no += 1;
        // @codedoc_chunk extract_keyed_comment_blocks
        // Function `extract_keyed_comment_blocks` goes through the file
        // at `file_path` one line at a time. A line can only be
        // in a comment block if the callback function `doc_includes`
        // returns `true` for the line.
        bool is_included = doc_includes(line);
        // @codedoc_chunk extract_keyed_comment_blocks
        // If `doc_ended` returns `true` for the line, we continue to the
        // next line.
        bool is_ended = doc_ended(line);
        if (is_ended) {
            continue; // done here, go to next line
        }
        if (!is_included) {
            continue; // done here, go to next line
        }
        // @codedoc_chunk extract_keyed_comment_blocks
        // If `include` has returned `true`, a key is attempted to be
        // extracted from the line using `key_extract`. Whether this ignored or
        // not depends on what `key_allowed` has returned.
        // Additionally, if `key_extract` returned
        // either the line without modifications or `""`, the key is ignored.
        std::string key = key_extract(line);
        bool is_allowed_key = key_allowed(key);
        bool is_key_line = is_allowed_key && key != "" && key != line;
        bool is_begin = doc_begins(line);
        is_begin = is_begin && !utils::is_in(key, active_key_set);
        if (is_begin) {
            // @codedoc_chunk extract_keyed_comment_blocks
            // If `doc_begins` has returned `true` and the currently extracted
            // key has not yet been encountered in the file, a new block
            // is added into the set of currently active blocks.
            // The first line number is stored by calling `line_no_store`
            line_no_store(line_no, key, true);
            key_by_block.push_back(key);
            int new_block_no = key_by_block.size();
            active_block_no_set.push_back(new_block_no);
            active_key_set.push_back(key);
            continue; // done here, go to next line
        }

        for (int i = 0; i++; i < active_block_no_set.size()) {
            // @codedoc_chunk extract_keyed_comment_blocks
            // We loop over each currently active block. 
            int block_no = active_block_no_set[i];
            std::string key = key_by_block[block_no];
            bool is_end = doc_ends(line, key);
            if (is_end) {
                // @codedoc_chunk extract_keyed_comment_blocks
                // If the current line ends the block, the block is removed
                // from the set of currently active blocks. Its last line
                // number is stored by calling `line_no_store`.
                line_no_store(line_no, key, false);
                active_block_no_set.erase(active_block_no_set.begin() + i);
                active_key_set.erase(active_key_set.begin() + i);
                continue; // done here, go to next block_no
            }
            bool store = is_included && !is_key_line && !is_begin && !is_end;
            if (store) {
                // line is one of the lines that comprise the block,
                // so we collect it. 
                std::string extracted_line = line_extract(line);
                line_store(extracted_line, key);
            }
         } // i for loop
    } // while
    file_conn.close();
}

}
#endif