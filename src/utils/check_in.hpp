#include <vector>

using namespace std;


/**
 * @brief Check if the given number is in the given vector.
 * 
 * @param result The vector to check.
 * @param j The number to check.
 * @return true The number is in the vector.
 * @return false The number is not in the vector.
 */
bool check_in(vector<float> result, float j) {
  for (auto i : result) {
    if (i == j) return true;
  }

  return false;
}
