#include "container.hpp"

container_c::container_c(const char *destination)
    : destination_file(destination) {
  errorMessage = "";
};

std::string container_c::getErrorMessage() { return errorMessage; }

bool container_c::readFile(Json::Value &parsedFile) {
  std::fstream configFileRead(destination_file, std::ifstream::binary);
  configFileRead.open(destination_file, std::ios::in);
  if (!configFileRead.is_open()) {
    std::ofstream configFileWrite;
    //make file if it did not exist, fill with empty json
    configFileWrite.open(destination_file, std::ios::out);
    Json::Value nothing;
    writeFile(nothing);
    configFileWrite.close();
    //retry
    configFileRead.open(destination_file, std::ios::in);
    if (!configFileRead.is_open()) {
      errorMessage =
          "ERROR, could not open file " + std::string(destination_file);
      return false;
    }
  }

  Json::Reader reader;
  if (!reader.parse(configFileRead, parsedFile)) {
    errorMessage = "Error in " + std::string(destination_file) + ": " +
                   reader.getFormatedErrorMessages();
    configFileRead.close();
    return false;
  }
  configFileRead.close();
  return true;
}

bool container_c::writeFile(const Json::Value &parsedFile) {
  Json::StyledStreamWriter writer;
  std::ofstream configFileWrite;
  configFileWrite.open(destination_file, std::ios::out);
  if (!configFileWrite.is_open()) {
    errorMessage =
        "ERROR, could not open file " + std::string(destination_file);
    return false;
  }
  writer.write(configFileWrite, parsedFile);
  configFileWrite.close();
  return true;
}

bool container_c::addElement(const std::string &key, const std::string &value) {
  Json::Value parsedFile;
  readFile(parsedFile);
  if (parsedFile.get(key, "err-1") != "err-1") {
    while (1) {
      std::cout << "Key already exist, do you want to override? y/n \n";
      std::string answer;
      getline(std::cin, answer);
      if (answer == "y" || answer == "Y") {
        break;
      }
      if (answer == "n" || answer == "N") {
        return true;
      }
    }
  }
  parsedFile[key] = value;
  return writeFile(parsedFile);
}

std::string container_c::getElement(const std::string &key,
                                    const std::string &errorString) {
  Json::Value parsedFile;
  if (!readFile(parsedFile)) {
    return errorString;
  }
  if (parsedFile.get(key, "err-1") == "err-1") {
    return " ";
  }
  return parsedFile[key].asString();
}

bool container_c::deleteElement(const std::string &key) {
  Json::Value parsedFile;
  if (!readFile(parsedFile)) {
    return false;
  }

  if (parsedFile.get(key, "err-1") == "err-1") {
    errorMessage = "ERROR, key is not present in file";
    return false;
  }

  parsedFile.removeMember(key);
  return writeFile(parsedFile);
}