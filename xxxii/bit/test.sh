function success
{
    printf "\033[F\033[32msuccess! ($I)\n\033[39m"
}

function failure
{
    printf "\033[F\033[31mfailure! ($I)\n\033[39m"
}

function run
{
    bin/g $N $M $K $RANDOM > res/i.txt &&
    # bin/s1 < res/i.txt > res/o1.txt &&
    # bin/s2 < res/i.txt > res/o2.txt &&
    bin/s3 < res/i.txt > res/o3.txt &&
    # cmp -s res/o3.txt res/o3.txt &&
    true
}

I=0
N=3000
M=3000
K=100000

make
echo

while [ $I -lt 100000 ]
do
    I=$(($I + 1))
    if run
    then
        success
    else
        failure
        break
    fi
done
