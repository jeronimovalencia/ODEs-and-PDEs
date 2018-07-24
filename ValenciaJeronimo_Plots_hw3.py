import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


datosCM = np.genfromtxt("datosCampoMagnetico.dat")

fig2 = plt.figure()
ax = fig2.gca(projection = '3d')
ax.plot(datosCM[:,1],datosCM[:,2],datosCM[:,3])
plt.savefig("graficasCM_3D.pdf")
plt.clf()
plt.close()

plt.figure(figsize=(8,8))
plt.subplot(221)
plt.title("Plano XY")
plt.plot(datosCM[:,1],datosCM[:,2])
plt.subplot(222)
plt.title("Plano XZ")
plt.plot(datosCM[:,1],datosCM[:,3])
plt.subplot(223)
plt.title("Plano YZ")
plt.plot(datosCM[:,2],datosCM[:,3])
plt.subplot(224)
plt.title("Y vs. Tiempo")
plt.plot(datosCM[:,0],datosCM[:,2])
plt.savefig("graficasCM_vistas.pdf")
plt.clf()
plt.close()

datosTamborCerradas = np.genfromtxt("datosTamborCerradas.dat")

N = 10

plt.figure(figsize=(8,10))
for i in range(N):
	plt.subplot(5,2,i+1)
	plt.plot(np.arange(0, 1, 0.01),datosTamborCerradas[i,:])

plt.savefig("cortesCerradas.pdf")
plt.clf()
plt.close()


fig3 = plt.figure()
ax1 = fig3.gca(projection = '3d')
X = np.arange(0, 1, 0.01)
Y = np.arange(0, 1, 0.01)
X, Y = np.meshgrid(X, Y)
ax1.plot_surface(X,Y,datosTamborCerradas[N:,:])
plt.title("Membrana en tiempo final (Cond. Cerradas)")
plt.savefig("graficaTamborCerradas.pdf")
plt.clf()
plt.close()

datosTamborAbiertas = np.genfromtxt("datosTamborAbiertas.dat")
datosTamborInicial = np.genfromtxt("datosTamborInicial.dat")

plt.figure(figsize=(8,10))
for i in range(N):
	plt.subplot(5,2,i+1)
	plt.plot(np.arange(0, 1, 0.01),datosTamborAbiertas[i,:])

plt.savefig("cortesAbiertas.pdf")
plt.clf()
plt.close()

fig4 = plt.figure()
ax2 = fig4.gca(projection = '3d')

ax2.plot_surface(X,Y,datosTamborAbiertas[N:,:])
plt.title("Membrana en tiempo final (Cond. Abiertas)")
plt.savefig("graficaTamborAbiertas.pdf")
plt.clf()
plt.close()

fig5 = plt.figure()
ax3 = fig5.gca(projection = '3d')
ax3.plot_surface(X,Y,datosTamborInicial)
plt.title("Condición inicial para la membrana")
plt.savefig("graficaTamborInicial.pdf")
plt.clf()
plt.close()



















