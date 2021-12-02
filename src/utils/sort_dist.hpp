#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

vector<int> argsort(vector<int> &array) {
  vector<int> indices(array.size());

  iota(indices.begin(), indices.end(), 0);
  sort(indices.begin(), indices.end(),
    [&array](int left, int right) -> bool {
        return array[left] < array[right];
    });

  return indices;
}
