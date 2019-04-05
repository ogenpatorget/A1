import numpy as np
import matplotlib.pyplot as plt

interval = np.array([10, 100, 1000, 10000, 100000])
cores = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15])
y_old = np.array([0, 0.986, 3.844, 8.778, 15.552, 24.223, 34.669, 47.342, 61.740, 79.292, 96.145])

line1 = plt.plot(x,y_b, label="Barnes hut")
line2 = plt.plot(x, y_old, label="Normal")


plt.xlabel("Number of particles[N]")
plt.ylabel("Time[s]")
plt.title("Complexity graph for both methods")
plt.legend()

plt.show()