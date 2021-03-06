#!/bin/sh

check(){
    sleep 5
    sudo pacman -Syy
    pkill -RTMIN+6 "${STATUSBAR:-dwmblocks}"
    number=$(pacman -Qu | grep -Fcv "[ignored]")
    if [ "$number" -eq "0" ]; then
        notify-send "ð¦ æç¤º" "åæ­¥å®æ¯. æ²¡æå¯æ´æ°çè½¯ä»¶å."
    else
        notify-send "ð æç¤º" "æå¯ç¨æ´æ°. ç¹å»ç¶ææ å¾æ  (ð¦) å¼å§æ´æ°."
    fi
}

update(){
    printf "å¼å§æ´æ°.\\n"
    yay -Syu
    pkill -RTMIN+6 "${STATUSBAR:-dwmblocks}"
    printf "\\næ´æ°å®æ¯.\\næ <Enter> éåºçªå£.\\n\\n"
    read -r
}

if [ "$1" == "--check" ]; then
    check
else
	update
fi



