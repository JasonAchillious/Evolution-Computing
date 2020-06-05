import math
import numpy as np


def select_parents_by_prob_list(prob_list, popu):
    probs = np.random.uniform(0, 1, 2)
    i=-1
    j=-1
    while probs[0] > 0:
        i += 1
        probs[0] -= prob_list[i]
    while probs[1] > 0:
        j += 1
        probs[1] -= prob_list[j]

    return popu[i], popu[j]


def select_idv_by_prob_list(prob_list, popu):
    prob = np.random.uniform(0, 1)
    i = 0
    while prob > 0:
        prob -= prob_list[i]
        i += 1
    return popu[i]


def rank_based_selection (fitness_list):
    ascending_rank = sorted(range(len(fitness_list)), key=lambda k: fitness_list[k], reverse=False)
    prob_list = []
    sum_rank = sum(ascending_rank) + len(ascending_rank)
    for rank in ascending_rank:
        prob_list.append((rank+1)/sum_rank)

    return prob_list


def exponential_ranking_selection (fitness_list):
    ascending_rank = sorted(range(len(fitness_list)), key=lambda k: fitness_list[k], reverse=False)
    mu = len(fitness_list)
    C = mu - ( math.exp(1) - math.exp(1-mu) ) / ( math.exp(1) -1 )
    prob_list = []
    for rank in ascending_rank:
        prob_list.append( ( 1 - math.exp(-rank)) / C )
    # print ('Output of exponential_ranking_selection: ')
    # print(prob_list)
    return prob_list
