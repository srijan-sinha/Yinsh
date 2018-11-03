cd Yinsh-AI/
for i in {1..665}
do
  	echo "Welcome $i times"
  	# ./io 1
  	./io 2 $i
	gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 ./run1.sh; exit; bash" | gnome-terminal -x sh -c "python client.py 0.0.0.0 10000 ./run_bot2.sh > output.txt; exit; bash"| python server.py 10000 -n 5 -NC 2 -TL 150 -LOG server.log
	sleep 10
	./check
done
