import numpy as np
import matplotlib.pyplot as plt

pimp=np.loadtxt("poblaciones_1_20.dat")

n_points = 1000
x = pimp[:,0]
y  =  pimp[:,1]

fig = plt.figure(figsize=(9.5,9.0))
ax = plt.axes()

ax.set_xlabel("$x$",fontsize=25)
ax.set_ylabel("$y$",fontsize=25)
ax.set_title("$\mathrm{Population\ growth}$", fontsize=25)


plt.plot(x,y, color='red', label="$f(x)=y$")

ax.legend()


filename = 'poblaciones_1_20'
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()