
import numpy as np
import matplotlib.pyplot as plt
import sys
from pylab import *
from mpl_toolkits.mplot3d import Axes3D

Re = 6378137 # meter (Earth radius)


if len(sys.argv) != 2:
    print "Este programa necesita un (1) argumento para funcionar"
    sys.exit()


filename=sys.argv[1]
pimp=np.loadtxt(filename)





fig = figure()
ax = Axes3D(fig)
ax.set_aspect('equal')
ax.set_xlabel("$x$",fontsize=25)
ax.set_ylabel("$y$",fontsize=25)
ax.set_zlabel("$z$",fontsize=25)
ax.set_title("$\mathrm{Trayectoria}$", fontsize=25)
ax.plot(pimp[:,0]/Re, pimp[:,1]/Re, pimp[:, 2]/Re)


filename = filename[:-4]
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
plt.show()