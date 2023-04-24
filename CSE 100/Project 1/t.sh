#!/bin/bash

testprog () {
    echo $testfile "- test"
    ./compress $testfile $compfile 
    ./uncompress $compfile $origfile
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

testfile="dna.txt"
compfile="dna.cmp"
origfile="dna.org"
testprog
echo ""
testfile="binary"
compfile="binary.cmp"
origfile="binary.org"
testprog
echo ""
testfile="alphaext.txt"
compfile="alphaext.cmp"
origfile="alphaext.org"
testprog
echo ""
testfile="empty.txt"
compfile="empty.cmp"
origfile="empty.org"
testprog
echo ""
testfile="zero"
compfile="zero.cmp"
origfile="zero.org"
testprog
