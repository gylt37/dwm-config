#/bin/sh

n ()
{
    export NNN_PLUG='z:autojump;n:bulknew;m:chksum;x:chmod;d:diffs;f:finder;c:fzcd;k:kdeconnect;b:nbak;o:openall;t:preview-tui;e:suedit;r:x2sel;s:xdgdefault'
    export NNN_TMPFILE="${XDG_CONFIG_HOME:-$HOME/.config}/nnn/.lastd"
    \nnn -axd "$@"
    if [ -f "$NNN_TMPFILE" ]; then
            . "$NNN_TMPFILE"
            rm -f "$NNN_TMPFILE" > /dev/null
    fi
}
n
