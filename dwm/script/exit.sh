xmenu <<EOF | sh &
退出			pkill -15 dwm
关机			systemctl poweroff
重启			systemctl reboot
睡眠			systemctl suspend
休眠			systemctl hibernate
EOF
