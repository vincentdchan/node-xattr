#pragma once

#include <vector>
#include <sys/xattr.h>
#include <sys/errno.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace utils {

bool GetXAttr(const std::string& path, const std::string& name, std::vector<char>& data, std::string& error_msg);

bool SetXAttr(const std::string& path, const std::string& name, char* value, std::size_t size, std::string& error_msg);

bool ListXAttr(const std::string& path, std::vector<std::string>& result, std::string& error_msg);

bool RemoveXAttr(const std::string& path, const std::string& name, std::string& error_msg);

std::vector<char> GetCustomIconFinderInfoBuffer();

bool GetCustomIconXattrBuffer(const std::string& iconPath, std::vector<char>&);

bool SetCustomIconForFile(const std::string& file_path, const std::string& icon_path, std::string& error_msg);

std::vector<char> SerializeArrayOfString(const std::vector<std::string>& content);

std::vector<std::string> DeserializeArrayOfString(const char* value, std::size_t size);

}
