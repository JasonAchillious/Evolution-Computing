from EAcode.dist_type import *


def circuit_euc_dist(src_index: int, city_index: list, cities: list)->float:
    d_total = dist_euc_2d(cities[src_index], cities[city_index[0 ] ]) \
         + dist_euc_2d(cities[src_index], cities[city_index[-1 ] ])
    for i in range(len(city_index) - 1):
        d_total += dist_euc_2d(cities[city_index[i]], cities[city_index[i + 1]])
    return d_total
