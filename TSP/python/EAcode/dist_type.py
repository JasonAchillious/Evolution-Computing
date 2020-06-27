import math


# Euclidean distance between two points


def dist_euc_2d(cityA:tuple, cityB:tuple) -> float:
    dx = cityA[1] - cityA[1]
    dy = cityA[2] - cityB[2]
    return math.sqrt(dx*dx + dy*dy)
