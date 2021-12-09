#include <tuple>
#include <vector>
#include <numeric>

#define ANT_COUNT 10
#define INITIAL_PHEROMONE 0.001

using namespace std;


class Edge;
class Ant;

vector<Edge> edges;
vector<Ant> ants;


/**
 * @brief The Edge class
 * 
 * Class representing an edge in the graph.
 */
class Edge {
public:
  tuple<float, float> city1;
  tuple<float, float> city2;

  float distance;
  float pheromone;


  /**
   * @brief Construct a new Edge object
   * 
   * @param city1 The first city of the edge
   * @param city2 The second city of the edge
   * @param distance The distance between the two cities
   * @param pheromone The level of pheromone on the edge
   */
  Edge(tuple<float, float> city1, tuple<float, float> city2, float distance, float pheromone) {
    this->city1 = city1;
    this->city2 = city2;

    this->distance = distance;
    this->pheromone = pheromone;
  }
};


/**
 * @brief The Ant class
 * 
 * Class representing an ant in the colony.
 */
class Ant {
public:
  float rho;
  float beta;

  float total_distance;
  int to_visit_cities_len;

  vector<Edge> visited_edges;
  tuple<float, float> current_city;
  tuple<float, float> starting_city;


  /**
   * @brief Roulette wheel selection
   * 
   * Select a city by the roulette wheel heuristic.
   * 
   * @param current_city The current city of the ant
   */
  tuple<float, float> _exploitation(tuple<float, float> current_city) {
    float prob;

    float total_pheromone = 0;
    float total_distance_edges = 0;

    vector<Edge> visitable_edges;

    for (auto edge : edges) {
      if (edge.city1 == current_city && !_check_in(visited_edges, edge)) {
        visitable_edges.push_back(edge);
      }
    }

    for (auto edge : visitable_edges) {
      total_pheromone += _compute_tau(edge);
      total_distance_edges += edge.distance;
    }
    
    for (auto edge : visitable_edges) {
      float tau = _compute_tau(edge);
      float eta = 1 / edge.distance;

      prob += (tau * pow(eta, beta)) / (total_pheromone * pow(1 / total_distance_edges, beta));
    }

    float random_value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / prob);

    prob = 0.0;

    for (auto edge : visitable_edges) {
      float tau = _compute_tau(edge);
      float eta = 1 / edge.distance;

      prob += (tau * pow(eta, beta)) / (total_pheromone * pow(1 / total_distance_edges, beta));

      if (random_value <= prob) {
        return edge.city2;
      }
    }
  }


  /**
   * @brief Exploration
   * 
   * Select a city by the exploration heuristic.
   * 
   * @param current_city The current city of the ant
   */
  tuple<float, float> _exploration(tuple<float, float> current_city) {
    tuple<float,float> best_city;
    vector<Edge> visitable_edges;
    
    float best_factor = 0.0;

    for (auto edge : edges) {
      if (edge.city1 == current_city && !_check_in(visited_edges, edge)) {
        visitable_edges.push_back(edge);
      }
    }

    for (auto edge : visitable_edges) {
      float tau = _compute_tau(edge);
      float eta = 1 / edge.distance;
      float factor =  tau * pow(eta, beta);

      if (factor > best_factor) {
        best_factor = factor;
        best_city = edge.city2;
      }
    }

    return best_city;
  }


  /**
   * @brief Compute pheromone
   * 
   * Compute the total amount of pheromone on an edge.
   * 
   * @param edge The edge
   * @return The tau value
   */
  float _compute_tau(Edge edge) {
    return (1 - rho) * edge.pheromone + rho * edge.pheromone;
  }


  /**
   * @brief Check if edge is in vector
   * 
   * Check if the given edge is in the vector of edges.
   * 
   * @param result The vector of edges
   * @param j The edge to check
   * @return true If the edge is in the vector
   * @return false If the edge is not in the vector
   */
  bool _check_in(vector<Edge> result, Edge j) {
    for (auto i : result) {
      if (i.city1 == j.city1 && i.city2 == j.city2) {
        return true;
      }
    }

    return false;
  }


public:
  /**
   * @brief Construct a new Ant object
   * 
   * @param to_visit_cities_len The number of cities to visit
   * @param starting_city The starting city
   */
  Ant(int to_visit_cities_len, tuple<float, float> starting_city) {
    this->rho = 0.1;
    this->beta = 2.0;
    this->total_distance = 0.0;

    this->visited_edges = vector<Edge>();

    this->current_city = starting_city;
    this->starting_city = starting_city;
    this->to_visit_cities_len = to_visit_cities_len;
  }


  /**
   * @brief Get the next city
   * 
   * Get the next city to visit by the ant.
   * 
   * @param current_city The current city
   * @param q0 Constant used to calculate the probability of choosing a city
   * @return The next city
   */
  void get_next_city(tuple<float, float> current_city, float q0) {
    float q = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    if (q > q0) {
      this->current_city = _exploitation(current_city);
    } else {
      this->current_city = _exploration(current_city);
    }

    for (auto edge : edges) {
      if (edge.city1 == current_city && edge.city2 == this->current_city) {
        this->to_visit_cities_len--;
        this->visited_edges.push_back(edge);
        this->total_distance += edge.distance;
      }
    }

    cout << "Total distance: " << this->total_distance << endl;
  }
};


/**
 * @brief Ant colony algorithm
 * 
 * The main function of the ant colony algorithm.
 * 
 * @param problem The problem to solve
 * @return The best solution found
 */
vector<int> ant_colony(Problem * problem) {
  int size = (problem->n_points * problem->n_points) - problem->n_points;

  // Initialize edges
  for (int i = 0; i < problem->n_points-1; i++) {
    tuple<float, float> city1 = make_tuple(problem->points[i][1], problem->points[i][2]);

    for (int j = i+1; j < problem->n_points; j++) {
      tuple<float, float> city2 = make_tuple(problem->points[j][1], problem->points[j][2]);

      // Create an Edge w/ initial pheromone = 0.001
      // TODO: Set different initial pheromone - NN heuristic
      edges.push_back(Edge(city1, city2, problem->distance_matrix[i][j], INITIAL_PHEROMONE));
    }
  }

  // Initialize ants
  for (int i = 0; i < ANT_COUNT; i++) {
    tuple<float, float> city = make_tuple(problem->points[i][1], problem->points[i][2]);

    ants.push_back(Ant(problem->n_points - 1, city));
  }

  return vector<int>();
}
