#!/bin/bash

files=( "fri26" "kroA100" "kroA200" "pcb442" "pr1002" "rat575" "rd100" "rd400" "si1032" "si535" )
pref=( "loc" "gen_o_0" "gen_o_1" "gen_i_0" "gen_i_1" )


for file in "${files[@]}"
do
	for pre in "${pref[@]}"
	do
		cat ./out/$file/$pre*$file*.txt >> ./out/$pre"_"$file.txt 
	done
done
