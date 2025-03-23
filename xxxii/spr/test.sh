#!/bin/sh

I=0
N=10
MAX_A=20
EQUAL=0

function run
{
    bin/g $N $MAX_A $EQUAL $RANDOM > res/i.txt &&
    bin/s3 < res/i.txt > res/o.txt &&
    cat res/i.txt res/o.txt | bin/v &&
    true
}

make
echo

while [ $I -lt 1000 ]
do
    I=$(($I + 1))
    if run
    then
        printf "\033[F\033[32msuccess! ($I)\n"
    else
        printf "\033[F\033[31mfailure! ($I)\n"
        break
    fi
done

printf "\033[39m"
