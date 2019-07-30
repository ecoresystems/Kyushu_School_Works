import pandas as pd
from matplotlib import pyplot as plt

df = pd.read_csv("testfile.csv")
print(df)
plt.plot(df['collection_size'],df['dp_time'],label="DP Time")
plt.plot(df['collection_size'],df['brutal_time'],label="Brutal Time")
plt.xlabel('Collection Size')
plt.yscale('linear')
plt.ylabel('Execution time (s)')
plt.title('Time comparison')
plt.legend()
plt.savefig("linear.png")
plt.show()
