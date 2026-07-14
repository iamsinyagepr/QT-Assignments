#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <regex>


//is valid author name format
inline bool isValidAuthorFormat(const std::string& input) {
    std::regex pattern(R"(^[A-Z]{1,}\s[A-Za-z]+(-[A-Za-z]+)*$)");
    return std::regex_match(input, pattern);
}

//is valid journal or title format

inline bool isValidJournalOrTitleFormat(const std::string& input) {
    std::regex pattern(R"(^[A-Za-z]+(\s+[A-Za-z]+|\s+[0-9]+)*$|^[0-9]+(\s+[A-Za-z]+|\s+[0-9]+)*$)");
    return std::regex_match(input, pattern);
}

// is valid pages format
inline bool isValidPagesFormat(const std::string& input) {
    std::regex pattern(R"(^\d+\s*-\s*\d+$)");

    return std::regex_match(input, pattern);
}

#endif // VALIDATORS_H
