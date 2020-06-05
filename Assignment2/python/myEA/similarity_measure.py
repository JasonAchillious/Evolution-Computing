import numpy as np


def dist_Euclidean(p1, p2):
    diff = p1 - p2
    return np.sqrt(np.sum(diff*diff))


def dist_abs_norm(p1, p2):
    diff = p1 - p2
    return np.sum(np.abs(diff))


def share_func_Eucl(popu, idv, radius, alpha, func):
    dim = len(popu)
    dists = np.array([dist_Euclidean(p, idv) for p in popu])
    sh_arr = np.array([1 - ((dists[i] / radius) ** alpha) if dists[i] < radius else 0 for i in range(dim)])

    return sh_arr


def share_func_Manha(popu, idv, radius, alpha, func):
    dim = len(popu)
    dists = np.array([dist_abs_norm(p, idv) for p in popu ])
    sh_arr = np.array([1 - ((dists[i] / radius) ** alpha) if dists[i] < radius else 0 for i in range(dim) ])

    return sh_arr