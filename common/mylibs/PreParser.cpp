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


std::expected<ParsedCMD,std::string> PreParse(const std::string str) {
    ParsedCMD tempPC;
    std::string tmpTitle="";
    std::string tmpArgs="";
    for(const char tmpC: str){
        if( std::isspace(tmpC) and (tmpTitle!="") ){
            
        }
        else{
            tmpS+=tmpC;
        }     
    }
    return tempPC;
};
