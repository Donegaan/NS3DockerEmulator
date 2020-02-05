#!/bin/bash

# This script install all the required packages for The NS3DockerEmulator  https://github.com/chepeftw/NS3DockerEmulator
# Ns3.30.1 and Docker 17.06
# To running , open Terminal and execute
# source install.sh

echo -e "\n\n Updating enviroment... \n"
sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y dist-upgrade

echo -e "\n\n Installing git ... \n"
sudo apt-get -y install git

echo -e "\n\n Installing Ns3 required packages ... \n"
sudo apt-get -y install gcc g++ python python-dev mercurial bzr gdb valgrind gsl-bin libgsl2 libgsl2:i386 flex bison tcpdump sqlite sqlite3 libsqlite3-dev libxml2 libxml2-dev libgtk2.0-0 libgtk2.0-dev uncrustify doxygen graphviz imagemagick python-pygraphviz python-kiwi python-pygoocanvas libgoocanvas-dev python-pygccxml cmake autoconf libc6-dev libc6-dev-i386 g++-multilib texlive texlive-extra-utils texlive-latex-extra texlive-font-utils texlive-lang-portuguese dvipng python-pygraphviz python-kiwi python-pygoocanvas libgoocanvas-dev ipython libboost-signals-dev libboost-filesystem-dev openmpi-bin openmpi-common openmpi-doc libopenmpi-dev qt4-dev-tools libqt4-dev unzip p7zip-full unrar-free cvs
sudo apt-get -y install python-pip
pip install pygccxml
pip install --upgrade pip
sudo -H pip install pygccxml --upgrade

echo -e "\n\n Setting Ns3 workspace ... \n"
cd
git clone https://gitlab.com/nsnam/ns-3-allinone.git
cd ns-3-allinone
./download.py

echo -e "\n\n Verifying Ns3  ... \n"
cd ns-3-dev

echo -e "\n\n Recompoling NS3 in optimized mode  ... \n"

./waf -d optimized configure --disable-examples --disable-tests --disable-python --enable-static --no-task-lines --enable-sudo
./waf

echo -e "\n\n Running first Ns3 example  ... \n"
cp examples/tutorial/first.cc scratch/
./waf
./waf --run scratch/first
cd ~

echo -e "\n\n Installing Docker required packages  ... \n"

sudo apt-get -y install apt-transport-https ca-certificates curl software-properties-common
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo apt-key fingerprint 0EBFCD88
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

service lxcfs stop
sudo apt-get -y remove lxc-common lxcfs lxd lxd-client

sudo apt-get -y update
sudo apt-get -y install docker-ce

echo -e "\n\n  Verifying  Docker  ... \n"
sudo docker run hello-world

echo -e "\n\n Installing Network Bridges  ... \n"

sudo apt install bridge-utils
sudo apt install uml-utilities