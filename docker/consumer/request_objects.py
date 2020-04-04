import mcrpc
import time

rpcuser = 'multichainrpc'
rpcpasswd = 'this-is-insecure-change-it-123'
rpchost = '10.12.0.1'
rpcport = '8000'
stream_name = 'stream1'

client = c = mcrpc.RpcClient(rpchost, rpcport, rpcuser, rpcpasswd)

client.subscribe(stream_name)

# Request stream objects
client.liststreamkeyitems()

for x in range(150):
    print(client.liststreamkeyitems(stream_name, 'key'+str(x)))
    time.sleep(2)
