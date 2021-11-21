import glob

import numpy as np
import pandas as pd

from classes import instances
from classes import solvers


def use_solver_to_compute_solution(solver, improve, index, results, name, verbose, show_plots, seed):
  solver.bind(improve)
  solver.compute_solution(return_value=False, verbose=verbose, seed=seed)

  if verbose:
    print(f"the total length for the solution found is {solver.found_length}",
          f"while the optimal length is {solver.problem_instance.best_sol}",
          f"the gap is {solver.gap}%",
          f"the solution is found in {solver.duration} seconds", sep="\n")

  index.append((name, solver.name_method))
  results.append([solver.found_length, solver.problem_instance.best_sol, solver.gap, solver.duration])

  if show_plots:
    solver.plot_solution()


def run(show_plots=False, verbose=False):
  problems = glob.glob('./problems/*.tsp')
  # problems = ["./problems/eil76.tsp"]
  results = []
  index = []
  i = 0;

  seeds = [11, 939, 490, 982, 993, 956, 49, 357, 938, 771]

  for problem_path in problems:
    prob_instance = instances.ProblemInstance(problem_path)

    if verbose:
        prob_instance.print_info()
    if show_plots:
        prob_instance.plot_data()

    solver = solvers.TSPSolver("random", prob_instance)
    use_solver_to_compute_solution(solver, "two_opt", index, results, problem_path, verbose, show_plots, seeds[i])

    i += 1

  if prob_instance.exist_opt and show_plots:
    solver = solvers.TSPSolver("optimal", prob_instance)
    solver.solved = True
    solver.solution = np.concatenate([prob_instance.optimal_tour, [prob_instance.optimal_tour[0]]])
    solver.plot_solution()

  index = pd.MultiIndex.from_tuples(index, names=['problem', 'method'])

  return pd.DataFrame(results, index=index, columns=["tour length", "optimal solution", "gap", "time to solve"])


if __name__ == '__main__':
  df = run(show_plots=False, verbose=True)
  df.to_csv("./results.csv")
