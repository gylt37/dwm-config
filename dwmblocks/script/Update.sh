#!/bin/sh

case $BLOCK_BUTTON in
	1) setsid -f "$TERMINAL" -e "/home/gylt/.config/dwm/update.sh" ;;
	2) notify-send "$(/usr/bin/pacman -Qu)" ;;
	3) setsid -f  "/bin/sh" -c "~/.config/dwm/exit.sh";;
	6) "$TERMINAL" -e "$EDITOR" "$0" ;;
esac

number=$(pacman -Qu | grep -Fcv "[ignored]")

if  [ "$number" -eq "0" ]; then
    icon=""
else
    icon="遲"
    sate=":$number"
fi

printf "$icon$sate"
