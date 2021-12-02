#include <vector>

using namespace std;


int min_el(vector<int> v) {
  int min = v[0];
  int min_index = 0;

  for (int i = 1; i < v.size(); i++) {
    if (v[i] < min) {
      min = v[i];
      min_index = i;
    }
  }

  return min_index;
}
