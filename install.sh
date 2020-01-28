# source ~/.bashrc

# python $BAKE_HOME/bake.py check
# python $BAKE_HOME/bake.py configure -e ns-3.26
# python $BAKE_HOME/bake.py download
# python $BAKE_HOME/bake.py build

echo -e "\n\n Verifying Ns3  ... \n"
cd ns-3-dev
./waf

echo -e "\n\n Recompoling NS3 in optimized mode  ... \n"
./waf distclean
./waf -d optimized configure --disable-examples --disable-tests --disable-python --enable-static --no-task-lines
./waf

echo -e "\n\n Running first Ns3 example  ... \n"
cp examples/tutorial/first.cc scratch/
./waf
./waf --run scratch/first
cd

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