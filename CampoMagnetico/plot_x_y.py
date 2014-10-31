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





fig = plt.figure()

plt.xlabel("$x$",fontsize=25)
plt.ylabel("$y$",fontsize=25)
plt.title("Proyeccion en el plano xy", fontsize=25)
plt.plot(pimp[:,0]/Re, pimp[:,1]/Re)


filename = filename[:-4]
plt.savefig(filename + '_x_y.pdf',format = 'pdf', transparent=True)
plt.close()
plt.show()
