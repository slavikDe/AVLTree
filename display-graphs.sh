#!/bin/bash

function cleanup() {
    exit 1
}

trap cleanup SIGINT

for i in $(ls graphs | grep -E "^graph[0-9]+\.dot$" | sed -E 's/graph([0-9]+)\.dot/\1 &/' | sort -n -k1,1 | sed -E 's/[0-9]+ //'
) ; do
	dot -Tdot graphs/$i | gvpr -c -f binary-tree-format.gvpr | neato -n -Tpng > graphs/graph.png
	display graphs/graph.png
done;
