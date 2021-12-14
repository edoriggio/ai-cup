#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Two-opt algorithm step
 * 
 * Perform a single step of the two-opt algorithm.
 * 
 * @param solution Solution to be optimized
 * @param problem Problem to be solved
 * @return Tuple containing the new solution and the total gain
 */
tuple<vector<float>, int> two_opt_step(vector<float> solution, Problem * problem) {
  int gain = 0;

  int best_i = 1;
  int best_j = 2;

  bool swapped = false;

  vector<float> new_solution = solution;

  for (int i = 1; i < solution.size()-2; i++) {
    for (int j = i+1; j < solution.size()-1; j++) {
      int old_link_len = problem->distance_matrix[new_solution[i]][new_solution[i-1]]
                         + problem->distance_matrix[new_solution[j]][new_solution[j+1]];
      int new_link_len = problem->distance_matrix[new_solution[j]][new_solution[i-1]]
                         + problem->distance_matrix[new_solution[i]][new_solution[j+1]];

      int gain_value = - old_link_len + new_link_len;

      if (gain_value < gain) {
        best_i = i;
        best_j = j;
        swapped = true;
        gain = gain_value;
      }
    }
  }

  reverse(new_solution.begin() + best_i, new_solution.begin() + best_j + 1);
  
  return make_tuple(new_solution, swapped);
}


/**
 * @brief Two-opt algorithm
 * 
 * Perform the two-opt algorithm on a solution.
 * 
 * @param solution Solution to be optimized
 * @param problem Problem to be solved
 * @return The optimized solution
 */
vector<float> two_opt(vector<float> solution, Problem * problem) {
  bool swapping = true;
  vector<float> new_solution = solution;

  while (swapping) {
    auto res = two_opt_step(new_solution, problem);
    new_solution = get<0>(res);
    swapping = get<1>(res);
  }

  return new_solution;
}
