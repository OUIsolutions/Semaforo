from os import system
from multiprocessing import Process
from os import system
import requests
import json
from os import makedirs
from os.path import isfile
from os.path import isdir
from os import remove
from os import listdir
def generate_list():

    while True:    

        with open('new_teste.json','r') as arq:
            itens = json.loads(arq.read())
        for url in itens:
            formated_url = url.replace('/','').replace(' ','').replace(':','')

            filename = f'listage/{formated_url}.txt'
            system(f'./a.out  --action lock --entity {filename}')
       
            with open(filename,'w') as arq:
                arq.write(url)

            system(f'./a.out --action unlock --entity {filename}')
        with open('new_teste.json','w') as arq:
            arq.write('[]')

        
def cap_url():
    while True:
        itens = listdir('listage')
        for e in itens:
            current_path = f'listage/{e}'
            lock_result =system(f'./a.out --wait 0 --action lock --entity {current_path}')
            if lock_result != 0:
                continue

            with open(current_path,'r') as arq:
                url = arq.read()
            content = requests.get(url)
            formated_url = url.replace('/','').replace(' ','')
            with open(f'result/{formated_url}','w') as arq:
                arq.write(content.text)
            
            
            system(f'./a.out  --action unlock --entity {current_path}')

        

if not isfile('new_teste.json'):
    with open('new_teste.json','w') as arq:
        arq.write('[]')

makedirs('listage',exist_ok=True)

makedirs('result',exist_ok=True)

generate_list()
