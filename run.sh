#!/bin/sh
gcc adsb_R3.c -o run_R3 -O2 -lm
for dirname in all2/Model1/*;
do
    # echo run ${dirname}
    # echo correct answer
    # cat ${dirname}/answer
    # echo my answer
    ./run_R3 ${dirname}/idata ${dirname}/odata ${dirname}/answer
    # echo -e "\n\n\n"
done

for dirname in all2/Model2/*;
do
    # echo run ${dirname}
    # echo correct answer
    # cat ${dirname}/answer
    # echo my answer
    ./run_R3 ${dirname}/idata ${dirname}/odata ${dirname}/answer
    # echo -e "\n\n\n"
done