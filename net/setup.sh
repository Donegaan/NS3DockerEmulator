#!/bin/sh
sudo brctl addbr br-left
sudo brctl addbr br-right
sudo tunctl -t tap-left
sudo tunctl -t tap-right
sudo ifconfig tap-left 0.0.0.0 promisc up
sudo ifconfig tap-right 0.0.0.0 promisc up
sudo brctl addif br-left tap-left
sudo ifconfig br-left up
sudo brctl addif br-right tap-right
sudo ifconfig br-right up
pushd /proc/sys/net/bridge
for f in bridge-nf-*; do echo 0 > $f; done
popd
