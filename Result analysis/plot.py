from matplotlib import pyplot
import numpy as np

# Charger les données depuis le fichier
data = np.loadtxt('data.txt', delimiter='|')

pyplot.plot(data[:,0],data[:,1],label="Voltage")
pyplot.legend()
pyplot.savefig("Voltage.png")
pyplot.close()

pyplot.plot(data[:,0],data[:,2],label="Current")
pyplot.legend()
pyplot.savefig("Current")
pyplot.close()