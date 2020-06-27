import pandas as pd
import os


dir_path = "../results"

files_path = os.listdir(dir_path)
file_group = []
f_arr = []
for f in files_path:
    f_arr.append( f.split("-"))

for id1, arr1 in enumerate(f_arr):
    for id2, arr2 in enumerate(f_arr):
        if len(arr1) == 2 and len(arr2) == 2:
            if (arr1[0] == arr2[0]
                    and arr1[1] == "01.csv"
                    and arr2[1] == "02.csv"
                    and arr1[0] == "wi29shuffle0"):
                file_group.append( (files_path[id1], files_path[id2]) )
print(file_group)


for group in file_group:
    avg_dict = dict()
    name_arr = group[0].split("-")
    output = os.path.join("../results/",  "avg_" + name_arr[0] + ".csv")
    for file_name in group:
        path = "../results/" + file_name
        df_tmp = pd.read_csv(path)
        header = [h for h in df_tmp.columns if "fitness" in h]
        print(header)
        avg_dict[path] = df_tmp[header].mean(axis=1)
    df_mean = pd.DataFrame(avg_dict)
    df_mean["avg"] = df_mean.mean(axis=1)
    df_mean.to_csv(output, index=False)
