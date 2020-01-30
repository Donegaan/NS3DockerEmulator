ifconfig br-left down
ifconfig br-right down
sudo brctl delif br-left tap-left
sudo brctl delif br-right tap-right
sudo brctl delbr br-left
sudo brctl delbr br-right
ifconfig tap-left down
ifconfig tap-right down
tunctl -d tap-left
tunctl -d tap-right
