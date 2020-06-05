from scipy.optimize import linear_sum_assignment
from myEA.similarity_measure import dist_Euclidean
import numpy as np


def Munkres_algorithm(parents_gene, offsprings_gene):
    num_p = len(parents_gene)
    num_o = len(offsprings_gene)
    cost = np.zeros((num_p, num_o))
    for i in range(num_p):
        for j in range(num_o):
            cost[i][j] = dist_Euclidean(parents_gene[i], offsprings_gene[j])
    row_idx, col_idx = linear_sum_assignment(cost)
    return row_idx, col_idx, cost[row_idx, col_idx].sum();

#def Munkres_assigment(parent, )