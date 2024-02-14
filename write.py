from os import system
from multiprocessing import Process
from os import system
import requests
import json
from os import makedirs
from os.path import isfile
from os.path import isdir
from os import listdir
def generate_list():

    while True:    

        with open('new_teste.json','r') as arq:
            itens = json.loads(arq.read())
        for e in itens:
            filename = f'listage/{e}.txt'
            system(f'./a.out -w 0 --action lock --entity {filename}')
            with open(filename,'w') as arq:
                arq.write(e)
            system(f'./a.out --action unlock --entity {filename}')

        
def cap_url(worker_id):
    while True:
        itens = listdir('listage')
        for e in itens:
            current_path = f'listage/{e}'
            system(f'./a.out -w 0 --action lock --entity {current_path}')
            with open(current_path,'r') as arq:
                url = arq.read()
            content = requests.get(url)
            formated_url = url.replace('/','').replace(' ','')
            with open(f'result/{formated_url}','w') as arq:
                arq.write(content.text)
            system(f'./a.out -w 0 --action unlock --entity {current_path}')

        

if not isfile('new_teste.json'):
    with open('new_teste.json','w') as arq:
        arq.write('[]')

makedirs('listage',exist_ok=True)

makedirs('result',exist_ok=True)

initial = Process(target=generate_list)
initial.start()
for i in range(0,2):
    p = Process(target= cap_url)
    p.start()
    