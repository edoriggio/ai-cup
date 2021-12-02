#include <vector>

#include "../utils/min_el.hpp"
#include "../utils/length.hpp"
#include "../utils/check_in.hpp"
#include "../utils/sort_dist.hpp"

using namespace std;


vector<int> nearest_neighbors(Problem * problem, int starting_node=0) {
  vector<vector<int> > distance_matrix = problem->distance_matrix;
  int len = problem->n_points;

  vector<int> result(len);
  int node = starting_node;
  result[0] = node;

  for (int i = 1; i < len-1; i++) {
    vector<int> sorted_dist = argsort(distance_matrix[node]);

    for (auto new_node : sorted_dist) {
      if (!check_in(result, new_node)) {
        result[i] = new_node;
        node = new_node;
        break;
      }
    }
  }

  return result;
}


vector<int> best_nearest_neighbors(Problem * problem) {
  vector<vector<int> > solutions(problem->n_points, vector<int>(problem->n_points));
  vector<int> best_solution(problem->n_points-1);
  vector<int> lengths(problem->n_points-1);

  for (int i = 0; i < problem->n_points; i++) {
    vector<int> solution = nearest_neighbors(problem, i);
    solutions[i] = solution;
    lengths[i] = length(solution, problem->distance_matrix);
  }

  if (lengths.size() == 0) return vector<int>();

  problem->best_solution_len = lengths[min_el(lengths)];
  
  return solutions[min_el(lengths)];
}
