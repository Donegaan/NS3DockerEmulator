from Savoir import Savoir
rpcuser = 'multichainrpc'
rpcpasswd = 'this-is-insecure-change-it-123'
rpchost = 'localhost'
rpcport = '8000'
chainname = 'DockerChain'

api = Savoir(rpcuser, rpcpasswd, rpchost, rpcport, chainname)
print(api.getinfo())
