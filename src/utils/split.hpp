#include <vector>
#include <string>
#include <sstream>

using namespace std;


/**
 * @brief Splits a string into a vector of strings given a delimiter
 * 
 * @param s The string to split`
 * @param delimiter The delimiter
 * @return vector<string> 
 */
vector<string> split(string s, string delimiter) {
  size_t pos_end;
  size_t pos_start = 0;
  size_t delim_len = delimiter.length();

  string token;
  vector<string> res;

  while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
    token = s.substr (pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back (token);
  }

  res.push_back (s.substr (pos_start));
  return res;
}
