#!/bin/sh

# This file basically destroy the network bridge and TAP interface
# created by the singleSetup.sh script

if [ -z "$1" ]
  then
    echo "No name supplied"
    exit 1
fi

NAME=$1

# ifconfig br-$NAME down

sudo ip link set dev br-$NAME down

sudo brctl delif br-$NAME tap-$NAME

sudo brctl delbr br-$NAME

# ifconfig tap-$NAME down
sudo ip link set dev tap-$NAME down

sudo ip link delete tap-$NAME

sudo tunctl -d tap-$NAME