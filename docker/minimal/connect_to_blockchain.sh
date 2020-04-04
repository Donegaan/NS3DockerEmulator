# Address is ip:port, ip address seems to be the same everytime new container is created
multichaind DockerChain@10.12.0.1:7447 -daemon

multichain-cli DockerChain

create stream stream1 '{"restrict":"write"}'

quit

# cat create_stream.py
# python3 create_stream.py # Will run if producer