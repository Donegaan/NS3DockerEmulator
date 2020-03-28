# Script to reset emulator environment. Delete and re-create docker images and start the example script

docker stop $(docker ps -a -q) && docker rm $(docker ps -a -q)
docker rmi $(docker images -a -q)
sudo python3 main.new.py -nprod 1 -ncon 4 -t 300 -s 300 -ns 5 -np 0 create_docker
sudo ./example.sh