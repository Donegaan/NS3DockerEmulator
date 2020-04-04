#!/usr/bin/python

import mcrpc
import time
import sys

rpcuser = 'multichainrpc'
rpcpasswd = 'this-is-insecure-change-it-123'
rpchost = '10.12.0.1'
rpcport = '8000'
stream_name = 'stream1'


def main(argv):
    client = c = mcrpc.RpcClient(rpchost, rpcport, rpcuser, rpcpasswd)

    client.subscribe(stream_name)

    # Request stream objects
    client.liststreamkeyitems(stream_name, argv[0])


if __name__ == "__main__":
    main(sys.argv[1:])