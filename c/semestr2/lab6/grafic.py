import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

sizes = [100, 200, 400, 600, 800, 1000]
threads_list = [1,2, 4, 8, 16]
colors = plt.cm.viridis(np.linspace(0, 1, len(threads_list)))

threads_time_1 = [7, 28, 137, 450, 1300, 2350]
threads_time_2  = [4, 21, 82, 240, 571, 1341]
threads_time_4  = [2, 11, 50, 151, 358, 793]
threads_time_8  = [1, 8, 40, 124, 317, 642]
threads_time_16 = [2, 12, 36, 123, 282, 548]


plt.figure(figsize=(14, 7))

plt.plot(sizes, threads_time_1, "o-", label="1 поток", color=colors[0], linewidth=2, markersize=8)
plt.plot(sizes, threads_time_2,  'o-', label='2 потока',  color=colors[1], linewidth=2, markersize=8)
plt.plot(sizes, threads_time_4,  's-', label='4 потока',  color=colors[2], linewidth=2, markersize=8)
plt.plot(sizes, threads_time_8,  '^-', label='8 потоков',  color=colors[3], linewidth=2, markersize=8)
plt.plot(sizes, threads_time_16, 'd-', label='16 потоков', color=colors[4], linewidth=2, markersize=8)


plt.xlabel('Размер матрицы (N)', fontsize=12)
plt.ylabel('Время выполнения (мс)', fontsize=12)
plt.title('Зависимость времени перемножения матриц от размера и количества потоков', fontsize=14)
plt.legend(fontsize=10)
plt.grid(True, alpha=0.3, linestyle='--')
plt.yscale('log')
plt.xscale('log')
plt.tight_layout()
plt.show()