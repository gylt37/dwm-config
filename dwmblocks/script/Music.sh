#!/bin/sh
paused=$(mpc | grep paused | wc -l)

filter() {
if [ $paused -eq 0 ] ; then
     mpc -f %title%
fi
}

case $BLOCK_BUTTON in
	1) setsid -f "$TERMINAL" -e ncmpcpp ;;
	2) mpc status ;mpc toggle ;;
	3) notify-send "🎵 音乐模块" "\- 显示正在播放的音乐.
- 左键点击打开音乐列表.
- 鼠标中键暂停/播放音乐.
- 鼠标滚轮切换音乐.";;
	4) mpc prev   ;;
	5) mpc next   ;;
	6) "$TERMINAL" -e "$EDITOR" "$0" ;;
	*) filter ;;
esac
