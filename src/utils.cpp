#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "const.h"
#include "utils.h"


std::vector< std::string > utils::split(std::string str, char delimiter) {
    std::vector< std::string > words{};
    std::string word = "";
    for (char& c : str) {
      if (c != delimiter) {
        word.append(1, c);
      }
      else if (word.size() > 0) {
        words.push_back(word);
        word = "";
      }
    }
    if (word.size() > 0) {
      words.push_back(word);
      word = "";
    }
    return words;
}

std::vector< std::string > utils::split_equal(std::string str, int size) {
  std::string word = "";
  std::vector< std::string > words{};
  int i = 0;

  for (char& c : str) {
    i += 1;  
    word.append(1, c);
    if ((i % size) == 0) {
      words.push_back(word);
      word = "";
    }
  }
  if (word.size() > 0) {
    words.push_back(word);
  }
  return words;
}

std::string utils::remove_comment(std::string line) {
  unsigned int first_pos = line.find(cCommentTag);
  return line.substr(0, first_pos);
}

float utils::square(float number) {
  return number * number;
}

int utils::float_equal(float a, float b) {
  return (std::abs(a - b) < cFloatDelta);
}

std::string utils::inc_ending_number(
 std::string name) {
  unsigned int first_index = 0;
  for ( unsigned int i=0; i<name.size(); i++) {
    if ( ! (std::isdigit(name[i])) ) {
      first_index = i;
    }
  }
  std::string trunc = "";
  std::string ending = "";
  for ( unsigned int i=0; i<name.size(); i++) {
    if (i <= first_index) {
      trunc += name[i];
    }
    else {
      ending += name[i];
    }
  }
  ending = std::to_string(std::stoi(ending) + 1);
  return trunc + ending;
}

StatusByteType utils::status_byte_type(
 std::vector< unsigned char > message) {
  if (message.size() == 3) {
    unsigned char byte = message[0];
    if ((144 <= byte) && (byte < 160)) {
      return note_on;
    }
    else if ((128 <= byte) && (byte < 144)) {
      return note_off;
    }
    else if ((176 <= byte) && (byte < 192)) {
      if (message[1] == 64) {
        if (message[2] > 64) {
          return pedal_pressed;
        }
        else {
          return pedal_released;
        }
      }
      else {
        return unknown;
      }
    }
    else if ((224 <= byte) && (byte < 240)) {
        return bending;
    }
    else {
      return unknown;
    }
  }
  else {
    return unknown;
  }
}

int utils::channel(std::vector< unsigned char > message) {
  StatusByteType type = status_byte_type(message);
  if (type == note_on) {
    return message[0] - 144;
  }
  else if (type == note_off) {
    return message[0] - 128;
  }
  else if (type == pedal_pressed) {
    return message[0] - 176;
  }
  else if (type == pedal_released) {
    return message[0] - 176;
  }
  else if (type == bending) {
    return message[0] - 224;
  }
  else {
    return 0;
  }
}

std::string utils::message_to_string(
  std::vector < unsigned char > message) {
  std::string result("");
  result.append("< ");
  for(unsigned char c : message) {
    result.append(std::to_string(c));
    result.append(" ");
  }
  result.append(">");
  return result;
}

std::string utils::intvector_to_string(
  std::vector < int > vector) {
  std::string result("");
  result.append("< ");
  for(int i : vector) {
    result.append(std::to_string(i));
    result.append(" ");
  }
  result.append(">");
  return result;
}
std::vector < int > utils::vector_str_to_int(
    std::vector < std::string > str_vector) {
    std::vector < int > result{};
    for(std::string s : str_vector) {
        result.push_back(std::stoi(s));
    }
    return result;
}

