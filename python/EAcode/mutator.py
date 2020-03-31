import random


def mutator_swap(individual: list) -> list:
    length = len(individual)
    p1 = random.randint(0, length-1)
    p2 = random.randint(0, length-1)
    tmp = individual[p1]
    individual[p1] = individual[p2]
    individual[p2] = tmp
    return individual


def mutator_swap_mul(individual: list, swap_time) -> list:
    assert swap_time * 2 <= len(individual)
    length = len(individual)
    p_mut = random.sample(range(length), swap_time*2)
    while len(p_mut) > 0:
        p1 = p_mut[0]
        p2 = p_mut[1]
        p_mut.remove(p1)
        p_mut.remove(p2)
        tmp = individual[p1]
        individual[p1] = individual[p2]
        individual[p2] = tmp


def mutator_reverse_by_length(individual: list, rev_length):
    idv_length = len(individual)
    assert rev_length % 2 == 0 and rev_length <= idv_length
    rev_s = random.randint(0, idv_length-rev_length)
    rev_e = rev_s + rev_length
    individual[rev_s:rev_e] = individual[rev_s:rev_e][::-1]


def mutator_001(individual: list):
    max_i = max(individual)
    min_i = min(individual)
    i_mut = random.randint(min_i+1, max_i)
    p1 = individual.index(i_mut)
    p2 = individual.index(min_i)
    tmp = individual[ p1 ]
    individual[ p1 ] = individual[ p2 ]
    individual[ p2 ] = tmp


def mutator_002(individual: list):
    max_i = max(individual)
    min_i = min(individual)
    i_mut = random.randint(min_i, max_i-1)
    j_mut = i_mut+1
    p1 = individual.index(i_mut)
    p2 = individual.index(j_mut)
    tmp = individual[ p1 ]
    individual[ p1 ] = individual[ p2 ]
    individual[ p2 ] = tmp


def mutator_003(individual: list):
    prob = random.uniform(0, 1)
    thred = 1 / len(individual)
    i_max = max(individual)
    i_min = min(individual)
    if prob < thred:
        p1 = individual.index(i_min)
        i2 = i_min + 1
        p2 = individual.index(i2)
        tmp = individual[ p1 ]
        individual[ p1 ] = individual[ p2 ]
        individual[ p2 ] = tmp
    else:
        for idx, i in enumerate(individual):
            if i == i_max:
                individual[idx] = i_min + 1
            elif i >= i_min+1:
                individual[idx] += 1
