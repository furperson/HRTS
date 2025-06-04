#include "PreParser.hpp"

#include <cctype>

// ParsedCMD PreParse(const std::string str) {
//     ParsedCMD temp;
//     int start, end = -1;
//     int flag = 0;
//     do {
//         start = end + 1;
//         end = str.find(" ", start);
//         if (flag == 0) {
//             temp.title = str.substr(start, end - start);
//             flag = 1;
//         } else {
//             temp.args.push_back(str.substr(start, end - start));
//         }

//     } while (end != -1);
//     return temp;
// };

std::expected<ParsedCMD, std::string> PreParse(const std::string& str) {
    const std::string& tmpStr = str+" ";
    ParsedCMD tempPC;
    bool titleFlag = true;
    bool argsTitleFlag = true;
    bool quotesFlag = false;
    OptionType optionType = OptionType::OTHER;
    std::string tmpTitle = "";
    std::string tmpArgs = "";
    for (const char tmpC : tmpStr) {
        if (not quotesFlag and std::isspace(tmpC) and tmpTitle!="") {
            if (titleFlag) {
                tempPC.title = tmpTitle;
                titleFlag = false;
                tmpTitle = "";
            } else {
                if(tmpTitle.length()<=2)
                    return std::unexpected(tmpTitle);
                if(tmpTitle.substr(0,2)=="--"){
                    if(not argsTitleFlag)
                        return std::unexpected(tmpTitle);
                    tempPC.secArgs.push_back(tmpTitle.substr(2,tmpTitle.size()-2));
                }
                else if(tmpTitle[0]=='-'){
                    if(argsTitleFlag)
                        return std::unexpected(tmpTitle);
                    tempPC.oneArgs[tmpTitle.substr(1,tmpTitle.size()-1)]=tmpArgs;
                    
                }
                else {
                    if(not argsTitleFlag)
                        return std::unexpected(tmpTitle);
                    tempPC.otherArgs.push_back(tmpTitle);
                }
                argsTitleFlag = true;
            }
        } else {
            if (titleFlag) {
                tmpTitle += tmpC;
            } else if (argsTitleFlag) { // reading option title
                if (tmpC == '=') {
                    argsTitleFlag = false;
                } else {
                    tmpTitle += tmpC;
                }
            } else if (tmpC == '"') { // reading args for option
                quotesFlag = not quotesFlag;
            } else {
                tmpArgs += tmpC;
            }
        }
    }

    if (quotesFlag)
        return std::unexpected(tmpTitle);
    return tempPC;
};
