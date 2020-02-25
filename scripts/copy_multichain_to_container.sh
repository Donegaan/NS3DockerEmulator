# This copies the multichain executable files to a container and makes them executable
# This expects a container name
sudo </usr/local/bin/multichaind lxc-attach -n $1 -- bin/sh -c "/bin/cat > /usr/local/bin/multichaind"
sudo </usr/local/bin/multichain-cli lxc-attach -n $1 -- bin/sh -c "/bin/cat > /usr/local/bin/multichain-cli"
sudo </usr/local/bin/multichain-util lxc-attach -n $1 -- bin/sh -c "/bin/cat > /usr/local/bin/multichain-util"

# Make files executable
sudo lxc-execute -n $1 chmod +x /usr/local/bin/multichaind
sudo lxc-execute -n $1 chmod +x /usr/local/bin/multichain-cli
sudo lxc-execute -n $1 chmod +x /usr/local/bin/multichain-util
