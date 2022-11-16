
case $BLOCK_BUTTON in
	3) $(notify-send 亮度 -h int:value:`light`);;
	4) light -A 5 $(notify-send 亮度 -h int:value:`light`);;
	5) light -U 5 $(notify-send 亮度 -h int:value:`light`);;
	6) "$TERMINAL" -e "$EDITOR" "$0" ;;
esac

for battery in /sys/class/power_supply/BAT?
do
	# Get its remaining capacity and charge status.
	capacity=$(cat "$battery"/capacity 2>/dev/null) || break
	status=$(sed "s/[Dd]ischarging//;s/[Nn]ot charging//;s/[Cc]harging//;s/[Uu]nknown//;s/[Ff]ull//" "$battery"/status)

	printf "%s:%s" "$status" "$capacity";
done | sed 's/ *$//'
