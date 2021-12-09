#include <vector>

using namespace std;


/**
 * @brief Length of tour
 * 
 * This function computes the length of a given tour.
 * 
 * @param solution The tour
 * @param distance_matrix The distance matrix
 * @return The length of the tour
 */
int length(vector<float> solution, vector<vector<float> > distance_matrix) {
  int length = 0;
  int starting_node = solution[0];
  int from_node = starting_node;

  for (int i = 1; i < solution.size(); i++) {
    int to_node = solution[i];
    length += distance_matrix[from_node][to_node];
    from_node = to_node;
  }

  length += distance_matrix[starting_node][from_node];
  
  return length;
}
