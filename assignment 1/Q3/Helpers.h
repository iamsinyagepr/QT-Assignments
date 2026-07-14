#ifndef HELPERS_H
#define HELPERS_H

#include <regex>
#include <QStandardItemModel>

class QString;

inline bool isValidFormat(const std::string& input) {
    // \d+ matches one or more digits
    // \s* matches zero or more spaces
    // - matches the literal hyphen
    std::regex pattern(R"(^\d+\s*-\s*\d+$)");

    return std::regex_match(input, pattern);
}


inline void setTableHeader(QStandardItemModel* model, std::list<QString> headers) {
    int i = 0;
    for (const QString& title : headers) {
        model->setHeaderData(i, Qt::Horizontal, title);
        i++;
    }
}

// {"Author", "Year", "Title", "Journal", "Volume", "Issue"};
inline int getColumnIndex(std::string filter) {
    if(filter == "Author") return 0;
    if(filter == "Year") return 1;
    if(filter == "Title") return 2;
    if(filter == "Journal") return 3;
    if(filter == "Volume") return 4;
    if(filter == "Issue") return 5;

    return -1;
}

#endif // HELPERS_H
