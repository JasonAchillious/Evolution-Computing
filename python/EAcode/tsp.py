from EAcode import EA

if __name__ == '__main__':
    EA.ea_swap(
        tsp_file_path="../instances/wi29.tsp",
        output_path="../results/swap_triple02.csv",
        gen_num=50000,
        test_num=25,
        popu_size=10,
        time_swap=3
    )