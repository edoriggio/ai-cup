import numpy as np

from utils import compute_length

def random(instance, seed=None):
  if seed is not None:
    np.random.seed(seed)
  
  seed = np.random.get_state()[1][0]
  sol = np.random.choice(np.arange(instance.nPoints), size=instance.nPoints, replace=False)

  return sol, seed
