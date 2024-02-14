from multiprocessing import Process
import requests
import json
from os import makedirs, remove
from os.path import isfile, isdir
from os import system, listdir
from json import JSONDecodeError
from time import time
BASE_MUL = 256
FILE_ITS_ALREADY_LOCKED_CODE = 1 *BASE_MUL
INVALID_STORAGE_FILE = 3  *BASE_MUL
        

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
            raise Exception('Unexpected Error')
                
        
    
    def __exit__(self, exc_type, exc_value, traceback):
        result = system(f'./a.out  --quiet true  --action unlock --entity {self.filename}')
                
        if result == InvalidStorageFile:
            raise InvalidStorageFile(self.storage_point)
        
        if result != 0:
            raise Exception('Unexpected Error')
                
        
start = time()
with FileLock(f'a.txt'):
    pass 
duracao = time() - start
print(duracao)