import numpy as np


def global_discrete_recombination(p1, p2):
    dim = len(p1)
    assert dim == len(p2)
    rands = np.random.rand(1, dim)
    offspring1 = np.zeros(dim)
    offspring2 = np.zeros(dim)
    for i in range(dim):
        if rands[i] < 0.5:
            offspring1[i] = p1[i]
            offspring2[i] = p2[i]
        else:
            offspring1[i] = p2[i]
            offspring2[i] = p1[i]
    return offspring1, offspring2


def arithmetic_recombination(p1, p2, weight):
    dim = len(p1)
    # assert dim == len(p2)
    offspring1 = weight*p1 + (1-weight)*p2
    offspring2 = weight*p2 + (1-weight)*p1
    return offspring1, offspring2


def simple_arithmetic_recombination(p1, p2, w):
    dim = len(p1)
    # assert dim == len(p2)
    offspring1 = np.zeros(dim)
    offspring2 = np.zeros(dim)
    prob = np.random.random_sample()
    recom_point = np.random.randint(0, dim)
    if prob < 0.5:
        offspring1[0:recom_point] = p1[0:recom_point]
        offspring1[recom_point:] = w*p1[recom_point:] + (1-w)*p2[recom_point:]
        offspring2[0:recom_point] = p2[0:recom_point]
        offspring2[recom_point:] = w*p2[recom_point:] + (1-w)*p1[recom_point:]
    else:
        offspring1[recom_point:] = p1[recom_point:]
        offspring1[0:recom_point] = w * p1[0:recom_point] + (1 - w) * p2[0:recom_point]
        offspring2[recom_point:] = p2[recom_point:]
        offspring2[0:recom_point] = w * p2[0:recom_point] + (1 - w) * p1[0:recom_point]
    return offspring1, offspring2


def quadratic_recombination(p1, p2):
    return None

