#include <iostream>
#include <vector>
#include <string>
#include "const.h"
#include "utils.h"
#include "TimedMessage.h"

TimedMessage::TimedMessage(
  long time,
  std::vector < unsigned char > message) {
  zTime = time;
  zMessage = message;
}

TimedMessage::~TimedMessage() {
}

long TimedMessage::get_time () {
  return zTime;
}

std::vector < unsigned char> 
  TimedMessage::get_message() {
  return zMessage;
}

std::string TimedMessage::get_string() {
  std::string result("");
  result.append(std::to_string(zTime));
  result.append(" ");
  for(unsigned char c : zMessage) {
    result.append(std::to_string(c));
    result.append(" ");
  }
  return result;
}
