cd Yinsh-AI/
# gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 ./run.sh; bash" | gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 RandomPlayer.py -mode GUI; bash"| python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log
# gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 ./run.sh; bash" | gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 ./run1.sh -mode GUI; bash"| python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log
./run.sh