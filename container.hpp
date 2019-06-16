#pragma once
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>

class container_c {
private:
  /**
   * @brief
   * file to save the elements
   */
  const char *destination_file;
  /**
   * @brief
   * variable to write the most recent error to
   */
  std::string errorMessage;

   /**
   * @brief
   * Reads the jsonfile via jsoncpp
   * @details
   * Reads the jsonfile via jsoncpp, adjust the parsedFile as result. If first try did not work since the file is not present, 
   * it will make its own file. Returns if succeeded or not to read file.
   */
  bool readFile(Json::Value &parsedFile);

  /**
   * @brief
   * Write to the jsonfile via jsoncpp
   * @details
   * Write to the jsonfile via jsoncpp, returns if succeeded or not. If the file is not present, 
   * it will make its own file.
   */
  bool writeFile(const Json::Value &parsedFile);

public:
  /**
   * @brief
   * Constructor container_c
   * @param    destination: file destination
   */
  container_c(const char *destination);

  /**
   * @brief
   * returns the current errormessage
   */
  std::string getErrorMessage();


  /**
   * @brief
   * Add key and value to the jsonfile via jsoncpp
   * @details
   * Add key and value to the jsonfile via jsoncpp, returns if succeeded or not
   */
  bool addElement(const std::string &key, const std::string &value);

  /**
   * @brief
   * Returns value from the given key
   * @details
   * Returns value from the given key. If key is not present, it wil return " "
   */
  std::string getElement(const std::string &key,
                         const std::string &errorString);

  /**
   * @brief
   * Remove key and value from the jsonfile via jsoncpp
   * @details
   * Remove key and value from the jsonfile via jsoncpp, returns if succeeded or not
   */
  bool deleteElement(const std::string &key);
};
