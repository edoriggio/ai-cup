#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Two-dot-five-opt algorithm step
 * 
 * Perform a single step of the two-dot-five-opt algorithm.
 * 
 * @param solution Solution to be optimized
 * @param problem Problem to be solved
 * @return Tuple containing the new solution and the total gain
 */
tuple<vector<float>, int> two_dot_five_opt_step(vector<float> solution, Problem * problem) {
  int tot_gain = 0;

  vector<float> new_solution = solution;

  for (int i = 1; i < solution.size()-2; i++) {
    for (int j = i+1; j < solution.size()-1; j++) {
      // 2-opt gain
      int old_two_opt_len = problem->distance_matrix[new_solution[i]][new_solution[i-1]]
                            + problem->distance_matrix[new_solution[j]][new_solution[j+1]];
      int new_two_opt_len = problem->distance_matrix[new_solution[j]][new_solution[i-1]]
                            + problem->distance_matrix[new_solution[i]][new_solution[j+1]];

      int two_opt_gain = - old_two_opt_len + new_two_opt_len;

      // Node shift 1 gain
      int old_node_shift_1_len = problem->distance_matrix[new_solution[i]][new_solution[i-1]]
                                 + problem->distance_matrix[new_solution[i]][new_solution[i+1]]
                                 + problem->distance_matrix[new_solution[j]][new_solution[j+1]];
      int new_node_shift_1_len = problem->distance_matrix[new_solution[i-1]][new_solution[i+1]]
                                 + problem->distance_matrix[new_solution[i]][new_solution[j]]
                                 + problem->distance_matrix[new_solution[i]][new_solution[j+1]];

      int node_shift_1_gain = - old_node_shift_1_len + new_node_shift_1_len;

      // Node shift 2 gain
      int old_node_shift_2_len = problem->distance_matrix[new_solution[i]][new_solution[i-1]]
                                 + problem->distance_matrix[new_solution[j]][new_solution[j-1]]
                                 + problem->distance_matrix[new_solution[j]][new_solution[j+1]];
      int new_node_shift_2_len = problem->distance_matrix[new_solution[j]][new_solution[i-1]]
                                 + problem->distance_matrix[new_solution[i]][new_solution[j]]
                                 + problem->distance_matrix[new_solution[j-1]][new_solution[j+1]];

      int node_shift_2_gain = - old_node_shift_2_len + new_node_shift_2_len;

      if (two_opt_gain < 0 || node_shift_1_gain < 0 || node_shift_2_gain < 0) {
        if (two_opt_gain < node_shift_1_gain && two_opt_gain < node_shift_2_gain) {
          // 2-opt swap
          reverse(new_solution.begin() + i, new_solution.begin() + j + 1);
          tot_gain += two_opt_gain;
        } else if (node_shift_1_gain < two_opt_gain && node_shift_1_gain < node_shift_2_gain) {
          // Node shift 1 swap
          vector<float> array_one = {new_solution.begin(), new_solution.begin() + i};
          vector<float> array_two = {new_solution.begin() + i + 1, new_solution.begin() + j + 1};
          vector<float> array_three = {new_solution.begin() + j + 1, new_solution.end()};

          vector<float> sol = array_one;
          sol.insert(sol.end(), array_two.begin(), array_two.end());
          sol.push_back(new_solution[i]);
          sol.insert(sol.end(), array_three.begin(), array_three.end());

          new_solution = sol;
          tot_gain += node_shift_1_gain;
        } else if (node_shift_2_gain < two_opt_gain && node_shift_2_gain < node_shift_1_gain) {
          // Node shift 2 swap
          vector<float> array_one = {new_solution.begin(), new_solution.begin() + i};
          vector<float> array_two = {new_solution.begin() + i, new_solution.begin() + j};
          vector<float> array_three = {new_solution.begin() + j + 1, new_solution.end()};

          vector<float> sol = array_one;
          sol.push_back(new_solution[j]);
          sol.insert(sol.end(), array_two.begin(), array_two.end());
          sol.insert(sol.end(), array_three.begin(), array_three.end());

          new_solution = sol;
          tot_gain += node_shift_2_gain;
        }
      }
    }
  }
  
  return make_tuple(new_solution, tot_gain);
}


/**
 * @brief Two-dot-five-opt algorithm
 * 
 * Perform the two-dot-five-opt algorithm on a solution.
 * 
 * @param solution Solution to be optimized
 * @param problem Problem to be solved
 * @return The optimized solution
 */
vector<float> two_dot_five_opt(vector<float> solution, Problem * problem) {
  int gain = -1;
  vector<float> new_solution = solution;

  while (gain < 0) {
    auto res = two_dot_five_opt_step(new_solution, problem);
    new_solution = get<0>(res);
    gain = get<1>(res);
  }

  return new_solution;
}
