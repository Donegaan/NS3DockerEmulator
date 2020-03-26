apt-get update
apt-get upgrade -q -y
apt-get dist-upgrade -q -y
apt-get install -q -y wget curl python
apt-get clean
rm -rf /var/lib/apt/lists/*
wget -nv https://www.multichain.com/download/multichain-2.0.5.tar.gz
tar -xvzf multichain-2.0.5.tar.gz
cd multichain-2.0.5
mv multichaind multichain-cli multichain-util /usr/local/bin
curl https://bootstrap.pypa.io/get-pip.py | python
pip install dump-env -q
mkdir /root/.multichain
rm -rf /tmp/multichain-2.0.5

