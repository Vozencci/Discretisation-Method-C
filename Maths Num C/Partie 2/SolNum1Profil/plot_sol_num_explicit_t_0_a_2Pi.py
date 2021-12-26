import math
import matplotlib.pyplot as plt

Plot_list = []
    
with open('graphescustomexplicit.txt', 'r') as f:
        
    lines = f.readlines()
        
    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
    
    Plot_list.append(plt.plot(x,y,label="t = t_custom"))
 
for k in Plot_list:
 
    plt.plot()
    plt.grid()
    plt.axis([0, 10 * math.pi, -1, 1])
    plt.title('Solution Numerique Explicite de t variant entre 0 à 2Pi')
    plt.xlabel("position x (en m)")
    plt.ylabel("pression P (en Pa)")
    plt.legend(loc = 4)    
    plt.show()