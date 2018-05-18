#!/bin/bash

if [ $# != 1 ]
then echo "./compile_scenario.sh #scenario"
else
	clang++ main.cpp --std=c++11 -DS$1 -o unique_ptr_s$1
fi
