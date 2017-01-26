#ifndef TOKENIZE_STR_H
#define TOKENIZE_STR_H

#include <string>
#include <vector>

// Tokenize a given string with a given set of delimeters
// Inputs:
//   str  string to be tokensize
//   delims  string of delimiting characters
// Returns vector of tokens
std::vector<std::string> tokenize_str(
  const std::string & str,
  const std::string & delims=", \t");


// Implementation
// http://rosettacode.org/wiki/Tokenize_a_string#C.2B.2B

std::vector<std::string> tokenize_str(
  const std::string & str,
  const std::string & delims)
{
  using namespace std;
  // Skip delims at beginning, find start of first token
  string::size_type lastPos = str.find_first_not_of(delims, 0);
  // Find next delimiter @ end of token
  string::size_type pos     = str.find_first_of(delims, lastPos);
 
  // output vector
  vector<string> tokens;
 
  while (string::npos != pos || string::npos != lastPos)
    {
      // Found a token, add it to the vector.
      tokens.push_back(str.substr(lastPos, pos - lastPos));
      // Skip delims.  Note the "not_of". this is beginning of token
      lastPos = str.find_first_not_of(delims, pos);
      // Find next delimiter at end of token.
      pos     = str.find_first_of(delims, lastPos);
    }
 
  return tokens;
}

#endif
