#!/bin/bash

test -d pack || mkdir -p pack
test -d pack/libs || mkdir -p pack/libs

SEETA_BIN_LIB="$(find '.' -type f -exec file -i '{}' \; | egrep 'x-executable; charset=binary|x-sharedlib; charset=binary' | awk -F ': ' '{print $1}')"
echo "$SEETA_BIN_LIB" > bin_lib.txt
SEETA_BIN="$(find '.' -type f -exec file -i '{}' \; | grep 'x-executable; charset=binary' | awk -F ': ' '{print $1}')"
echo "$SEETA_BIN" > bin.txt

cp /lib64/ld-linux-x86-64.so.2 pack/libs

for i in `cat bin_lib.txt`; do
	deps="$(ldd "$i" | awk -F ' ' '{print $3}'|grep '.so')"
	for j in $deps; do
		cp -n $j pack/libs
	done
done

cp "$1" pack
cp loggercfg.cfg pack 
cp conf.json pack
rm bin_lib.txt bin.txt
tar czf "$1".tar.gz pack
rm pack -rf
