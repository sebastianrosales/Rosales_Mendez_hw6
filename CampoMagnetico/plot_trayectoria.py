import numpy as np
import matplotlib.pyplot as plt
import sys
from mpl_toolkits.mplot3d import Axes3D

if len(sys.argv) != 2:
    print "Este programa necesita un (1) argumento para funcionar"
    sys.exit()


filename=sys.argv[1]
pimp=np.loadtxt(filename)

n_points = 100
x = pimp[:,1]
y  =  pimp[:,2]
z  =  pimp[:,3]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

o=fig.gca(projection='3d')
o.scatter(x,y,z)



o.set_xlabel("$x$",fontsize=25)
o.set_ylabel("$y$",fontsize=25)
o.set_zlabel("$z$",fontsize=25)
o.set_title("$\mathrm{Trayectoria}$", fontsize=25)

filename = filename[:-4]
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
plt.show()
