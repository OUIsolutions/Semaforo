from os import system
from multiprocessing import Process, Queue

def my_function(x):
 
    system('./a.out --action lock --entity a.txt')
    with open('teste.txt','r') as arq:
        result = arq.read()


    with open('teste.txt','w') as arq:
        arq.write(result + x + "\n")
    system('./a.out --action unlock --entity a.txt')



with open('teste.txt','w') as arq:
    arq.write('')
    
for x in range(0,50):
    p = Process(target=my_function, args=(f'{x}',))
    p.start()