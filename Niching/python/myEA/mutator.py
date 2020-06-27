import numpy as np


def standard_cauchy_mutator(offspring, alpha, func):
    dim = len(offspring)
    set_boundary_rate = 0.5
    illegal = True
    mutated_offspring = np.zeros(dim)
    while illegal:
        illegal = False
        for k in range(dim):
            mutated_offspring[k] = offspring[k]
        for k in range(dim):
            ub = func.get_ubound(k)
            lb = func.get_lbound(k)
            mutated_offspring[k] += alpha * (ub-lb) * np.random.standard_cauchy()
            if mutated_offspring[k] > ub:
                prob = np.random.uniform()
                if prob < set_boundary_rate:
                    mutated_offspring[k] = ub
                else:
                    illegal = True
                    break
            if mutated_offspring[k] < lb:
                prob = np.random.uniform()
                if prob < set_boundary_rate:
                    mutated_offspring[k] = lb
                else:
                    illegal = True
                    break

    return mutated_offspring