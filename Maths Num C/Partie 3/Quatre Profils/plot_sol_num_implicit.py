import math
import matplotlib.pyplot as plt

for (i,j) in zip(range(1,5),[ 0.5 , 1 , 1.5 , 2 ]):

    Plot_list = []
    
    with open('graphes3.txt', 'r') as f:
        
        lines = f.readlines()
        
        x = [float(line.split()[0]) for line in lines]
        y = [float(line.split()[i]) for line in lines]
    
    Plot_list.append(plt.plot(x,y,label="t = " + str(j) + "π"))
 
for k in Plot_list:
 
    plt.plot()
    plt.grid()
    plt.axis([0, 10 * math.pi, -1, 1])
    plt.title('Solution Numérique Implicite de la pression accoustique')
    plt.xlabel("position x (en m)")
    plt.ylabel("pression P (en Pa)")
    plt.legend(loc = 4)    
    plt.show()