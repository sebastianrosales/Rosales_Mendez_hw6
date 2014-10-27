import numpy as np
import matplotlib.pyplot as plt
import sys

if len(sys.argv) != 2:
    print "Este programa necesita un (1) argumento para funcionar"
    sys.exit()


filename=sys.argv[1]
pimp=np.loadtxt(filename)

n_points = 1000
x = pimp[:,1]
y  =  pimp[:,2]

fig = plt.figure(figsize=(9.5,9.0))
ax = plt.axes()

ax.set_xlabel("$x$",fontsize=25)
ax.set_ylabel("$y$",fontsize=25)
ax.set_title("$\mathrm{Dinamica\ poblaciones}$", fontsize=25)


plt.plot(x,y, color='red', label="$f(x)=y$")

ax.legend()


filename = filename[:-4]
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
