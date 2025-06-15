#! /bin/zsh

t=100
n=100
k=3
i=0

while [ $i -le 10 ]
do
	bin/g1 $t $n $k > "res/answer.txt"
	bin/g2 $t $n $k < "res/answer.txt" > "res/input.txt"
	bin/s2 < "res/input.txt" > "res/output.txt"
	cat "res/answer.txt" "res/output.txt" | bin/v $t $n $k

	((i++))
done
