#!/bin/sh
picom&
dunst&
copyq&
variety&
nm-applet&
redshift-gtk&
dwmblocks&
mpd&
lxsession&
kdeconnect-settings&
xbindkeys
/usr/local/share/dwm/update.sh --check&
xautolock -time 60 -locker "/usr/local/share/dwm/lock.sh | xset dpms force off " &
xset s 1800
