#include <vector>

using namespace std;


int length(vector<int> solution, vector<vector<int> > distance_matrix) {
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
