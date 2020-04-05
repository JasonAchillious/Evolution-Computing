import pandas as pd
import matplotlib.pyplot as plt
import os
"""
    
"""

dir_path = "../results/"

op_key = "mutator"
labels = ["mutator001", "mutator002", "mutator003", "swap"]
title = ["dj38", "wi29", "qa194"]
output = "log_exp_mutator.png"

files = ["avg_wi29_exp_rank_swap1.csv", "avg_dj38_exp_rank_swap1.csv", "avg_qa194_exp_rank_swap1.csv"]

files_name = os.listdir(dir_path)
f_name_arr = [s.split("_") for s in files_name]
f_op_group = [files_name[idx] for idx, arr in enumerate(f_name_arr)
           if len(arr) >= 5 and op_key in arr[4] and arr[0] == "avg" ]

f_op_group.sort()
print(f_op_group)

avgs = pd.DataFrame()
for f in f_op_group:
    df = pd.read_csv(os.path.join(dir_path, f))
    avgs[f] = df["avg"]


for f in files:
    df = pd.read_csv(os.path.join(dir_path, f))
    avgs[f] = df["avg"]

print(avgs.columns)
avgs = avgs.values
print(avgs.shape)

fig = plt.figure(figsize=(12,4))
plt.tight_layout()
#plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
ax1 = plt.subplot(131)
plt.plot(avgs[:,0],color="y",linestyle = "--", label=labels[0])
plt.plot(avgs[:,1],color="b",linestyle = "-", label=labels[1])
plt.plot(avgs[:,2],color="g",linestyle = "-.", label=labels[2])
plt.plot(avgs[:,10],color="r", linestyle = ":", label=labels[3])
plt.xscale('log')
plt.xlabel('Evalution *10')
plt.ylabel('Distance')
plt.title(title[0])
plt.legend()
ax2 = plt.subplot(132)
plt.plot(avgs[:,3], color="y",linestyle = "--", label=labels[0])
plt.plot(avgs[:,4], color="b",linestyle = "-",  label=labels[1])
plt.plot(avgs[:,5], color="g",linestyle = "-.", label=labels[2])
plt.plot(avgs[:,11],color="r", linestyle = ":", label=labels[3])
plt.xscale('log')
plt.xlabel('Evalution *10')
plt.ylabel('Distance')
plt.title(title[1])
plt.legend()
ax3 = plt.subplot(133)
plt.plot(avgs[:,6], color="y",linestyle = "--", label=labels[0])
plt.plot(avgs[:,7], color="b",linestyle = "-", label=labels[1])
plt.plot(avgs[:,8], color="g",linestyle = "-.", label=labels[2])
plt.plot(avgs[:,9],color="r", linestyle = ":", label=labels[3])
plt.xscale('log')
plt.xlabel('Evalution *10')
plt.ylabel('Distance')
plt.title(title[2])
plt.legend()
#print(avgs[:,7])


#fig.suptitle("Swap")
plt.savefig(output)
plt.show()



