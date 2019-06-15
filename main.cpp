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
  while (retrievedStr[index] != '\0') {

    if (retrievedStr[index] == delimiter) {
      resultSplitter.push_back(tempString);
      tempString = "";
    } else {
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
    amountArguments = char(given) + '0' - 1;
  } else {
    amountArguments = "10+";
  }
  std::string targetChar = "";
  targetChar = char(target) + '0';
  std::string error =
      "ERROR, " + targetChar + " argument(s) needed, " + amountArguments + " where given";
  return error;
}

std::string updateViaString(const std::string &retrievedStr,
                            container_c &container) {

  std::vector<std::string> commands = splitString(retrievedStr, ' ');
  int lengthCommands = commands.size();
  try {
    if (lengthCommands > 0) {
      if (commands[0] == "SET" || commands[0] == "set") {
        if (lengthCommands == 3) {
          if (!container.addElement(commands[1], commands[2])) {
            throw container.getErrorMessage();
          } else {
            return "OK";
          }
        } else {
          throw lengthError(2, lengthCommands);
        }
      } else if (commands[0] == "GET" || commands[0] == "get") {
        if (lengthCommands == 2) {
          std::string result = container.getElement(commands[1], "err-1");
          if(result == "err-1"){
            throw container.getErrorMessage();
          }
          return result;
        } else {
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

int main() {
  container_c containerFile("config/config.json");
  while (1) {
    std::cout << "> ";
    std::cout << updateViaString(getLine(), containerFile) << "\n";
  }
}