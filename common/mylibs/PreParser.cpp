#include "PreParser.hpp"

ParsedCMD PreParse(const std::string str) {
    ParsedCMD temp;
    int start, end = -1;
    int flag = 0;
    do {
        start = end + 1;
        end = str.find(" ", start);
        if (flag == 0) {
            temp.title = str.substr(start, end - start);
            flag = 1;
        } else {
            temp.args.push_back(str.substr(start, end - start));
        }

    } while (end != -1);
    return temp;
};
