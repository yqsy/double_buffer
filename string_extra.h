#ifndef string_extra_h__
#define string_extra_h__

#include <vector>
#include <string>

bool GetSplitStringPosition(const std::string& str, const std::string& separate, int position, std::string* out);

std::vector<std::string> split(const std::string& str, char c);

#endif // string_extra_h__