from os import system
from multiprocessing import Process, Queue
from os import system
import requests
import json
from os import makedirs
from os.path import isfile

def cap_url(worker_id):
    while True:
        system('./a.out --action lock --entity new_teste.json')
        with open('new_teste.json','r') as arq:
            result = json.loads(arq.read())

        for url in result:
            
            retorno = system(f'./a.out -w 0 --action lock --entity {url}')
            
            if retorno == 0:
                system('./a.out --action unlock --entity new_teste.json')

                response = requests.get(url)
                print(f"worker: {worker_id} Url: {url} Status: {response.status_code}")
                filename = f'result/{url.replace(" ", "").replace("/", "")}.json';

                with open(filename,'w') as arq:
                    arq.write(response.text)

                system('./a.out --action lock --entity new_teste.json')

                #removendo a url
                with open('new_teste.json','r') as arq:
                    result = json.load(arq)
                    result.remove(url)

                with open('new_teste.json','w') as arq:
                    json.dump(result, arq)



                system(f'./a.out -w 0 --action unlock --entity {url}')
     

        
        system('./a.out --action unlock --entity new_teste.json')
        

if not isfile('new_teste.json'):
    with open('new_teste.json','w') as arq:
        arq.write('[]')

makedirs('result',exist_ok=True)
for x in range(0,2):
    p = Process(target=cap_url, args=(str(x),))
    p.start()