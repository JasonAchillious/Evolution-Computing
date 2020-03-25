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

