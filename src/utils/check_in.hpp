#include <vector>

using namespace std;


bool check_in(vector<float> result, float j) {
  for (auto i : result) {
    if (i == j) return true;
  }

  return false;
}
