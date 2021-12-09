#include <vector>

using namespace std;


/**
 * @brief Nearest neighbors
 * 
 * The nearest neighbors algorithm.
 * 
 * @param problem The problem to solve
 * @param visited The visited nodes
 * @param start The starting node
 * @return The solution
 */
vector<float> nearest_neighbors(Problem * problem, vector<bool> & visited, int start=0) {
  vector<float> result;

  result.push_back(start);
  visited[start] = true;

  for (int i = 0; i < problem->n_points-1; i++) {
    float min_dist = INFINITY;
    float min_dist_idx = 0;

    for (int j = 0; j < problem->n_points; j++) {
      if (i == j) continue;

      float dist = problem->distance_matrix[result[result.size()-1]][j];

      if (dist < min_dist && !visited[j]) {
        min_dist = dist;
        min_dist_idx = j;
      }
    }

    visited[min_dist_idx] = true;
    result.push_back(min_dist_idx);
  }

  return result;
}


/**
 * @brief Best nearest neighbors
 * 
 * The best nearest neighbors algorithm.
 * 
 * @param problem The problem to solve
 * @return The solution
 */
vector<float> best_nearest_neighbors(Problem * problem) {
  vector<float> result;

  float min_length = INFINITY;
  
  for (int i = 0; i < problem->n_points; i++) {
    vector<bool> visited(problem->n_points, false);

    vector<float> temp = nearest_neighbors(problem, visited, i);
    int curr_len = length(temp, problem->distance_matrix);

    if (curr_len < min_length) {
      result = temp;
      min_length = curr_len;
    }
  }

  return result;
}
