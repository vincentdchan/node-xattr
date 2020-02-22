#pragma once

#include <napi.h>
#include <string>
#include "mac_utils.h"

class SetXAttrWorker : public Napi::AsyncWorker {
public:
  SetXAttrWorker(Napi::Function& callback, std::string path, std::string name, std::vector<char> buffer)
  : AsyncWorker(callback), path_(std::move(path)), name_(std::move(name)), buffer_(std::move(buffer)) {}

  void Execute() override {
    std::string error_msg;
    if (!utils::SetXAttr(path_, name_, buffer_.data(), buffer_.size(), error_msg)) {
      SetError(error_msg);
    }
  }

  void OnOK() override {
    Napi::HandleScope scope(Env());
    Callback().Call({});
  }

private:
  std::string path_;
  std::string name_;
  std::vector<char> buffer_;

};

class GetXAttrWorker : public Napi::AsyncWorker {
public:
  GetXAttrWorker(Napi::Function& callback, std::string path, std::string name)
  : AsyncWorker(callback), path_(std::move(path)), name_(std::move(name)) {}

  void Execute() override {
    std::string error_msg;
    if (!utils::GetXAttr(path_, name_, buffer_, error_msg)) {
      SetError(error_msg);
    }
  }

  void OnOK() override {
    Napi::HandleScope scope(Env());
    auto buffer = Napi::Buffer<char>::Copy(Env(), buffer_.data(), buffer_.size());
    Callback().Call({ Env().Undefined(), buffer });
  }

private:
  std::string path_;
  std::string name_;
  std::vector<char> buffer_;

};

class RemoveXAttrWorker : public Napi::AsyncWorker {
public:
  RemoveXAttrWorker(Napi::Function& callback, std::string path, std::string name)
  : AsyncWorker(callback), path_(std::move(path)), name_(std::move(name)) {}

  void Execute() override {
    std::string error_msg;
    if (!utils::RemoveXAttr(path_, name_, error_msg)) {
      SetError(error_msg);
    }
  }

  void OnOK() override {
    Napi::HandleScope scope(Env());
    Callback().Call({});
  }

private:
  std::string path_;
  std::string name_;

};

class ListXAttrWorker : public Napi::AsyncWorker {
public:
  ListXAttrWorker(Napi::Function& callback, std::string path)
  : AsyncWorker(callback), path_(std::move(path)) {}

  void Execute() override {
    std::string error_msg;
    if (!utils::ListXAttr(path_, result_, error_msg)) {
      SetError(error_msg);
    }
  }
  
  void OnOK() override {
    Napi::HandleScope scope(Env());
    Napi::Array result = Napi::Array::New(Env());

    for (std::size_t i = 0; i < result_.size(); i++) {
      const auto& item_name = result_[i];
      result[i] = Napi::String::New(Env(), item_name);
    }

    Callback().Call({ Env().Undefined(), result });
  }

private:
  std::string path_;
  std::vector<std::string> result_;

};

class SetCustomIconForFileWorker : public Napi::AsyncWorker {
public:
  SetCustomIconForFileWorker(Napi::Function& callback, std::string file_path, std::string icon_path)
  : AsyncWorker(callback), file_path_(std::move(file_path)), icon_path_(icon_path) {}

  void Execute() override {
    std::string error_msg;
    if (!utils::SetCustomIconForFile(file_path_, icon_path_, error_msg)) {
      SetError(error_msg);
    }
  }

  void OnOK() override {
    Napi::HandleScope scope(Env());
    Callback().Call({});
  }

private:
  std::string file_path_;
  std::string icon_path_;

};
