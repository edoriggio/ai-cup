#include <tuple>
#include <vector>
#include <algorithm>

#define MAX_UNCROSSES 1000

using namespace std;


/**
 * @brief Compute the gain of a possible swap
 * 
 * Compute the gain of a possible swap of two edges. If the gain is negative,
 * the swap is not allowed.
 * 
 * @param i First edge
 * @param j Second edge
 * @param solution Solution to be optimized
 * @param distance_matrix Distance matrix
 * @return Gain of the possible swap
 */
int gain(int i, int j, vector<float> solution, vector<vector<float> > distance_matrix) {
  int old_link_len = distance_matrix[solution[i]][solution[i-1]] + distance_matrix[solution[j]][solution[j+1]];
  int new_link_len = distance_matrix[solution[j]][solution[i-1]] + distance_matrix[solution[i]][solution[j+1]];
  
  return - old_link_len + new_link_len;
}


/**
 * @brief Two-opt algorithm step
 * 
 * Perform a single step of the two-opt algorithm.
 * 
 * @param solution Solution to be optimized
 * @param problem Problem to be solved
 * @return Tuple containing the new solution, the total gain,
 *         and the number of uncrosses
 */
tuple<vector<float>, int, int> two_opt_step(vector<float> solution, Problem * problem) {
  int tot_gain = 0;
  int tot_uncrosses = 0;

  vector<float> new_solution = solution;

  for (int i = 1; i < solution.size()-2; i++) {
    for (int j = i+1; j < solution.size()-1; j++) {
      int gain_value = gain(i, j, new_solution, problem->distance_matrix);

      if (gain_value < 0) {
        reverse(new_solution.begin() + i, new_solution.begin() + j + 1);
        tot_gain += gain_value;
        
        tot_uncrosses++;
      }
    }
  }
  
  return make_tuple(new_solution, tot_gain, tot_uncrosses);
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
  int uncrosses = 0;

  vector<float> new_solution = solution;

  while (uncrosses < MAX_UNCROSSES) {
    auto res = two_opt_step(new_solution, problem);

    if (get<1>(res) >= 0) break;

    new_solution = get<0>(res);
    uncrosses += get<2>(res);
  }

  return new_solution;
}
