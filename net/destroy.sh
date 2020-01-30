sudo ifconfig br-left down
sudo ifconfig br-right down
sudo brctl delif br-left tap-left
sudo brctl delif br-right tap-right
sudo brctl delbr br-left
sudo brctl delbr br-right
sudo ifconfig tap-left down
sudo ifconfig tap-right down
sudo tunctl -d tap-left
sudo tunctl -d tap-right
