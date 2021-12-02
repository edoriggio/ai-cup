#include <vector>

using namespace std;


bool check_in(vector<int> result, int j) {
  for (auto i : result) {
    if (i == j) return true;
  }

  return false;
}
