#/bin/sh
options="\
       -kb-cancel "Alt+Escape,Escape" \
       -kb-accept-entry "!Alt-Tab,Return,!Alt-l,!Alt-h"\
       -kb-row-down "Alt+Tab,Alt+l,Alt+ISO_Left_Tab" \
       -kb-row-up "Alt+Shift+Tab,Alt+h,Alt+n""

rofi -show window $options