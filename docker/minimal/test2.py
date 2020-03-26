import mcrpc

rpcuser = 'multichainrpc'
rpcpasswd = 'this-is-insecure-change-it-123'
rpchost = 'localhost'
rpcport = '8000'

client = c = mcrpc.RpcClient(rpchost, rpcport, rpcuser, rpcpasswd)

print(client.getinfo())
