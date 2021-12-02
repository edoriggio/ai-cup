import numpy as np

def nearest_neighbor(instance_, starting_node=0):
    dist_matrix = np.copy(instance_.dist_matrix)
    n = int(instance_.nPoints)
    node = starting_node
    tour = [node]
    for _ in range(n - 1):
        for new_node in np.argsort(dist_matrix[node]):
            if new_node not in tour:
                tour.append(new_node)
                node = new_node
                break
    # tour.append(starting_node)
    return np.array(tour)


def best_nearest_neighbor(instance_):
    solutions, lengths = [], []
    for start in range(instance_.nPoints):
        new_solution = nearest_neighbor(instance_, starting_node=start)
        solutions.append(new_solution)
        lengths.append(compute_length(new_solution, instance_.dist_matrix))

    if lengths is []:
        return None
    else:
        solution = solutions[np.argmin(lengths)]
        return solution