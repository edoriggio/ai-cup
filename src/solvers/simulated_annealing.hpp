#include <cmath>
#include <tuple>
#include <random>
#include <vector>
#include <algorithm>

#define CONSTANT_TEMP 0.95
#define MAX_ITERATIONS 100

using namespace std;


tuple<vector<float>, int> random_neighbor(vector<float> solution, Problem * problem) {
  int i;
  int j;

  vector<float> neighbor = solution;

  random_device rd;
  mt19937 rng(rd());
  uniform_int_distribution<int> uni(1, solution.size() - 1);

  auto i_tmp = uni(rng);
  auto j_tmp = uni(rng);

  if (i_tmp < j_tmp) {
    i = i_tmp;
    j = j_tmp;
  } else {
    i = j_tmp;
    j = i_tmp;
  }

  if (j == i+1) j++;

  int old_two_opt_len = problem->distance_matrix[neighbor[i]][neighbor[i-1]]
                        + problem->distance_matrix[neighbor[j]][neighbor[j+1]];
  int new_two_opt_len = problem->distance_matrix[neighbor[j]][neighbor[i-1]]
                        + problem->distance_matrix[neighbor[i]][neighbor[j+1]];

  int gain = - old_two_opt_len + new_two_opt_len;
  reverse(neighbor.begin() + i, neighbor.begin() + j + 1);

  return make_tuple(neighbor, gain);
}


vector<float> simulated_annealing(vector<float> solution, Problem * problem) {
  float temp = problem->best_solution_len / sqrt(problem->n_points);
  
  vector<float> curr_solution = solution;
  int curr_length = length(curr_solution, problem->distance_matrix);

  vector<float> best_solution = curr_solution;
  int best_length = curr_length;

  while (temp > 0.001) {
    for (int i = 0; i < MAX_ITERATIONS; i++) {
      auto sol = random_neighbor(curr_solution, problem);

      if (get<1>(sol) < 0) {
        curr_solution = get<0>(sol);
        curr_length += get<1>(sol);

        if (curr_length < best_length) {
          best_solution = curr_solution;
          best_length = curr_length;

        }
      } else {
        random_device rd;
        mt19937 rng(rd());
        uniform_real_distribution<float> uni(0, 1);

        auto rand = uni(rng);

        if (rand < exp(-(get<1>(sol) / temp))) {
          curr_solution = get<0>(sol);
          curr_length += get<1>(sol);

          
        }
      }

      temp *= CONSTANT_TEMP;
    }
  }

  return best_solution;
}
