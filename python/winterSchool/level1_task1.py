from math import exp

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = np.linspace(-2, 2, 50)
y = np.linspace(-2, 2, 50)
T= 50 * np.e**(-(x**2 + y**2)) + 20

X, Y = np.meshgrid(x, y)
Z = X**2 + Y**2
x0, y0 = 0.8,0.6
T0 = 50 * np.e**(-(x0**2 + y0**2)) + 20
print(f"Темпереатура в точке ({x0};{y0}): {T0}")





z0 = np.exp(-(x0**2 + y0**2))
print(f"z({x0}, {y0}) = {z0:.4f}")

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis')
ax.set_title('Параболоид: z = x² + y²')
plt.show()
