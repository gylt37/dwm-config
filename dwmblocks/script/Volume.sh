#!/bin/sh

case $BLOCK_BUTTON in
	1) setsid -f "alacritty" -e pulsemixer;;
	2) pamixer -t ;;
    3) setsid -f "$TERMINAL" -e ncmpcpp ;;
	4) pamixer --allow-boost -i 5 ;;
	5) pamixer --allow-boost -d 5 ;;
	6) "$TERMINAL" -e "$EDITOR" "$0" ;;
	7) light -A 5 ; notify-send 亮度$(light);;
	8) light -U 5 ; notify-send 亮度$(light);
esac

vol=$(pamixer --get-volume)

mute=$(pamixer --get-mute)

if  [ $mute == "true" ]; then
    icon="󰖁"
elif [ "$vol" -gt "100"  ]; then
    icon=""
elif [ "$vol" -gt "70" ]; then
	icon="󰕾"
elif [ "$vol" -lt "30" ]; then
	icon=""
else
	icon=""
fi

printf "$icon:$vol"
