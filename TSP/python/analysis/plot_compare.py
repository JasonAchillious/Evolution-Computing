import pandas as pd
import matplotlib.pyplot as plt
import os

file_dir = "../results/"
figure_output = "dj38_swap-1_shuffle.png"
avgs = pd.DataFrame(columns=[])
csv_files = ["avg_dj38_shuffle000.csv",
             "avg_dj38_swap1.csv"
             ]
title = "dj38"
labels = ["shuffle", "1-swap"]

for idx, f in enumerate(csv_files):
    df = pd.read_csv(os.path.join(file_dir, f))
    avgs[f] = df["avg"]

print(avgs.columns)
avgs = avgs.values
print(avgs.shape)
print(avgs)

fig = plt.figure(figsize=(4,4))
plt.tight_layout()
plt.plot(avgs[:,0], color="g",linestyle = ":", label=labels[0])
plt.plot(avgs[:,1], color="b",linestyle = "-",  label=labels[1])
#plt.xlim((0, 50000))
#plt.xscale('log')

plt.title(title, fontsize='large', fontweight='bold')
plt.legend()
plt.ylabel("Distance")
plt.xlabel("Evalution *10")
plt.savefig(figure_output,  bbox_inches = 'tight')
plt.show()