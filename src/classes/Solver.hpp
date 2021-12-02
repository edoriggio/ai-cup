#include <ctime>
#include <vector>

#include "../solvers/two_opt.hpp"
#include "../solvers/nearest_neighbors.hpp"

using namespace std;

#ifndef SOLVER_HPP
#define SOLVER_HPP

class Solver {
private:
  int algo_name;
  float duration;
  int found_length;

  bool solved;
  Problem * problem;
  vector<int> solution;


  /**
   * @brief Solve the problem using the given algorithms
   * 
   * @return The solution vector of the problem
   */
  vector<int> compute_solution() {
    clock_t start = clock();

    cout << endl;
    cout << "### Solving problem with ['best_nearest_neighbors'] ###" << endl;

    vector<int> solution = best_nearest_neighbors(this->problem);
    // solution = two_opt(solution, this->problem);

    // if (!check_validity(solution)) {
    //   cout << "ERROR: Solution is not valid" << endl;
    //   exit(1);
    // }

    this->duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    this->solved = true;

    cout << "Solution found in " << this->duration << " seconds" << endl;
    cout << "Legnth of solution: " << this->problem->best_solution_len << endl;

    return solution;
  }


  /**
   * @brief Check if the solution is valid
   * 
   * @param solution The solution vector
   * @return true If the solution is valid
   * @return false If the solution is not valid
   */
  bool check_validity(vector<int> solution) {
    int sum = 0;

    for (int i = 0; i < this->problem->n_points; i++) {
      if (check_in(solution, i)) sum += 1;
    }

    return sum == this->problem->n_points;
  } 

public:
  /**
   * @brief Construct a new Solver object
   * 
   * @param problem The problem to solve
   */
  Solver(Problem * problem) {
    this->duration = 0;
    this->found_length = 0;

    this->solved = false;
    this->problem = problem;
    this->solution = compute_solution();
  }
};

#endif // SOLVER_HPP
