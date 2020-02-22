
#include "mac_utils.h"
#include <sys/stat.h>

#import "mac/GMFinderInfo.h"
#import "mac/GMResourceFork.h"

static constexpr char kFinderAppInfoXAttrKey[] = "com.apple.FinderInfo";
static constexpr char kAppleResourceForkXAttrKey[] = "com.apple.ResourceFork";

namespace utils {

bool GetXAttr(const std::string& path, const std::string& name, std::vector<char>& data, std::string& error_msg) {
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

bool SetXAttr(const std::string& path, const std::string& name, char* value, std::size_t size, std::string& error_msg) {
  int ret = setxattr(path.c_str(), name.c_str(), value, size, 0, 0);
  if (ret < 0) {
    error_msg = strerror(errno);
    return false;
  }
  return true;
}

bool ListXAttr(const std::string& path, std::vector<std::string>& result, std::string& error_msg) {
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

bool RemoveXAttr(const std::string& path, const std::string& name, std::string& error_msg) {
  int ret = removexattr(path.c_str(), name.c_str(), 0);
  if (ret < 0) {
    error_msg = strerror(errno);
    return false;
  }
  return true;
}

std::vector<char> GetCustomIconFinderInfoBuffer() {
  std::vector<char> result;

  GMFinderInfo* info = [GMFinderInfo finderInfo];

  NSNumber* flags = [NSNumber numberWithLong:kHasCustomIcon];
  [info setFlags:(UInt16)[flags longValue]];

  NSData* finalizedData = [info data];
  NSUInteger bufferSize = [finalizedData length];

  result.resize(bufferSize);
  memcpy(result.data(), [finalizedData bytes], bufferSize);

  return result;
}

bool GetCustomIconXattrBuffer(const std::string& iconPath, std::vector<char>& result) {
  NSString* nsIconPath = [NSString stringWithUTF8String:iconPath.c_str()];

  NSData *imageData = [NSData dataWithContentsOfFile:nsIconPath];
  if (imageData == nil) {
    return false;
  }

  GMResourceFork* resourceFork = [GMResourceFork resourceFork];
  [resourceFork addResourceWithType:'icns'
    resID:kCustomIconResource
    name:nil
    data:imageData];

  NSData* forkData = [resourceFork data];
  NSUInteger bufferSize = [forkData length];

  result.resize(bufferSize);
  memcpy(result.data(), [forkData bytes], bufferSize);
  
  return true;
}

bool SetCustomIconForFile(const std::string& file_path, const std::string& icon_path, std::string& error_msg) {
  struct stat _stat;
  if (stat(icon_path.c_str(), &_stat) < 0) {
    error_msg = "can not open file: " + icon_path;
    return false;
  }
  std::vector<char> icon_buffer;

  if (!GetCustomIconXattrBuffer(icon_path, icon_buffer)) {
    error_msg = "read icon content failed: " + icon_path;
    return false;
  }

  auto finder_info_buffer = GetCustomIconFinderInfoBuffer();

  if (!SetXAttr(file_path, kFinderAppInfoXAttrKey, finder_info_buffer.data(), finder_info_buffer.size(), error_msg)) {
    return false;
  }

  if (!SetXAttr(file_path, kAppleResourceForkXAttrKey, icon_buffer.data(), icon_buffer.size(), error_msg)) {
    return false;
  }

  return true;
}

std::vector<char> SerializeArrayOfString(const std::vector<std::string>& content) {
  NSMutableArray *array = [NSMutableArray arrayWithCapacity:content.size()];

  std::vector<char> result;

  for (const auto& item : content) {
    NSString* content = [NSString stringWithUTF8String:item.c_str()];
    [array addObject:content];
  }

  NSError *error;
  NSData *data = [NSPropertyListSerialization
    dataWithPropertyList:array
    format:NSPropertyListBinaryFormat_v1_0
    options:0 error:&error
  ];;
  NSUInteger dataSize = [data length];

  result.resize(dataSize);
  memcpy(result.data(), [data bytes], dataSize);

  return result;
}

std::vector<std::string> DeserializeArrayOfString(const char* value, std::size_t size) {
  std::vector<std::string> result;

  NSData* nsData = [NSData dataWithBytes:value length:size];

  NSError* error;
  NSArray* array = [NSPropertyListSerialization
    propertyListWithData:nsData
    options:NSPropertyListImmutable
    format:NULL error:&error
  ]; 

  for (NSUInteger i = 0; i < [array count]; i++) {
    NSObject* obj = [array objectAtIndex:i];
    NSString* str = (NSString*)obj;
    if (str == nil) {
      return result;
    }

    std::string item = std::string([str UTF8String]);
    result.push_back(std::move(item));
  }

  return result;
}

}
