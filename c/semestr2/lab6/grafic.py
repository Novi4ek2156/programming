import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

sizes = [100, 200, 400, 600, 800, 1000]
threads_list = [2, 4, 8, 16]
colors = plt.cm.viridis(np.linspace(0, 1, len(threads_list)))


threads_time_2  = [4, 24, 82, 240, 653, 1318]
threads_time_4  = [2, 17, 54, 818, 1808, 1434]
threads_time_8  = [1, 8, 40, 130, 1004, 2236]
threads_time_16 = [1, 6, 36, 109, 282, 3109]


theoretical = [n**3 / 1_000_000 for n in sizes]

plt.figure(figsize=(14, 7))


plt.plot(sizes, threads_time_2,  'o-', label='2 потока',  color=colors[0], linewidth=2, markersize=8)
plt.plot(sizes, threads_time_4,  's-', label='4 потока',  color=colors[1], linewidth=2, markersize=8)
plt.plot(sizes, threads_time_8,  '^-', label='8 потоков',  color=colors[2], linewidth=2, markersize=8)
plt.plot(sizes, threads_time_16, 'd-', label='16 потоков', color=colors[3], linewidth=2, markersize=8)


plt.plot(sizes, theoretical, 'k--', label='O(N³) (теоретическая)', alpha=0.7, linewidth=2)


plt.xlabel('Размер матрицы (N)', fontsize=12)
plt.ylabel('Время выполнения (мс)', fontsize=12)
plt.title('Зависимость времени перемножения матриц от размера и количества потоков', fontsize=14)
plt.legend(fontsize=10)
plt.grid(True, alpha=0.3, linestyle='--')
plt.yscale('log')
plt.xscale('log')
plt.tight_layout()
plt.show()