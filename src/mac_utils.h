#pragma once

#include <vector>
#include <sys/xattr.h>
#include <cstdlib>
#include <cstring>

namespace utils {

inline bool GetXAttr(const std::string& path, const std::string& name, std::vector<char>& data, std::string& error_msg) {
  ssize_t buffer_size = getxattr(path.c_str(), name.c_str(), nullptr, 0, 0, 0);

  if (buffer_size < 0) {
    error_msg = strerror(errno);
    return false;
  }

  data.resize(buffer_size);

  ssize_t receive_size = getxattr(path.c_str(), name.c_str(), data.data(), buffer_size, 0, 0);

  if (receive_size < 0) {
    error_msg = strerror(errno);
    return false;
  }

  return true;
}

inline bool SetXAttr(const std::string& path, const std::string& name, char* value, std::size_t size, std::string& error_msg) {
  int ret = setxattr(path.c_str(), name.c_str(), value, size, 0, 0);
  if (ret < 0) {
    error_msg = strerror(errno);
    return false;
  }
  return true;
}

inline bool ListXAttr(const std::string& path, std::vector<std::string>& result, std::string& error_msg) {
  ssize_t buffer_size = listxattr(path.c_str(), nullptr, 0, 0);
  if (buffer_size < 0) {
    error_msg = strerror(errno);
    return false;
  }

  std::vector<char> buffer;
  buffer.resize(buffer_size);
  char* buffer_ptr = buffer.data();

  ssize_t ret = listxattr(path.c_str(), buffer_ptr, buffer_size, 0);
  if (ret < 0) {
    error_msg = strerror(errno);
    return false;
  }

  ssize_t index = 0;
  while (index < buffer_size) {
    size_t str_len = strlen(buffer_ptr + index);
    std::string name(buffer_ptr + index, str_len);
    result.push_back(std::move(name));

    index += str_len + 1;
  }

  return true;
}

inline bool RemoveXAttr(const std::string& path, const std::string& name, std::string& error_msg) {
  int ret = removexattr(path.c_str(), name.c_str(), 0);
  if (ret < 0) {
    error_msg = strerror(errno);
    return false;
  }
  return true;
}

}

