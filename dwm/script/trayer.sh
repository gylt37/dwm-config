#!/bin/sh
killall trayer
if [ $? != 0 ]; then
	trayer  --width 10 --height 30  --align right --transparent true --monitor 1 --tint 0000000 --alpha 200
fi
