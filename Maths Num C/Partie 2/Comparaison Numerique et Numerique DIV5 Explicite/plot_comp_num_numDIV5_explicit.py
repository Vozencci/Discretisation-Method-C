import math
import numpy as np
import matplotlib.pyplot as plt

for (i,j) in zip(range(1,5),[ 0.5 , 1 , 1.5 , 2 ]):

    Plot_list = []
    
    with open('graphes2.txt', 'r') as f:
        
        lines = f.readlines()
        
        x_numerique = [float(line.split()[0]) for line in lines]
        y_numerique = [float(line.split()[i]) for line in lines]
        
        X_numerique = np.array(x_numerique)
        Y_numerique = np.array(y_numerique)
    
    with open('graphes2div5.txt', 'r') as g:
        
        lines = g.readlines()
        
        x_numerique_div5 = [float(line.split()[0]) for line in lines]
        y_numerique_div5 = [float(line.split()[i]) for line in lines]
        
        X_numerique_div5 = np.array(x_numerique_div5)
        Y_numerique_div5 = np.array(y_numerique_div5)
    
    Plot_list.append(plt.plot(abs(X_numerique), abs(Y_numerique - Y_numerique_div5), label="t = " + str(j) + "π"))
 
for k in Plot_list:
 
    plt.plot()
    plt.grid()
    plt.axis([0, 10 * math.pi, 0, 0.015])
    plt.title('Graphe différence solutions explicites Numérique et Numérique avec Δt/5')
    plt.xlabel("position x (en m)")
    plt.ylabel("pression P (en Pa)")
    plt.legend(loc = 4)
    plt.show()