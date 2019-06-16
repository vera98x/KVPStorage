#include "container.hpp"
#include <iostream>
#include <string>
#include <vector>

std::string getLine() {
  std::string retrievedStr;
  getline(std::cin, retrievedStr);
  return retrievedStr;
}

std::vector<std::string> splitString(const std::string &retrievedStr,
                                     char delimiter) {
  int index = 0;
  std::vector<std::string> resultSplitter;
  std::string tempString = "";
  // Do until end of string
  while (retrievedStr[index] != '\0') {

    if (retrievedStr[index] == delimiter) {
      resultSplitter.push_back(tempString);
      tempString = "";
    } else {
      // add character to string
      tempString += retrievedStr[index];
    }

    index++;
  }
  // make sure last element is not forgotten
  if (tempString != "") {
    resultSplitter.push_back(tempString);
  }

  return resultSplitter;
}

std::string lengthError(int target, int given) {
  std::string amountArguments = "";
  if (given <= 10) {
    // int to char
    amountArguments = char(given) + '0' - 1;
  } else {
    amountArguments = "10+";
  }
  std::string targetChar = "";
  // int to char
  targetChar = char(target) + '0';
  std::string error = "ERROR, " + targetChar + " argument(s) needed, " +
                      amountArguments + " were given";
  return error;
}

std::string updateViaString(const std::string &retrievedStr,
                            container_c &container) {

  std::vector<std::string> commands = splitString(retrievedStr, ' ');
  int lengthCommands = commands.size();
  try {
    // check if input has been given so you don't go out of range
    if (lengthCommands > 0) {
      if (commands[0] == "SET" || commands[0] == "set") {
        if (lengthCommands == 3) {
          if (!container.addElement(commands[1], commands[2])) {
            throw container.getErrorMessage();
          } else {
            return "OK";
          }
        } else {
          // give error about too few/much arguments
          throw lengthError(2, lengthCommands);
        }
      } else if (commands[0] == "GET" || commands[0] == "get") {
        if (lengthCommands == 2) {
          // give 2snd parameter to verify if key is not in file
          std::string result = container.getElement(commands[1], "err-1");
          if (result == "err-1") {
            throw container.getErrorMessage();
          }
          return result;
        } else {
          // give error about too few/much arguments
          throw lengthError(1, lengthCommands);
        }
      } else if (commands[0] == "DELETE" || commands[0] == "delete") {
        if (lengthCommands == 2) {
          if (!container.deleteElement(commands[1])) {
            throw container.getErrorMessage();
          } else {
            return "OK";
          }
        } else {
          // give error about too few/much arguments
          throw lengthError(1, lengthCommands);
        }
      } else {
        throw "ERROR, unknown command";
      }
    } else {
      throw "ERROR, no command given";
    }
  } catch (const char *msg) {
    return msg;
  } catch (const std::string &msg) {
    return msg;
  }
}

bool testFunctions() {
  int succeeded = 1;

  std::string teststring = "hello i am testing this";
  std::vector<std::string> result = splitString(teststring, ' ');
  if (result.size() == 5 && result[0] == "hello" && result[1] == "i" &&
      result[2] == "am" && result[3] == "testing" && result[4] == "this") {
    std::cout << "test 0 complete\n";
  } else {
    std::cout << "test 0 failed: outcome with the first two elements is: " +
                     result[0] + "  " + result[1] + "  " + result[2] + "  " +
                     result[3] + "  " + result[4] + "\n";
    std::cout << "This should be hello i am testing this\n";
    succeeded = 0;
  }

  std::string teststring1 = "hello test              ";
  std::vector<std::string> result1 = splitString(teststring1, ' ');
  if (result1.size() > 2 && result1[0] == "hello" && result1[1] == "test") {
    std::cout << "test 1 complete\n";
  } else {
    std::cout << "test 1 failed: outcome with the first two elements is: " +
                     result1[0] + "  " + result1[1] + "\n";
    std::cout << "This should be hello test\n";
    succeeded = 0;
  }

  std::string result2 = lengthError(7, 6);
  if (result2 == "ERROR, 7 argument(s) needed, 5 were given") {
    std::cout << "test 2 complete\n";
  } else {
    std::cout << "test 2 failed: outcome is " + result2 +
                     ", but should be \"ERROR, 7 argument(s) needed, 5 were "
                     "given\" \n";
    succeeded = 0;
  }

  container_c containerFile("config/config.json");
  std::string result3 =
      updateViaString("SET DeviceName TestDevice_123", containerFile);
  if (result3 == "OK") {
    std::cout << "test 3.1 complete\n";
  } else {
    std::cout << "test 3.1 failed: outcome is " + result3 +
                     ", but should be \"OK\" \n";
    succeeded = 0;
  }
  // SET key value, while key exist. Gives question for override, should be ok
  std::string result3_2 =
      updateViaString("SET DeviceName TestDevice_123", containerFile);
  if (result3_2 == "OK") {
    std::cout << "test 3.2 complete\n";
  } else {
    std::cout << "test 3.2 failed: outcome is " + result3_2 +
                     ", but should be \"OK\" \n";
    succeeded = 0;
  }

  std::string result4 = updateViaString("GET DeviceName", containerFile);
  if (result4 == "TestDevice_123") {
    std::cout << "test 4 complete\n";
  } else {
    std::cout << "test 4 failed: outcome is " + result4 +
                     ", but should be \"TestDevice_123\" \n";
    succeeded = 0;
  }

  std::string result5_1 =
      updateViaString("DELETE TestDevice_123", containerFile);
  if (result5_1 == "ERROR, key is not present in file") {
    std::cout << "test 5.1 complete\n";
  } else {
    std::cout << "test 5.1 failed: outcome is " + result5_1 +
                     ", but should be \"ERROR, key is not present in file\" \n";
    succeeded = 0;
  }

  std::string result5_2 = updateViaString("DELETE DeviceName", containerFile);
  if (result5_2 == "OK") {
    std::cout << "test 5.2 complete\n";
  } else {
    std::cout << "test 5.2 failed: outcome is " + result5_2 +
                     ", but should be \"OK\" \n";
    succeeded = 0;
  }

  std::string result6 = updateViaString("GET DeviceName", containerFile);
  if (result6 == " ") {
    std::cout << "test 6 complete\n";
  } else {
    std::cout << "test 6 failed: outcome is " + result6 +
                     ", but should be \" \" \n";
    succeeded = 0;
  }

  std::string result7 = updateViaString("GET TEST true", containerFile);
  if (result7 == "ERROR, 1 argument(s) needed, 2 were given") {
    std::cout << "test 7 complete\n";
  } else {
    std::cout << "test 7 failed: outcome is " + result7 +
                     ", but should be \"ERROR, 1 argument(s) needed, 2 were "
                     "given\" \n";
    succeeded = 0;
  }

  if (containerFile.addElement("clay", "test")) {
    std::cout << "test 8 complete\n";
  } else {
    std::cout << "Test 8 failed, could not add clay : test to file " +
                     containerFile.getErrorMessage()
              << "\n";
  }

  std::string result9 = containerFile.getElement("clay", "testfail");
  if (result9 == "test") {
    std::cout << "test 9 complete\n";
  } else {
    std::cout << "test 9 failed: outcome is " + result9 +
                     ", but should be \"test\" \n";
  }

  if (containerFile.deleteElement("clay")) {
    std::cout << "test 10 complete\n";
  } else {
    std::cout << "Test 10 failed, could not delete clay from file: " +
                     containerFile.getErrorMessage()
              << "\n";
  }

  return succeeded;
}

int main() {
  container_c containerFile("config/config.json");
  bool testing = true;
  if (testing) {
    if (testFunctions()) {
      std::cout << "All tests have passed\n";
    } else {
      std::cout << "Some test have failed"
                << "\n";
    }
  }
  while (1) {
    std::cout << "> ";
    std::cout << updateViaString(getLine(), containerFile) << "\n";
  }
}
