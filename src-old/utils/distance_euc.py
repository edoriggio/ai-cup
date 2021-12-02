import numpy as np

def distance_euc(point_i, point_j):
  rounding = 0
  x_i, y_i = point_i[0], point_i[1]
  x_j, y_j = point_j[0], point_j[1]
  distance = np.sqrt((x_i - x_j) ** 2 + (y_i - y_j) ** 2)
  
  return round(distance, rounding)
