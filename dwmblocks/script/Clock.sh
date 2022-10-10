#!/bin/sh

case $BLOCK_BUTTON in
	1) notify-send "月份信息" "$(cal --color=always | sed "s/..7m/<b><span color=\"red\">/;s/..27m/<\/span><\/b>/")" && notify-send "$(calcurse -D ~/.config/calcurse -d3)" ;;
	2) setsid -f "$TERMINAL" -e calcurse ;;
	3) notify-send "日期模块" "\- 查看月份信息
- 左键点击显示日历和未来三天的计划
- 中键点击打开calcurse(如果已安装)" ;;
	6) "$TERMINAL" -e "$EDITOR" "$0" ;;
esac

LOCALTIME=$(date +" %m-%d(%a)%H:%M")
printf "${LOCALTIME}"

