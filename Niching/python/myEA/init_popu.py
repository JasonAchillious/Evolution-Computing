from cec2013.cec2013 import *
import numpy as np


def rand_init(popu_size, func):
    dim = func.get_dimension()
    popu = np.zeros((popu_size, dim))
    ub = np.zeros(dim)
    lb = np.zeros(dim)

    for k in range(dim):
        ub[k] = func.get_ubound(k)
        lb[k] = func.get_lbound(k)

    for j in range(popu_size):
        popu[j] = lb + (ub - lb) * np.random.rand(1, dim)

    return popu
