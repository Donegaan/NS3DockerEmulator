#!/bin/bash

if [ -z "$CHAINNAME" ]; then
    CHAINNAME='DockerChain'
fi

printf "Starting blockchain"
multichaind $CHAINNAME -daemon