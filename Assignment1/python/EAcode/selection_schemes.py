#!/usr/bin/env python
# selection schemes are copy from https://github.com/SUSTech-EC2020/selectionSchemes

import random
import math
import numpy as np


def select_individual(population, prob_list):
    prob = random.uniform(0, 1)
    p_size = len(population)
    individual = None
    for i in range(p_size):
        prob -= prob_list[i]
        if prob < 0:
            individual = population[i]
            break
    return individual

# Selection schemes


def rank_based_selection (fitness_list):
    ascending_rank = sorted(range(len(fitness_list)), key=lambda k: fitness_list[k], reverse=True)
    prob_list = []
    sum_rank = sum(ascending_rank) + len(ascending_rank)
    for rank in ascending_rank:
        prob_list.append((rank+1)/sum_rank)

    return prob_list


def exponential_ranking_selection (fitness_list):
    ascending_rank = sorted(range(len(fitness_list)), key=lambda k: fitness_list[k], reverse=True)
    mu = len(fitness_list)
    C = mu - ( math.exp(1) - math.exp(1-mu) ) / ( math.exp(1) -1 )
    prob_list = []
    for rank in ascending_rank:
        prob_list.append( ( 1 - math.exp(-rank)) / C )

    return prob_list

