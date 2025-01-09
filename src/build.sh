#!/bin/bash

#把所有.cpp檔封裝成.o檔
for file in *.cpp; do
    g++ "$file" -c -std=c++14 -I include
done

#生成執行檔
g++ *.o -o main -std=c++14 -I include -L lib -lraylib

#清理.o檔
rm *.o