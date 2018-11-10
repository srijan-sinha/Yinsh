cd Yinsh-AI/
gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 ./run.sh; exit" | gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 ./debu.sh -mode GUI; exit"| python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log
