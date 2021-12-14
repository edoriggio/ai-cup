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
  int gain = 0;

  int best_i = 1;
  int best_j = 2;

  int method = -1;
  bool swapped = false;

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

      if (two_opt_gain < gain || node_shift_1_gain < gain || node_shift_2_gain < gain) {
        best_i = i;
        best_j = j;
        swapped = true;

        if (two_opt_gain < node_shift_1_gain && two_opt_gain < node_shift_2_gain) {
          method = 1;
          gain = two_opt_gain;
        } else if (node_shift_1_gain < two_opt_gain && node_shift_1_gain < node_shift_2_gain) {
          method = 2;
          gain = node_shift_1_gain;
        } else if (node_shift_2_gain < two_opt_gain && node_shift_2_gain < node_shift_1_gain) {
          method = 3;
          gain = node_shift_2_gain;
        }
      }
    }
  }

  if (method == 1) {
    // Two-opt swap
    reverse(new_solution.begin() + best_i, new_solution.begin() + best_j + 1);
  } else if (method == 2) {
    // Node shift 1 swap
    vector<float> array_one = {new_solution.begin(), new_solution.begin() + best_i};
    vector<float> array_two = {new_solution.begin() + best_i + 1, new_solution.begin() + best_j + 1};
    vector<float> array_three = {new_solution.begin() + best_j + 1, new_solution.end()};

    vector<float> sol = array_one;
    sol.insert(sol.end(), array_two.begin(), array_two.end());
    sol.push_back(new_solution[best_i]);
    sol.insert(sol.end(), array_three.begin(), array_three.end());

    new_solution = sol;
  } else if (method == 3) {
    // Node shift 2 swap
    vector<float> array_one = {new_solution.begin(), new_solution.begin() + best_i};
    vector<float> array_two = {new_solution.begin() + best_i, new_solution.begin() + best_j};
    vector<float> array_three = {new_solution.begin() + best_j + 1, new_solution.end()};

    vector<float> sol = array_one;
    sol.push_back(new_solution[best_j]);
    sol.insert(sol.end(), array_two.begin(), array_two.end());
    sol.insert(sol.end(), array_three.begin(), array_three.end());

    new_solution = sol;
  } else {
    return make_tuple(solution, false);
  }
  
  return make_tuple(new_solution, swapped);
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
  bool swapping = true;
  vector<float> new_solution = solution;

  while (swapping) {
    auto res = two_dot_five_opt_step(new_solution, problem);
    new_solution = get<0>(res);
    swapping = get<1>(res);
  }

  return new_solution;
}
