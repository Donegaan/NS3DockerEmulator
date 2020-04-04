#!/usr/bin/python

import mcrpc
import time
import sys

rpcuser = 'multichainrpc'
rpcpasswd = 'this-is-insecure-change-it-123'
rpchost = '172.17.0.2'
rpcport = '8000'
stream_name = 'stream1'

client = c = mcrpc.RpcClient(rpchost, rpcport, rpcuser, rpcpasswd)

# Will only create one stream with the same name so can leave it in if multiple producers
# There will be errors, fine if it doesn't stop emulation execution
client.create('stream', stream_name, True)

client.subscribe(stream_name)
