import mcrpc

rpcuser = 'multichainrpc'
rpcpasswd = 'this-is-insecure-change-it-123'
rpchost = '10.12.0.1'
rpcport = '8000'
stream_name = 'stream1'

client = c = mcrpc.RpcClient(rpchost, rpcport, rpcuser, rpcpasswd)

client.create('stream', stream_name, True)

client.subscribe(stream_name)

client.publish(stream_name, 'key1',
               {"json": {"name": "Jane Smith", "city": "Paris"}})

client.liststreamitems(stream_name)
