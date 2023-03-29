#pragma once

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <string>

class JsonConfig {
public:
  static JsonConfig* getInstance();

  bool LoadFile(const std::string &fileName);
  bool SaveFile();
  ~JsonConfig();

  bool HasKey(const std::string &key);
  bool RemoveMember(const std::string &key);

  template <typename T> void Set(const std::string &key, T value);
  template <typename T> T Get(const std::string &key, const T &defaultValue = T());

  class Recovery
    {
    public:
        ~Recovery() {
            if(JsonConfig::mInstance)
            {
                delete JsonConfig::mInstance;
                JsonConfig::mInstance = NULL;
            }
        }
    };

private:
  static JsonConfig* mInstance;

  JsonConfig();

  std::string mFileName;
  rapidjson::Document mDocument;
};

template <typename T> inline void JsonConfig::Set(const std::string &key, T value) {
  rapidjson::Value val(value);
  rapidjson::Value jsonKey;
  jsonKey.SetString(key.c_str(), key.size(), mDocument.GetAllocator());
  mDocument.AddMember(jsonKey, val, mDocument.GetAllocator());
}

template <> inline void JsonConfig::Set<std::string>(const std::string &key, std::string value) {
  rapidjson::Value val;
  val.SetString(value.c_str(), value.length(), mDocument.GetAllocator());
  rapidjson::Value jsonKey;
  jsonKey.SetString(key.c_str(), key.size(), mDocument.GetAllocator());
  mDocument.AddMember(jsonKey, val, mDocument.GetAllocator());
}

template <typename T> inline T JsonConfig::Get(const std::string &key, const T &defaultValue) {
  if (mDocument.HasMember(key.c_str())) {
    return mDocument[key.c_str()].Get<T>();
  } else {
    return T();
  }
}

template <> inline std::string JsonConfig::Get<std::string>(const std::string &key, const std::string &defaultValue) {
  if (mDocument.HasMember(key.c_str())) {
    return mDocument[key.c_str()].GetString();
  }
}