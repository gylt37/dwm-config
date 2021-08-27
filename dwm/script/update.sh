#!/bin/sh

check(){
    sleep 5
    sudo pacman -Syy
    pkill -RTMIN+6 "${STATUSBAR:-dwmblocks}"
    number=$(pacman -Qu | grep -Fcv "[ignored]")
    if [ "$number" -eq "0" ]; then
        notify-send "📦 提示" "同步完毕. 没有可更新的软件包."
    else
        notify-send "🎁 提示" "有可用更新. 点击状态栏图标 (📦) 开始更新."
    fi
}

update(){
    printf "开始更新.\\n"
    yay -Syu
    pkill -RTMIN+6 "${STATUSBAR:-dwmblocks}"
    printf "\\n更新完毕.\\n按 <Enter> 退出窗口.\\n\\n"
    read -r
}

if [ "$1" == "--check" ]; then
    check
else
	update
fi



