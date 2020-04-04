# Address is ip:port, ip address seems to be the same everytime new container is created
multichaind DockerChain@10.12.0.1:7447 -daemon

python3 create_stream.py # Will run if producer