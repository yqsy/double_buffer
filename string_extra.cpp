#include "string_extra.h"


bool GetSplitStringPosition(const std::string& str, const std::string& separate, int position, std::string* out) {
    if (out == NULL || position <= 0)
        return false;

    *out = "";

    const size_t len = separate.length();

    std::string::size_type begin = 0;
    std::string::size_type pos = 0;

    int current_position = 0;

    do {
        pos = str.find(separate, begin);
        if (pos != std::string::npos) {
            std::string sub_rtn = str.substr(begin, pos - begin);
            begin = pos + len;
            current_position++;

            if (current_position == position) {
                *out = sub_rtn;
                return true;
            }
        }
    } while (pos != std::string::npos);

    std::string endstr = str.substr(begin);
    if (endstr != "") {
        current_position++;

        if (current_position == position) {
            *out = endstr;
            return true;
        }
    }

    return false;
}
