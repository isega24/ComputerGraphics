import matplotlib.pyplot as pyplt
import sys
infile = open(sys.argv[1], 'r')
line1 = infile.readline().split()
planets = int(line1[0])
steps = int(line1[1])
line1 = infile.readline().split()
paintingX = []
paintingY = []
for i in range(planets):
    paintingX.append([])
    paintingY.append([])

for lin in infile:
    line = lin.split()
    for i in range(planets):
	paintingX[i].append(float(line[2*i]))
        paintingY[i].append(float(line[2*i+1]))
# Cerramos el fichero.
for i in range(planets):
    pyplt.plot(paintingX[i],paintingY[i])

pyplt.show()
infile.close()
