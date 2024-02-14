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


def cap_url():
    while True:

        with open('new_teste.json','r') as arq:
            itens = json.loads(arq.read())

        if not itens:
            continue

        for url in itens:
            formated_url = url.replace('/','').replace(' ','').replace(':','')
 
            content = requests.get(url)
            formated_url = url.replace('/','').replace(' ','')
            with open(f'result/{formated_url}','w') as arq:
                arq.write(content.text)
            

        with open('new_teste.json','w') as arq:
            arq.write('[]')
        

if not isfile('new_teste.json'):
    with open('new_teste.json','w') as arq:
        arq.write('[]')

makedirs('listage',exist_ok=True)

makedirs('result',exist_ok=True)

cap_url()