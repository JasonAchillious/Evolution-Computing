import random

"""
    randomly initialize the population    
"""


def init_random(p_size, cities, tour_length) -> list:
    popu = []
    for i in range(p_size):
        popu.append(random.sample(cities, tour_length))
    return popu