#!/bin/bash

h_user="/home/est_posgrado_edgar.lopez/"
executable="TSP/TSP_run"

infiles=( "fri26.tsp" "kroA100.tsp" "rd100.tsp" "kroA200.tsp" "rd400.tsp" "pcb442.tsp" "si535.tsp" "rat575.tsp" "pr1002.tsp" "si1032.tsp" )
indir="TSP/instances/"
outdir="TSP/out/"

if test -f ./tasks; then
	echo "./tasks exists."
	rm ./tasks
fi

for file in "${infiles[@]}"
do
	for j in {1..30}
	do
		echo $h_user$executable $j $h_user$indir$file $h_user$outdir"loc_$j$file.txt" localsearch >> tasks
		echo $h_user$executable $j $h_user$indir$file $h_user$outdir"gen_o_0_$j$file.txt" genetic ord 0 >> tasks
		echo $h_user$executable $j $h_user$indir$file $h_user$outdir"gen_o_1_$j$file.txt" genetic ord 1 >> tasks
		echo $h_user$executable $j $h_user$indir$file $h_user$outdir"gen_i_0_$j$file.txt" genetic inv 0 >> tasks
		echo $h_user$executable $j $h_user$indir$file $h_user$outdir"gen_i_1_$j$file.txt" genetic inv 1 >> tasks
	done
done
