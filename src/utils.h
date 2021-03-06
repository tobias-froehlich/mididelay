#ifndef UTILS_H_
#define UTILS_H_

namespace utils {
  std::vector< std::string > split(std::string str, char delimiter);
    // Splits str into words, seperated by delimiter. Several delimeters
    // occuring in a group are treated as one. Delimiters at beginning or end
    // are ignored.
  std::vector< std::string > split_equal(std::string str, int size);
    // Splits str into words of length size. If length of str is not
    // a multiple of size, then the last word is shorter.
  std::string remove_comment(std::string line);
      // removes everything from the string from the first comment tag.
      // Which character this is, is specified in const.h (zCommentTag).
  float square(float number);
      // Calculates the square of a float. Just to avoid calculating
      // the number twice like (some caclulation) * (same calculation).
  int float_equal(float a, float b);
      // Tests whether a and b differ less than cFloatDelta (in const.h).

  unsigned char notename_to_midicode(std::string notename);
  
  std::string midicode_to_notename(unsigned char midicode);

  std::string inc_ending_number(std::string name);

  StatusByteType status_byte_type(
   std::vector< unsigned char > message);

  int channel(std::vector< unsigned char > message);

  std::string message_to_string(
    std::vector < unsigned char > message);

  std::string intvector_to_string(
    std::vector < int > vector);

  std::vector < int > vector_str_to_int(
    std::vector < std::string >);
}

#endif
