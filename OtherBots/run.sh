if [ ${file: -3} == ".py" ]
then
	$1
else
	./$1
fi