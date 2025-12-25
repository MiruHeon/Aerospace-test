import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x, y, z = [], [], []

with open("orbit.txt") as f:
    for line in f:
        xi, yi, zi = map(float, line.split())
        x.append(xi)
        y.append(yi)
        z.append(zi)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot(x, y, z, label="Satellite Orbit")
ax.scatter(0, 0, 0, color='blue', label="Earth")

ax.set_xlabel("X (km)")
ax.set_ylabel("Y (km)")
ax.set_zlabel("Z (km)")
ax.legend()

plt.show()
