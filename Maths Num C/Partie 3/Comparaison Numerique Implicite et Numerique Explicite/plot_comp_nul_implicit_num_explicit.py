import math
import numpy as np
import matplotlib.pyplot as plt

for (i,j) in zip(range(1,5),[ 0.5 , 1 , 1.5 , 2 ]):

    Plot_list = []
    
    with open('graphes2.txt', 'r') as f:
        
        lines = f.readlines()
        
        x_numerique_explicite = [float(line.split()[0]) for line in lines]
        y_numerique_explicite = [float(line.split()[i]) for line in lines]
        
        X_numerique_explicite = np.array(x_numerique_explicite)
        Y_numerique_explicite = np.array(y_numerique_explicite)
    
    with open('graphes3.txt', 'r') as g:
        
        lines = g.readlines()
        
        x_numerique_implicite = [float(line.split()[0]) for line in lines]
        y_numerique_implicite = [float(line.split()[i]) for line in lines]
        
        X_numerique_implicite = np.array(x_numerique_implicite)
        Y_numerique_implicite = np.array(y_numerique_implicite)
    
    Plot_list.append(plt.plot(abs(X_numerique_implicite), abs(Y_numerique_implicite - Y_numerique_explicite), label="t = " + str(j) + "π"))
 
for k in Plot_list:
 
    plt.plot()
    plt.grid()
    plt.axis([0, 10 * math.pi, -0.05, 0.05])
    plt.title('Graphe différence solutions Numérique Implicite et Numérique Explicite')
    plt.xlabel("position x (en m)")
    plt.ylabel("pression P (en Pa)")
    plt.legend(loc = 4)    
    plt.show()