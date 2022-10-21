/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* 托盘相关 */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray       = 1;     /* 0 means no systray */

static const unsigned int snap     = 30;  /* 窗口吸附边缘像素 */
static const unsigned int borderpx = 3;   /* 窗口边框像素 */

static const unsigned int gappih = 10;  /* 内 水平间隙 */
static const unsigned int gappiv = 10;  /* 内 垂直间隙 */
static const unsigned int gappoh = 10;  /* 外 水平间隙 */
static const unsigned int gappov = 10;  /* 外 垂直间隙 */

static const int user_lrpad = -12; /* 自定义 左右间距 */
static const int user_bh    = 2;  /* 自定义 增加上下间距 */

static const int vertpad            = 3;       /* vertical padding of bar */
static const int sidepad            = 4;       /* horizontal padding of bar */

/* 1表示只有一个窗口时没有外部边框 */
static const int smartgaps  = 0;

/* 状态栏 设置 */
static const int showbar    = 1;     /* 0 为隐藏 bar */
static const int topbar     = 1;     /* 0 为底部 bar */

static const Bool viewontag = True;  /* Switch view on tag switch */

/* 字体 设置 */
static const char *fonts[] = {
    "Roboto Mono:size=12",
    "Symbols Nerd Font Mono:size=10",
    "Noto Sans CJK SC:size=10",
    "monospace:size=10",
};

/* 颜色 前景 */
static const char col_fg1[] = "#cecec1";
static const char col_fg2[] = "#74c8e2";
static const char col_fg3[] = "#9e9eff";

/* 颜色 边框 */
static const char col_cray1[]  = "#9e9eff";
static const char col_cray2[]  = "#4cee4c";

/* 颜色 背景 */
static const char col_bg1[] = "#2a2a2a";
static const char col_bg2[] = "#474747";

/* 状态栏配色 */
static const char *colors[][3] = {
    /*                  fg           bg             border      */
    [SchemeNorm] = { col_fg1,     col_bg1,        col_cray1 }, /* 默认 */
    [SchemeSel]  = { col_fg2,     col_bg1,        col_cray2 }, /* 选中 */
    [SchemeHid]  = { col_fg3,     col_bg2,        col_cray2 }, /*隐藏*/
};
/* 窗口 默认 透明值 */
static const double defaultopacity = 1;
/* 状态栏 透明值 */
static const unsigned int alphas[][3] = {
    /*               fg   bg     border */
    [SchemeNorm] = { 0,  128,      0 },
    [SchemeSel]  = { 0,  128,      0 },
    [SchemeHid]  = { 0,   72,      0 },
};

/* 便签窗口 */
typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty","--class","Alacritty,spterm", NULL };
const char *spcmd2[] = {"alacritty","--class", "Alacritty,spranger","--title","ranger","-e","ranger",NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"ranger",      spcmd2},
};

/* 标签名称与默认命令 */
static const char *tags[] = { "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹" };
static const char *defaulttagapps[] = {
    "alacritty",
    "/usr/bin/google-chrome-stable",
    "/usr/bin/dolphin",
    "/usr/bin/obsidian",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/* 窗口设置, 使用xprop获取 */
static const Rule rules[] = {
    /*class        instance   title   tags mask  isfloating  monitor  opacity  float x,y,w,h  floatborderpx */
    /*窗口类          事例      标题      标签         悬浮      屏幕位置   透明度    窗口位置与大小   浮动边界*/
    { "spterm",      NULL,    NULL,    SPTAG(0),     1,       -1,      0.85,    -1,-1,960,720,     0 },
    { "spranger",    NULL,    NULL,    SPTAG(1),     1,       -1,      0.85,    -1,-1,1080,810,    0 },
    { "copyq",       NULL,    NULL,    0,	         1,	      -1,	   0.7,	 -1,-1,600,450,	   0 },
    { "mpv",         NULL,    NULL,    0,	         1,	      -1,	   -1,     -1,-1,-1,-1,	   0 },
    { "scrcpy",      NULL,    NULL,    0,	         1,	      -1,	   -1,	    -1,-1,-1,-1,	   0 },
};

/* layout(s) */
static const float mfact  = 0.55;   /* 主栈窗口占比 */
static const int nmaster     = 1;   /* 主栈窗口数量 */
static const int resizehints = 1;   /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
  /* symbol     arrange     function */
    { "",      tile },    /* 平铺 */
    { "",      NULL },    /* 浮动 */
    { "",      monocle }, /* 全屏 */
};


/* custom symbols for nr. of clients in monocle layout */
/* when clients >= LENGTH(monocles), uses the last element */
static const char *monocles[] = { "", "", "", "", "", "", "", "", "", "" };

/* 特殊键为Win键 */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* 按键设置 */
static Key keys[] = {
    /* 特殊键                    虚拟键码     调用函数         参数 */

    /* 脚本 */
    { MODKEY,                   XK_Return, spawn,          SHCMD("~/.config/dwm/terminal.sh")  },
    { MODKEY,                   XK_r,      spawn,          SHCMD("~/.config/dwm/rofi-drun.sh") },
    { Mod1Mask,                 XK_Tab,    spawn,          SHCMD("~/.config/dwm/rofi-windows.sh") },
    { MODKEY|ShiftMask,         XK_l,      spawn,          SHCMD("~/.config/dwm/lock.sh" )},
    { Mod1Mask,                 XK_F4,     spawn,          SHCMD("~/.config/dwm/exit.sh" )},

    /* 退出 */
    { ControlMask|Mod1Mask,     XK_Delete, quit,           {0} },

    /* 开关状态栏 */
    { MODKEY,                   XK_b,      togglebar,      {0} },

    /* 真全屏 */
    { MODKEY|ShiftMask,         XK_b,      fullscreen,     {0} },

    /* 调整主窗口数量 */
    { MODKEY,                   XK_f,      incnmaster,     {.i = +1 } },
    { MODKEY,                   XK_g,      incnmaster,     {.i = -1 } },

    /* 调整主副窗口纵比 */
    { MODKEY,                   XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                   XK_l,      setmfact,       {.f = +0.05} },

    /* 聚集下一个窗口 */
    { MODKEY,                   XK_j,      focusstackvis,  {.i = +1 } },
    { MODKEY,                   XK_k,      focusstackvis,  {.i = -1 } },

    /* 聚集下一个隐藏窗口 */
    { MODKEY|ShiftMask,         XK_j,      focusstackhid,  {.i = +1 } },
    { MODKEY|ShiftMask,         XK_k,      focusstackhid,  {.i = -1 } },

    /* 隐藏窗口*/
    { MODKEY,                   XK_d,      hide,           {0} },
    /* 取消隐藏所有窗口*/
    { MODKEY,                   XK_s,      showall,        {0} },
    /* 取消隐藏当前窗口*/
    { MODKEY|ShiftMask,         XK_s,      show,           {0} },

    /* 关闭应用 */
    { MODKEY|ShiftMask,         XK_q,      killclient,     {0} },

    /* 切换平铺方式 */
    { MODKEY,                   XK_x,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                   XK_c,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                   XK_v,      setlayout,      {.v = &layouts[2]} },

    /* 浮动<->平铺 之间切换 */
    { MODKEY,                   XK_space, togglefloating,  {0} },

    /* 交换窗口位置 */
    { MODKEY|ControlMask,       XK_space,     zoom,              {0} },
    { MODKEY|ControlMask,       XK_j,      inplacerotate,  {.i = +1} },
    { MODKEY|ControlMask,       XK_k,      inplacerotate,  {.i = -1} },
    { MODKEY|ControlMask,       XK_h,      inplacerotate,  {.i = +2} },
    { MODKEY|ControlMask,       XK_l,      inplacerotate,  {.i = -2} },

    /* 全窗口合并 */
    { MODKEY,                   XK_grave,      view,       {.ui = ~0 } },
    /* 提升到全标签 */
    { MODKEY|ShiftMask,         XK_grave,      tag,        {.ui = ~0 } },

    /* 切换多屏幕焦点 */
    { MODKEY,                   XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                   XK_period, focusmon,       {.i = +1 } },

    /* 切换窗口多屏幕 */
    { MODKEY|ShiftMask,         XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,         XK_period, tagmon,         {.i = +1 } },

    /* 权重修改 */
    { MODKEY|ShiftMask,         XK_z,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,         XK_x,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,         XK_c,      setcfact,       {.f =  0.00} },

    { MODKEY,                   XK_Tab,    view,           {0} },
    TAGKEYS(                    XK_1,                      0)
    TAGKEYS(                    XK_2,                      1)
    TAGKEYS(                    XK_3,                      2)
    TAGKEYS(                    XK_4,                      3)
    TAGKEYS(                    XK_5,                      4)
    TAGKEYS(                    XK_6,                      5)
    TAGKEYS(                    XK_7,                      6)
    TAGKEYS(                    XK_8,                      7)
    TAGKEYS(                    XK_9,                      8)

    /* 透明度 */
    { MODKEY|ShiftMask,         XK_KP_Add,      changeopacity,    {.f = +0.1}},
    { MODKEY|ShiftMask,         XK_KP_Subtract, changeopacity,    {.f = -0.1}},

    /* 默认窗口应用 */
    { MODKEY,                   XK_w,       spawndefault,   {0} },

    /* 便签窗口 */
    { MODKEY,                   XK_a,       togglescratch,  {.ui = 0 } },
    { MODKEY,                   XK_z,       togglescratch,  {.ui = 1 } },

    /* 默认窗口间隙 无窗口间隙*/
    { MODKEY,                   XK_0,      defaultgaps,    {0} },
    { MODKEY|ShiftMask,         XK_0,      togglegaps,     {0} },

    /* 增大全窗口间隙 减小全窗口间隙 */
    { MODKEY,                   XK_minus,  incrgaps,       {.i = +1 } },
    { MODKEY,                   XK_equal,  incrgaps,       {.i = -1 } },

    /* 移动 悬浮窗口 */
    { MODKEY,                   XK_Down,   moveresize,     {.v = "0x 25y 0w 0h"  } },
    { MODKEY,                   XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
    { MODKEY,                   XK_Right,  moveresize,     {.v = "25x 0y 0w 0h"  } },
    { MODKEY,                   XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },

    /* 扩大 悬浮窗口 */
    { MODKEY|ShiftMask,         XK_Down,   moveresize,     {.v = "0x 0y 0w 25h"  } },
    { MODKEY|ShiftMask,         XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
    { MODKEY|ShiftMask,         XK_Right,  moveresize,     {.v = "0x 0y 25w 0h"  } },
    { MODKEY|ShiftMask,         XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },

    /* 吸附 悬浮窗口 */
    { MODKEY|ControlMask,       XK_Up,     moveresizeedge, {.v = "t"} },
    { MODKEY|ControlMask,       XK_Down,   moveresizeedge, {.v = "b"} },
    { MODKEY|ControlMask,       XK_Left,   moveresizeedge, {.v = "l"} },
    { MODKEY|ControlMask,       XK_Right,  moveresizeedge, {.v = "r"} },

    /* 吸附并扩大 悬浮窗口 */
    { MODKEY|Mod1Mask,          XK_Up,     moveresizeedge, {.v = "T"} },
    { MODKEY|Mod1Mask,          XK_Down,   moveresizeedge, {.v = "B"} },
    { MODKEY|Mod1Mask,          XK_Left,   moveresizeedge, {.v = "L"} },
    { MODKEY|Mod1Mask,          XK_Right,  moveresizeedge, {.v = "R"} },

    /* 特殊媒体键 */
    { 0, XF86XK_AudioMute,          spawn,      SHCMD("pamixer -t; pkill -RTMIN+3 dwmblocks") },
    { 0, XF86XK_AudioRaiseVolume,   spawn,      SHCMD("pamixer --allow-boost -i 3; pkill -RTMIN+3 dwmblocks") },
    { 0, XF86XK_AudioLowerVolume,   spawn,      SHCMD("pamixer --allow-boost -d 3; pkill -RTMIN+3 dwmblocks") },
    { 0, XF86XK_AudioPrev,          spawn,      SHCMD("mpc prev; pkill -RTMIN+1 dwmblocks") },
    { 0, XF86XK_AudioNext,          spawn,      SHCMD("mpc next; pkill -RTMIN+1 dwmblocks") },
    { 0, XF86XK_AudioPause,         spawn,      SHCMD("mpc pause; pkill -RTMIN+1 dwmblocks") },
    { 0, XF86XK_AudioPlay,          spawn,      SHCMD("mpc toggle; pkill -RTMIN+1 dwmblocks") },
    { 0, XF86XK_MonBrightnessUp,    spawn,      SHCMD("light -A 5;notify-send 亮度$(light)") },
    { 0, XF86XK_MonBrightnessDown,  spawn,      SHCMD("light -U 5;notify-send 亮度$(light)") },
};

/* 鼠标设置 */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

    { ClkWinTitle,          0,              Button1,        togglewin,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },

    /* 发送dwmblocks信号量 */
    { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
    { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
    { ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
    { ClkStatusText,        ShiftMask,      Button4,        sigdwmblocks,   {.i = 7} },
    { ClkStatusText,        ShiftMask,      Button5,        sigdwmblocks,   {.i = 8} },

    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },

    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },

    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
