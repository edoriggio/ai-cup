#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> argsort(vector<int> & nums) {
  vector<int> idx(nums.size());
  iota(idx.begin(), idx.end(), 0);

  const auto function = [&nums](int i1, int i2) noexcept -> bool {
    return nums[i1] < nums[i2];
  };

  sort(idx.begin(), idx.end(), function);
  
  return idx;
}
