#!/bin/bash

testmem () {
    echo $testfile "- test"
    valgrind $options ./compress $testfile $compfile 
    valgrind $options ./uncompress $compfile $origfile
    diff -q $origfile $testfile
    fs1=$(wc -c $testfile | awk '{print $1}')
    fs2=$(wc -c $compfile | awk '{print $1}')
    fs3=$(wc -c $origfile | awk '{print $1}')
    echo "original: "
    printf $fs1
    echo ""
    echo "compressed: "
    printf $fs2
    echo ""
    echo "decompressed: "
    printf $fs3
    echo ""
    rm $compfile
    rm $origfile
}

#options="--leak-check=full --track-origins=yes --show-leak-kinds=all"
options="--leak-check=yes --track-origins=yes"
testfile="dna.txt"
compfile="dna.cmp"
origfile="dna.org"
testmem
echo ""
testfile="binary"
compfile="binary.cmp"
origfile="binary.org"
testmem
echo ""
testfile="alphaext.txt"
compfile="alphaext.cmp"
origfile="alphaext.org"
testmem
echo ""
testfile="empty.txt"
compfile="empty.cmp"
origfile="empty.org"
testmem
echo ""
testfile="zero"
compfile="zero.cmp"
origfile="zero.org"
testmem
