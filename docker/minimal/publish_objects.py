#!/usr/bin/python

import mcrpc
import time
import sys

rpcuser = 'multichainrpc'
rpcpasswd = 'this-is-insecure-change-it-123'
rpchost = '10.12.0.2'
rpcport = '8000'
stream_name = 'stream1'


def main(argv):

    client = c = mcrpc.RpcClient(rpchost, rpcport, rpcuser, rpcpasswd)

    client.publish(stream_name, argv[0], {"json": {"message": argv[1]}})


if __name__ == "__main__":
    main(sys.argv[1:])
