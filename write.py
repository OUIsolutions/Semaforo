from multiprocessing import Process
import requests
import json
from os import makedirs, remove
from os.path import isfile, isdir
from os import system, listdir
from json import JSONDecodeError

FILE_ITS_ALREADY_LOCKED_CODE = 1
INVALID_STORAGE_FILE = 3
        

class FIleIsAlreadyLocked (Exception):
    def __init__(self,filename) -> None:
        self.message = f'file:{filename} its already locked'
        super().__init__(self.message)
        self.filenmae = filename
        
class InvalidStorageFile (Exception):
    def __init__(self,filename) -> None:
        self.message = f'file:{filename} its not well formated'
        super().__init__(self.message)
        self.filenmae = filename
        

class FileLock:
    def __init__(self,filename ,wait_time=60,timeout=60,storage_point='lock.json'):
        self.filename = filename
        self.wait_time = wait_time
        self.timeout = timeout
        self.storage_point = storage_point

    def __enter__(self):
        result = system(f'./a.out  --quiet true --action lock --entity {self.filename} --wait {self.wait_time} --timeout {self.timeout}')

        if result == FILE_ITS_ALREADY_LOCKED_CODE:
            raise FIleIsAlreadyLocked(self.filename)
        
        if result == INVALID_STORAGE_FILE:
            raise InvalidStorageFile(self.storage_point)
        
        if result != 0:
            print(result)

            raise Exception('unexpected error')
                
        
    
    def __exit__(self, exc_type, exc_value, traceback):
        result = system(f'./a.out  --quiet true  --action unlock --entity {self.filename}')
                
        if result == InvalidStorageFile:
            raise InvalidStorageFile(self.storage_point)
        
        if result != 0:
            print(result)
            raise Exception('unexpected error')
                


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
            except FIleIsAlreadyLocked as e:
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