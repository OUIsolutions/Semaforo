# Semaforo
An Entity locker
Semaforo i'ts an entity locker , projected to lock folders/files and all types of entitys 

Usage: 
in these following example we are locking file "a.txt" for at max 60 seconds, waiting 10 senconds max
 to get the ownership of file 
```shell
./semaforo a.txt -timeout 60  -wait 10
```
Flags:

| Name    | Default    | What                                                        |
|---------|------------|-------------------------------------------------------------|
| timeout | 60         | max time that current process can be with the ownership     |
| wait    | 60         | max time for waiting the ownershil (after returns an error) |
| storage | .lock.json | the entity locks json  to control what its been locked      |



Possible returns:

Flags:

| Number | What                                                             |
|--------|------------------------------------------------------------------|
| 0      | means you get the ownership of entity                            |
| 1      | means its reach the wait timeout and its locked by other process |
| 2      | means the .lock.json its not well formatted                      |

