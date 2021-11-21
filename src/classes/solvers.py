from time import time as t

import numpy as np
import matplotlib.pyplot as plt

from solver import random
from solver import two_opt
from solver import simulated_annealing


class TSPSolver:
  def __init__(self, algorithm_name, problem_instance):
    self.improver = simulated_annealing.simulated_annealing
    self.solver = random.random
    self.duration = np.inf
    self.found_length = np.inf
    self.algorithm_name = algorithm_name
    self.algorithms = [algorithm_name]
    self.name_method = 'initialized with ' + algorithm_name
    self.solved = False
    self.problem_instance = problem_instance
    self.solution = None


  def bind(self, local_or_meta):
    self.algorithms.append(local_or_meta)
    self.name_method += ', improved with ' + local_or_meta


  def pop(self):
    self.algorithms.pop()
    self.name_method = self.name_method[::-1][self.name_method[::-1].find('improved'[::-1]) + len('improved') + 2:][::-1]


  def compute_solution(self, seed=None, verbose=True, return_value=True):
    self.solved = False

    if verbose:
      print(f'###  solving with {self.algorithms} ####')

    start_time = t()

    sol = self.solver(self.problem_instance, seed)
    self.solution = sol[0]
    seed = sol[1]

    if not self.check_if_solution_is_valid():
      print(f'Error the solution of {self.algorithm_name} for problem {self.problem_instance.name} is not valid')
      
      if return_value:
        return False

    for i in range(1, len(self.algorithms)):
      improver = self.algorithms[i]
      # self.solution = self.improver(self.solution, self.problem_instance)
      self.solution = two_opt.two_opt(self.solution, self.problem_instance)

      if not self.check_if_solution_is_valid():
        print(f'Error the solution of {self.algorithm_name} with {improver} for problem {self.problem_instance.name} is not valid')

        if return_value:
          return False

    end_time = t()
    self.duration = np.around(end_time - start_time, 3)
    self.solved = True
    self.evaluate_solution()
    self._gap()

    if return_value:
      return self.gap, seed


  def plot_solution(self):
    assert self.solved, 'You can\'t plot the solution, you need to compute it first!'
    plt.figure(figsize=(8, 8))
    self._gap()
    plt.title(f'{self.problem_instance.name} solved with {self.name_method} solver, gap {self.gap}')
    ordered_points = self.problem_instance.points[self.solution]
    plt.plot(ordered_points[:, 1], ordered_points[:, 2], 'b-')
    plt.plot(ordered_points[[0, -1], 1], ordered_points[[0, -1], 2], 'b-')
    plt.show()


  def check_if_solution_is_valid(self):
    right_values = np.sum([self.check_validation(i, self.solution) for i in np.arange(self.problem_instance.nPoints)])

    return right_values == self.problem_instance.nPoints


  @staticmethod
  def check_validation(node, solution):
    if np.sum(solution == node) == 1:
      return 1
    else:
      return 0


  def evaluate_solution(self, return_value=False):
    total_length = 0
    starting_node = self.solution[0]
    from_node = starting_node

    for node in self.solution[1:]:
      total_length += self.problem_instance.dist_matrix[from_node, node]
      from_node = node

    total_length += self.problem_instance.dist_matrix[from_node, starting_node]
    self.found_length = total_length

    if return_value:
      return total_length


  def pass_and_check_if_solution_is_valid(self, solution):
    right_values = np.sum([self.check_validation(i, solution) for i in np.arange(self.problem_instance.nPoints)])

    return right_values == self.problem_instance.nPoints


  def _gap(self):
    self.evaluate_solution(return_value=False)
    self.gap = np.round(((self.found_length - self.problem_instance.best_sol) / self.problem_instance.best_sol) * 100, 2)
