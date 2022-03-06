#ifndef USER_INFO_H
#define USER_INFO_H

#include <unordered_map>
#include <string>

// IMPORT_USER

#ifdef IMPORT_USER

std::unordered_map<std::string, std::string> UserLoginInfo;

inline void InitUserInfo()
{
    UserLoginInfo["a"]="a";
    UserLoginInfo["b"]="b";
    UserLoginInfo["c"]="c";
    UserLoginInfo["d"]="d";
}

#else

extern std::unordered_map<std::string, std::string> UserLoginInfo;

#endif

#endif