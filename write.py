from multiprocessing import Process
import requests
import json
from os import makedirs, remove
from os.path import isfile, isdir
from os import system, listdir
from json import JSONDecodeError


class FileLockExeption (Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)
        


class FileLock:
    def __init__(self,filename ,wait_time=60,timeout=60):
        self.filename = filename
        self.wait_time = wait_time
        self.timeout = timeout

    def __enter__(self):
        result = system(f'./a.out  --quiet true --action lock --entity {self.filename} --wait {self.wait_time} --timeout {self.timeout}')
        if result != 0:
            raise FileLockExeption(f'file {self.filename} its already locked')
    
    def __exit__(self, exc_type, exc_value, traceback):
        system(f'./a.out  --quiet true  --action unlock --entity {self.filename}')
        


def generate_list():
    while True:
        with open('new_teste.json', 'r') as arq:
            try:
                itens = json.loads(arq.read())
            except JSONDecodeError:
                continue
        if not itens:
            continue

        for url in itens:
            formated_url = url.replace('/', '').replace(' ', '').replace(':', '')
            filename = f'listage/{formated_url}.txt'

            with FileLock(filename):
                with open(filename, 'w') as arq:
                    arq.write(url)

            with open('new_teste.json', 'w') as arq:
                arq.write('[]')


def cap_url():
    while True:
        itens = listdir('listage')
        for e in itens:
            current_path = f'listage/{e}'

            try:
                with FileLock(current_path,wait_time=0):
                    if not isfile(current_path):
                        continue

                    with open(current_path, 'r') as arq:
                        url = arq.read()

                    content = requests.get(url)
                    formated_url = url.replace('/', '').replace(' ', '')
                    with open(f'result/{formated_url}', 'w') as arq:
                        arq.write(content.text)

                    remove(current_path)
            except FileLockExeption as e:
                continue


if not isfile('new_teste.json'):
    with open('new_teste.json', 'w') as arq:
        arq.write('[]')

makedirs('listage', exist_ok=True)
makedirs('result', exist_ok=True)

initial = Process(target=generate_list)
initial.start()

for i in range(0, 10):
    p = Process(target=cap_url)
    p.start()