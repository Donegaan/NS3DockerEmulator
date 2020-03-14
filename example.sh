#!/usr/bin/env bash

COUNTER=0
MAIN_SCRIPT="main.new.py"

NODES=5 # Number of nodes
TIMEEMU=1800 # Time of the emulation in seconds
SIZE=300 # Size of the network, 300m x 300m
SPEED=5 # Speed in m/s
PAUSE=0 # Pause time of the nodes in seconds

export NS3_HOME=~/ns-3-allinone/ns-3-dev

# We create everything
python3 ${MAIN_SCRIPT} -n ${NODES} -t ${TIMEEMU} -s ${SIZE} -ns ${SPEED} -np ${PAUSE} create
# We run the NS3 simulation
python3 ${MAIN_SCRIPT} -n ${NODES} -t ${TIMEEMU} -s ${SIZE} -ns ${SPEED} -np ${PAUSE} ns3

while [  $COUNTER -lt 1 ]; do

    DATENOW=$(date +"%y_%m_%d_%H_%M")

    # Making a backup from the last iteration's logs
    echo "---------------------------"
    echo ${DATENOW}
    echo "---------------------------"
    mkdir -p var/archive/${DATENOW}
    mv var/log/* var/archive/${DATENOW}/

    # Run the emulation
    python3 ${MAIN_SCRIPT} -n ${NODES} -t ${TIMEEMU} -s ${SIZE} -ns ${SPEED} -np ${PAUSE} emulation

    ####################################################################
    # Run a custom script to gather data from the logs for further analysis
    # python3 statscollector2.py bla bla bla
    ####################################################################

        let COUNTER=COUNTER+1
done

# We destroy everything cause we don't need it anymore
python3 ${MAIN_SCRIPT} -n ${NODES} -t ${TIMEEMU} -s ${SIZE} -ns ${SPEED} -np ${PAUSE} destroy