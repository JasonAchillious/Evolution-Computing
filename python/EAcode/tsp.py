from EAcode import EA
from EAcode import mutator
import random

if __name__ == '__main__':

    files = ["dj38.tsp", "qa194.tsp"]
    """
    for f in files:
        for i in range(2, 3):
            for j in range(1, 3):
                EA.ea_swap(
                    tsp_file_path="../instances/" + f,
                    output_path="../results/" + f.split(".")[0] + "_swap-%d-0%d.csv" % (i, j),
                    gen_num=50000,
                    test_num=25,
                    popu_size=10,
                    time_swap=i,
                    start_city=0,
                    p_cities=list(range(1, 29)),
                    tour_length=29
                )
    """
    """
    for f in files:
        for i in range(2, 7, 2):
            for j in range(1, 3):
                EA.ea_reverse(
                    tsp_file_path="./instances/" + f,
                    output_path="./results/" + f.split(".")[ 0 ] + "_reverse-%d-0%d.csv" % (i, j),
                    gen_num=50000,
                    test_num=25,
                    popu_size=10,
                    rev_length=i,
                    start_city=0,
                    p_cities=list(range(1, 29)),
                    tour_length=29
                )
    """

    mutators = [random.shuffle]
    for f in files:
        for idx, mut in enumerate(mutators):
            for j in range(1, 3):
                EA.ea_mutator(
                    tsp_file_path="./instances/" + f,
                    output_path="./results/" + f.split(".")[ 0 ] + "_shuffle-00%d-0%d.csv" % (idx, j),
                    gen_num=50000,
                    test_num=25,
                    popu_size=10,
                    mutator=mut,
                    start_city=0,
                    p_cities=list(range(1, 29)),
                    tour_length=29
                )
