#pragma once
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>

class container_c {
private:
  const char *destination_file;
  std::string errorMessage;

public:
  container_c(const char *destination);

  std::string getErrorMessage();

  bool readFile(Json::Value &parsedFile);

  bool writeFile(const Json::Value &parsedFile);

  bool addElement(const std::string &key, const std::string &value);

  std::string getElement(const std::string &key, const std::string &errorString);

  bool deleteElement(const std::string &key);
};