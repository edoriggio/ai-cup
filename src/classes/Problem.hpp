#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../utils/split.hpp"
#include "../utils/matrices.hpp"
#include "../utils/distance.hpp"

using namespace std;

#ifndef PROBLEM_HPP
#define PROBLEM_HPP

class Problem {
public:
  bool exists_optimal = false;

  string name;
  string filename;

  int n_points;
  float best_solution_len;

  vector<string> lines;
  vector<int> optimal_tour;
  vector<vector<float> > points;
  vector<vector<float> > distance_matrix;


  /**
   * @brief Contructor of the Problem class
   * 
   * @param filename The name of the file
   */
  Problem(string filename) {
    this->filename = filename;
    this->lines = read_file(filename);

    this->name = split(lines[0], " : ")[1];
    this->n_points = stoi(split(lines[3], " : ")[1]);
    this->best_solution_len = stof(split(lines[5], " : ")[1]);

    this->points = parse_points(lines, this->n_points);
    this->distance_matrix = compute_distance_matrix(this->points, this->n_points);
    this->optimal_tour = check_optimal_tour();
  }


  /**
   * @brief Prints the problem info
   */
  void print_info() {
    cout << "\n\n#############################" << endl;
    cout << "Problem: " << this->name << endl;
    cout << "Number of points: " << this->n_points << endl;
    cout << "Best solution: " << (int)this->best_solution_len << endl;
    cout << "Optimal tour: " << boolalpha << this->exists_optimal << endl;
  }

private:
  /**
   * @brief Reads the problem from a file
   * 
   * @param filename The name of the file 
   * @return A vector of strings containing the lines of the file
   */
  vector<string> read_file(string filename) {
    ifstream file(filename);
    vector<string> lines;
    string line;

    while (getline(file, line)) {
      lines.push_back(line);
    }

    return lines;
  }


  /**
   * @brief Parses the points of the problem
   * 
   * @param lines The lines of the file
   * @param n_points The total number of points
   * @return A matrix containing the points
   */
  vector<vector<float> > parse_points(vector<string> lines, int n_points) {
    vector<vector<float> > points(n_points, vector<float>(3));
    
    for (int i = 7; i < n_points + 7; i++) {
      points[i-7][0] = stof(split(lines[i], " ")[0]);
      points[i-7][1] = stof(split(lines[i], " ")[1]);
      points[i-7][2] = stof(split(lines[i], " ")[2]);
    }

    return points;
  }


  /**
   * @brief Compute the distance matrix
   * 
   * @param points The points of the problem
   * @param n_points The total number of points
   * @return A matrix containing the distance matrix
   */
  vector<vector<float> > compute_distance_matrix(vector<vector<float> > points, int n_points) {
    vector<vector<float> > distance_matrix(n_points, vector<float>(n_points));

    for (int i = 0; i < n_points; i++) {
      for (int j = i; j < n_points; j++) {
        distance_matrix[i][j] = distance(points[i], points[j]);
      }
    }

    vector<vector<float> > transposed_matrix = m_transpose(distance_matrix);
    distance_matrix = m_sum(distance_matrix, transposed_matrix);

    return distance_matrix;
  }


  /**
   * @brief Parses the optimal tour
   * 
   * @return A vector containing the optimal tour
   */
  vector<int> check_optimal_tour() {
    vector<int> tour(this->n_points);

    if (this->filename == "./problems/eil76.tsp" || this->filename == "./problems/kroA100.tsp") {
      this->exists_optimal = true;
      
      ifstream file(this->filename.replace(this->filename.end()-3, this->filename.end(), "opt.tour"));
      vector<string> lines;
      string line;

      while (getline(file, line)) {
        lines.push_back(line);
      }

      for (int i = 6; i < this->n_points + 6; i++) {
        tour[i-6] = stoi(lines[i]);
      }

      return tour;
    }

    return vector<int>();
  }
};

#endif // PROBLEM_HPP
