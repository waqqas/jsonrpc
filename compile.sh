#!/usr/bin/env bash
java -Xmx500M -cp "/usr/local/lib/antlr-4.9-complete.jar:$CLASSPATH" org.antlr.v4.Tool -Dlanguage=Cpp JsonRpc.g4 -visitor -no-listener -package jsonrpc -o src/
g++ *.cpp src/*.cpp -I src/ -I/usr/local/include/antlr4-runtime -L /usr/local/lib -lantlr4-runtime -std=c++17 -o main

