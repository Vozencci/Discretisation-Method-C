import math
import numpy as np
import matplotlib.pyplot as plt

for (i,j) in zip(range(1,5),[ 0.5 , 1 , 1.5 , 2 ]):

    Plot_list = []
    
    with open('graphes1.txt', 'r') as f:
        
        lines = f.readlines()
        
        x_analytique = [float(line.split()[0]) for line in lines]
        y_analytique = [float(line.split()[i]) for line in lines]
        
        X_analytique = np.array(x_analytique)
        Y_analytique = np.array(y_analytique)
    
    with open('graphes2.txt', 'r') as g:
        
        lines = g.readlines()
        
        x_numerique = [float(line.split()[0]) for line in lines]
        y_numerique = [float(line.split()[i]) for line in lines]
        
        X_numerique = np.array(x_numerique)
        Y_numerique = np.array(y_numerique)
    
    Plot_list.append(plt.plot(abs(X_analytique), abs(Y_analytique - Y_numerique), label="t = " + str(j) + "π"))
 
for k in Plot_list:
 
    plt.plot()
    plt.grid()
    plt.axis([0, 10 * math.pi, -1, 1])
    plt.title('Graphe différence solutions Analytique-Numérique explicite')
    plt.xlabel("position x (en m)")
    plt.ylabel("pression P (en Pa)")
    plt.legend(loc = 4)    
    plt.show()