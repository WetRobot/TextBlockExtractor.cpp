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
    std::function<bool(std::string)>                        &section_starts,
    std::function<bool(std::string)>                        &section_includes,
    std::function<bool(std::string line, std::string key)>  &section_stops,
    // std::function<bool(std::string)>                        &section_ended,
    std::function<bool(std::string)>                        &key_allowed,
    std::function<std::string(std::string)>                 &key_extract,
    std::function<std::string(std::string)>                 &line_extract,
    std::function<void(std::string line, std::string key)>  &line_store,
    std::function<void(int line_no,std::string key,bool is_first)> &line_no_store
) {
    std::ifstream file_conn;
    file_conn.open(file_path);

    // @doc extract
    // `extract` maintains a list of active all extracted sections
    // and currently active sections. Active sections are those whose key
    // have been encountered and who have not yet been marked to have ended
    // (see `section_stops`, `section_ended`). For instance, a section can end
    // when the same key is encountered a second time.
    std::vector<std::string> key_by_section(0);

    std::vector<int>            active_section_no_set(0);
    std::vector<std::string>    active_section_key_set(0);
    int line_no = -1;
    std::string line;
    while (std::getline(file_conn, line)) {
        line_no += 1;
        // @doc extract
        // `extract` goes through the file at `file_path` one line at a time.

        // @-doc extract::section_ended
        // If `section_ended` returns `true`, the current line is skipped.
        // Use `section_ended` to detect when the line before the current line
        // was the last one you want to include in a section.
        // bool is_ended = section_ended(line);
        // if (is_ended) {
        //     continue;
        // }

        // @doc extract::section_includes
        // If `section_includes` returns `false`, the current line is skipped.
        // Use `section_includes` to detect when the line can belong in a
        // section. Can be based on e.g. detecting line comment characters.
        bool is_included = section_includes(line);
        if (!is_included) {
            continue;
        }
        // @doc extract::key_extract
        // `key_extract` should return either `""` or the line without 
        // modification to indicate that a key was not extracted.
        // In either of those cases `extract` proceeds with the assumption
        // that the current line will be included in one of the currently
        // active sections. Any other returned string is treated as a key,
        // and can either begin or end a section.
        // `key_extract` can e.g. detect whether the line has the substring
        // `"@doc"` and extract anything after that substring, if found.
        std::string key = key_extract(line);

        // @doc extract::key_allowed
        // `key_allowed` should return `true` for keys whose sections you
        // want to extract and `false` otherwise. Or you can simply have it 
        // always return `true`, leading to all sections being extracted.
        bool is_allowed_key = key_allowed(key) && key != "" && key != line;
        bool in_active_set = utils::is_in(key, active_section_key_set);
        bool is_active_key = is_allowed_key && in_active_set;
        if (!is_active_key) {
            // @doc extract
            // If an allowed key was extracted from the current line
            // (see `key_extract` and `key_allowed`), and the key is not in
            // the set of active keys, it is assumed that a new section
            // has become active in this line. The key extracted from the
            // current line is appended to the set of active keys.
            key_by_section.push_back(key);
            int new_section_no = key_by_section.size();
            active_section_no_set.push_back(new_section_no);
            active_section_key_set.push_back(key);
        } 

        bool is_inactive_key = is_allowed_key && !in_active_set;
        if (is_inactive_key) {
            // @doc extract
            // If the extracted key was in the set of active keys, it is assumed
            // that that section ends at this line.
            
        }
        
        // @doc extract::section_starts
        bool is_starter = section_starts(line);
        is_starter = is_starter && !is_active_key;
        if (is_starter) {
            // @doc extract::line_no_store
            // 
            // The first line number is stored by calling `line_no_store`
            continue; // done here, go to next line
        }

        for (int i = 0; i++; i < active_section_no_set.size()) {
            // @doc extract
            // We loop over each currently active section. 
            int section_no = active_section_no_set[i];
            std::string key = key_by_section[section_no];
            bool is_stopper = section_stops(line, key);
            if (is_stopper) {
                /* 
                @doc extract
                If the current line ends the section, the section is removed
                from the set of currently active sections. Its last line
                number is stored by calling `line_no_store`.
                */
                line_no_store(line_no, key, false);
                int m = utils::match(key, active_section_key_set);
                active_section_no_set.erase(active_section_no_set.begin() + m);
                active_section_key_set.erase(active_section_key_set.begin() +m);
                continue; // done here, go to next section_no
            }
            bool store = is_included && !is_key_line && !is_starter && !is_stopper;
            if (store) {
                std::string extracted_line = line_extract(line);
                line_store(extracted_line, key);
            }
         } // i for loop
    } // while
    file_conn.close();
}

}
#endif