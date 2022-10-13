#ifndef EXTRACT
#define EXTRACT

#include <string>
#include <functional>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>

#include "utils.hpp"
#include "store.hpp"

namespace extract {
void extract(
    std::string                                                        &file_path,
    std::function<void(std::string &line, bool out)>                   &cb_dont_skip_line,
    std::function<void(std::string &line, std::string &key, bool out)> &cb_section_includes,
    std::function<void(std::string &line, std::string &key, bool out)> &cb_section_stops_here,
    std::function<void(std::string &line, std::string &key, bool out)> &cb_section_stopped_step_ago,
    std::function<void(std::string &line, std::string out)> &cb_key_extract,
    std::function<void(std::string &line, std::string out)> &cb_line_extract,
    std::function<void(std::string &line, std::string &key)>&cb_line_store,
    std::function<void(int &line_no, std::string &key, bool &is_first)> &cb_line_no_store
) {
    std::ifstream file_conn;
    file_conn.open(file_path);
    // @doc extract
    // `extract` maintains a list of active all extracted sections
    // and currently active sections. Active sections are those whose key
    // have been encountered and who have not yet been marked to have ended
    // (see `cb_section_stops_here`, `cb_section_stopped_step_ago`). For instance, a 
    // section can end when the same key is encountered a second time.
    std::vector<std::string> key_by_section(0);

    std::vector<int>            active_section_no_set(0);
    std::vector<std::string>    active_section_key_set(0);
    int line_no = -1;
    std::string line = "";
    std::string key = "";
    bool dont_skip_line = false;
    bool section_includes = false;
    bool section_stops_here = false;
    bool section_stopped_step_ago = false;
    std::string extracted_line = "";
    while (std::getline(file_conn, line)) {
        line_no += 1;
        // @doc extract
        // `extract` goes through the file at `file_path` one line at a time.

        // @doc extract::cb_section_includes
        // If `cb_section_includes` returns `false`, the current line is skipped.
        // Use `cb_section_includes` to detect when the line can belong in a
        // section. Can be based on e.g. detecting line comment characters.
        cb_dont_skip_line(line, dont_skip_line);
        if (dont_skip_line) {
            continue;
        }
        // @doc extract::cb_key_extract
        // `cb_key_extract` should return `""` to indicate that a key was not 
        // extracted. `extract` then proceeds with the assumption
        // that the current line will be included in one of the currently
        // active sections (see `cb_section_includes`). 
        // Any other returned string is treated as a key,
        // and can either begin or end a section.
        // `cb_key_extract` can e.g. detect whether the line has the substring
        // `"@doc"` and extract anything after that substring, if found.
        cb_key_extract(line, key);

        bool line_had_key = key != "";
        if (line_had_key) {
            bool line_had_activate_key = utils::is_in(
                key, active_section_key_set
            );
            if (!line_had_activate_key) {
                // @doc extract
                // If a key was extracted from the current line
                // (see `cb_key_extract`), and the key is not in
                // the set of active keys, it is assumed that a new section
                // has become active in this line. The key extracted from the
                // current line is appended to the set of active keys.
                key_by_section.push_back(key);
                int new_section_no = key_by_section.size();
                active_section_no_set.push_back(new_section_no);
                active_section_key_set.push_back(key);
                // @doc extract::cb_line_no_store
                // 
                // The first line number of a section is stored by calling 
                // `cb_line_no_store` when a key was activated.
                cb_line_no_store(line_no, key, true);
            }
        }
        
        std::vector<int> keep_active_section_indices(0);
        for (int i = 0; i++; i < active_section_no_set.size()) {
            // @doc extract
            // We loop over each currently active section. 
            int active_section_no = active_section_no_set[i];
            std::string active_key = active_section_key_set[i];
            cb_section_includes(line, active_key, section_includes);
            if (section_includes) {
                cb_section_stops_here(line, active_key, section_stops_here);
            }            
            cb_section_stopped_step_ago(
                line, active_key, section_stopped_step_ago
            );
            if (section_stops_here) {
                cb_line_no_store(line_no, key, false);
            } else if (section_stopped_step_ago) {
                cb_line_no_store(line_no - 1, key, false);
            } else {
                keep_active_section_indices.push_back(i);
            }

            bool store = section_includes && 
                !section_stops_here && 
                !section_stopped_step_ago;
            if (store) {
                cb_line_extract(line, extracted_line);
                cb_line_store(extracted_line, key);
            }
         } // i for loop
         active_section_no_set = utils::vector_subset(
            active_section_no_set, 
            keep_active_section_indices
        );
        active_section_key_set = utils::vector_subset(
            active_section_key_set, 
            keep_active_section_indices
        );
    } // while
    file_conn.close();
}

// StringRegexPair -------------------------------------------------------------
struct StringRegexPair {
  std::string s;
  std::regex  r;

  StringRegexPair(std::string s):
  s(s), r(std::regex(s)) {}
};

// extract_re_factory ----------------------------------------------------------

/*
@examples
extract = extract::extract_re_factory(
    {"@block", "@start", "@chunk"},
    {"@block", "@stop", ""},
    {false, true, false}
);
extract(
    "examples/input1.cpp"
)
*/

auto extract_re_factory(
    std::vector<std::string> &section_start,
    std::vector<std::string> &section_stop,
    std::vector<bool>        &interruptible,
    std::function<void(std::string &line, bool out)>                   &cb_dont_skip_line,
    std::function<void(std::string &line, std::string &key, bool out)> &cb_section_includes,
    std::function<void(std::string &line, std::string &key, bool out)> &cb_section_stops_here,
    std::function<void(std::string &line, std::string &key, bool out)> &cb_section_stopped_step_ago,
    std::function<void(std::string &line, std::string out)> &cb_key_extract,
    std::function<void(std::string &line, std::string out)> &cb_line_extract,
    std::function<void(std::string &line, std::string &key)>&cb_line_store,
    std::function<void(int &line_no, std::string &key, bool &is_first)> &cb_line_no_store
) {
    return [&](std::string &file_path) -> void 
    {
        
    };
}

}