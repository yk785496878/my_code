#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

JsonConfig *JsonConfig::mInstance = NULL;

JsonConfig *JsonConfig::getInstance() {
  if (mInstance == NULL) {
    mInstance = new JsonConfig();
    static Recovery recvory;
  }
  return mInstance;
}

JsonConfig::JsonConfig(){}

JsonConfig::~JsonConfig() {SaveFile();}

bool JsonConfig::LoadFile(const std::string &fileName) {
  mFileName = fileName;
  try {
    std::ifstream inFile(mFileName);
    if (!inFile) {
      throw std::runtime_error("Failed to open file: " + mFileName);
    }
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContents = buffer.str();
    mDocument.Parse(fileContents.c_str());
    if (mDocument.HasParseError()) {
      throw std::runtime_error("Failed to parse file: " + mFileName);
    }
    inFile.close();
    return true;
  } catch (const std::exception &ex) {
    std::cout << ex.what() << std::endl;
    return false;
  }
}

bool JsonConfig::SaveFile() {
  try {
    std::ofstream outFile(mFileName);
    if (!outFile) {
      throw std::runtime_error("Failed to save file: " + mFileName);
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    mDocument.Accept(writer);
    outFile << buffer.GetString() << std::endl;
    outFile.close();
    return true;
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return false;
  }
}

bool JsonConfig::HasKey(const std::string &key) { return mDocument.HasMember(key.c_str()); }

bool JsonConfig::RemoveMember(const std::string &key) { return mDocument.RemoveMember(key.c_str()); }