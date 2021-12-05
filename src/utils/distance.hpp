#include <cmath>
#include <vector>

using namespace std;


/**
 * @brief Compute the Euclidean distance between two points
 * 
 * @param p1 The first point
 * @param p2 The second point
 * @return The Euclidean distance
 */
int distance(vector<float> p1, vector<float> p2) {
  int x1 = p1[1];
  int y1 = p1[2];
  int x2 = p2[1];
  int y2 = p2[2];

  return round(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}
