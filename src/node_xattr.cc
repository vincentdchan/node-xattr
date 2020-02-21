#include <napi.h>
#include <vector>
#include <sys/xattr.h>

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

  int ret = setxattr(path.c_str(), name.c_str(), buffer_ptr, buffer_size, 0, 0);
  if (ret < 0) {
    std::string message = strerror(errno);
    throw Napi::Error::New(env, message);
  }

  return env.Undefined();
}

static Napi::Buffer<char> GetXattrSync(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (!info[0].IsString()) {
    throw Napi::Error::New(env, "The first argument must be a string");
  }

  if (!info[1].IsString()) {
    throw Napi::Error::New(env, "The second argument must be a string");
  }

  std::string path = info[0].As<Napi::String>().Utf8Value();
  std::string name = info[1].As<Napi::String>().Utf8Value();

  ssize_t buffer_size = getxattr(path.c_str(), name.c_str(), nullptr, 0, 0, 0);

  if (buffer_size < 0) {
    std::string message = strerror(errno);
    throw Napi::Error::New(env, message);
  }

  Napi::Buffer<char> buffer = Napi::Buffer<char>::New(env, buffer_size);

  ssize_t receive_size = getxattr(path.c_str(), name.c_str(), buffer.Data(), buffer_size, 0, 0);
  
  if (buffer_size < 0) {
    std::string message = strerror(errno);
    throw Napi::Error::New(env, message);
  }

  return buffer;
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "setXattrSync"),
              Napi::Function::New(env, SetXattrSync));
  exports.Set(Napi::String::New(env, "getXattrSync"),
              Napi::Function::New(env, GetXattrSync));
  return exports;
}

NODE_API_MODULE(node_xattr, Init)
