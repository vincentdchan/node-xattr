#include <napi.h>
#include <vector>

#include "mac_utils.h"
#include "workers.h"

static Napi::Array ListXattrSync(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (!info[0].IsString()) {
    throw Napi::Error::New(env, "The first argument must be a string");
  }

  std::string path = info[0].As<Napi::String>().Utf8Value();

  ssize_t buffer_size = listxattr(path.c_str(), nullptr, 0, 0);
  if (buffer_size < 0) {
    std::string message = strerror(errno);
    throw Napi::Error::New(env, message);
  }

  std::vector<std::string> temp_result;
  std::string error_msg;

  if (!utils::ListXAttr(path, temp_result, error_msg)) {
    throw Napi::Error::New(env, error_msg);
  }

  Napi::Array result = Napi::Array::New(env);

  for (std::size_t i = 0; i < temp_result.size(); i++) {
    const auto& item_name = temp_result[i];
    result[i] = Napi::String::New(env, item_name);
  }

  return result;
}

static Napi::Value SetXattrSync(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (!info[0].IsString()) {
    throw Napi::Error::New(env, "The first argument must be a string");
  }

  if (!info[1].IsString()) {
    throw Napi::Error::New(env, "The second argument must be a string");
  }

  std::string path = info[0].As<Napi::String>().Utf8Value();
  std::string name = info[1].As<Napi::String>().Utf8Value();

  std::string buffer_str;
  Napi::Buffer<char> buffer_obj;

  char* buffer_ptr = nullptr;
  ssize_t buffer_size = 0;

  if (info[2].IsString()) {
    buffer_str = info[2].As<Napi::String>().Utf8Value();
    buffer_ptr = const_cast<char*>(buffer_str.c_str());
    buffer_size = buffer_str.size();
  } else if (info[2].IsBuffer()) {
    buffer_obj = info[2].As<Napi::Buffer<char>>();
    buffer_ptr = buffer_obj.Data();
    buffer_size = buffer_obj.Length();
  } else {
    throw Napi::Error::New(env, "The second argument must be either a string or a buffer");
  }

  std::string error_msg;
  if (!utils::SetXAttr(path.c_str(), name.c_str(), buffer_ptr, buffer_size, error_msg)) {
    throw Napi::Error::New(env, error_msg);
  }

  return env.Undefined();
}

static Napi::Value GetXattrSync(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (!info[0].IsString()) {
    throw Napi::Error::New(env, "The first argument must be a string");
  }

  if (!info[1].IsString()) {
    throw Napi::Error::New(env, "The second argument must be a string");
  }

  std::string path = info[0].As<Napi::String>().Utf8Value();
  std::string name = info[1].As<Napi::String>().Utf8Value();

  std::vector<char> temp_buffer;
  std::string error_msg;
  if (!utils::GetXAttr(path, name, temp_buffer, error_msg)) {
    throw Napi::Error::New(env, error_msg);
  }

  Napi::Buffer<char> buffer = Napi::Buffer<char>::Copy(env, temp_buffer.data(), temp_buffer.size());

  return buffer;
}

static Napi::Value RemoveXattrSync(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (!info[0].IsString()) {
    throw Napi::Error::New(env, "The first argument must be a string");
  }

  if (!info[1].IsString()) {
    throw Napi::Error::New(env, "The second argument must be a string");
  }

  std::string path = info[0].As<Napi::String>().Utf8Value();
  std::string name = info[1].As<Napi::String>().Utf8Value();
  std::string error_msg;

  if (!utils::RemoveXAttr(path, name, error_msg)) {
    throw Napi::Error::New(env, error_msg);
  }

  return env.Undefined();
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "listXattrSync"),
              Napi::Function::New(env, ListXattrSync));
  exports.Set(Napi::String::New(env, "setXattrSync"),
              Napi::Function::New(env, SetXattrSync));
  exports.Set(Napi::String::New(env, "getXattrSync"),
              Napi::Function::New(env, GetXattrSync));
  exports.Set(Napi::String::New(env, "removeXattrSync"),
              Napi::Function::New(env, RemoveXattrSync));
  return exports;
}

NODE_API_MODULE(node_xattr, Init)
