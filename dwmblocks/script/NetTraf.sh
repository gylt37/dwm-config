#!/bin/sh

case $BLOCK_BUTTON in
    1) nm-connection-editor ;;
    2) setsid -f "$TERMINAL" -e nmcli ;;
	6) "$TERMINAL" -e "$EDITOR" "$0" ;;
esac

update() {
    sum=0
    for arg; do
        read -r i < "$arg"
        sum=$(( sum + i ))
    done
    cache=${XDG_CACHE_HOME:-$HOME/.cache}/${1##*/}
    [ -f "$cache" ] && read -r old < "$cache" || old=0
    printf %d\\n "$sum" > "$cache"
    printf %d\\n $(( sum - old ))
}

RX=$(update /sys/class/net/[ew]*/statistics/rx_bytes)
TX=$(update /sys/class/net/[ew]*/statistics/tx_bytes)

if [[ $RX -lt 1000 ]];then
    RX=$(echo $RX | awk '{printf ("%3.fB", $1)}')
elif [[ $RX -gt 1048576 ]];then
    RX=$(echo $RX | awk '{printf ("%3.1fM", $1/1048576)}')
elif [[ $RX -gt 10240 ]];then
    RX=$(echo $RX | awk '{printf ("%3.fk", $1/1024)}')
else
    RX=$(echo $RX | awk '{printf ("%3.1fK", $1/1024)} ')
fi

if [[ $TX -lt 1000 ]];then
    TX=$(echo $TX | awk '{printf ("%3.fB", $1)}')
elif [[ $TX -gt 1048576 ]];then
    TX=$(echo $TX | awk '{printf ("%3.1fM", $1/1048576)}')
elif [[ $TX -gt 10240 ]];then
    TX=$(echo $TX | awk '{printf ("%3.fk", $1/1024)}')
else
    TX=$(echo $TX | awk '{printf ("%3.1fK", $1/1024) }')
fi

printf ":$TX :$RX"
