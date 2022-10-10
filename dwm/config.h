/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray       = 1;     /* 0 means no systray */

static const unsigned int snap     = 50;  /* snap pixel */
static const unsigned int borderpx = 3;   /* border pixel of windows */

static const unsigned int gappih = 4;  /* horiz inner gap between windows */
static const unsigned int gappiv = 4;  /* vert inner gap between windows */
static const unsigned int gappoh = 4;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 4;  /* vert outer gap between windows and screen edge */

static const int vertpad = 4;  /* vertical padding of bar */
static const int sidepad = 4;  /* horizontal padding of bar */

static const int smartgaps  = 0;     /* 1 means no outer gap when there is only one window */
static const int showbar    = 1;     /* 0 means no bar */
static const int topbar     = 1;     /* 0 means bottom bar */
static const Bool viewontag = True;  /* Switch view on tag switch */

static const char *fonts[] = {
    "Roboto Mono:size=12",
    "Noto Sans CJK SC:size=10",
    "Symbols Nerd Font Mono:size=10"
};
static const char dmenufont[] = "Noto Sans CJK SC:size=10";

static const char col_gray1[] = "#000000";
static const char col_gray2[] = "#cccccc";
static const char col_gray3[] = "#dddddd";

static const char col_cyan1[]  = "#008080";
static const char col_cyan2[]  = "#00ccff";
static const char col_violet[] = "#acacff";

static const char *colors[][3] = {
    /*                   fg         bg         border  */
    [SchemeNorm] = { col_gray2,  col_gray1,   col_gray2 },
    [SchemeSel]  = { col_gray3,  col_cyan1,   col_cyan2 },
    [SchemeHid]  = { col_violet, col_gray1,   col_cyan1 },
};

static const double defaultopacity = 1;

static const unsigned int alphas[][3] = {
    /*             fg     bg     border */
    [SchemeNorm] = { 0,  128,      0 },
    [SchemeSel]  = { 0,  128,      0 },
    [SchemeHid]  = { 0,   48,      0 },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;

const char *spcmd1[] = {"wezterm","start","--class","spterm", NULL };
const char *spcmd2[] = {"alacritty","--class", "Alacritty,spranger","--title","ranger","-e","ranger",NULL };

static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"ranger",      spcmd2},
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "6", "7", "8", "9" };
static const char *defaulttagapps[] = {
    "alacritty",
    "/usr/bin/google-chrome-stable",
    "/usr/bin/dolphin",
    "/usr/bin/joplin-desktop",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static const Rule rules[] = {
    /*class      instance   title   tags mask  isfloating   monitor  opacity     float x,y,w,h   floatborderpx*/
    /*窗口类         事例     标题      标签      悬浮    屏幕位置   透明度      窗口位置与大小  浮动边界*/
    { "spterm",      NULL,    NULL,    SPTAG(0),     1,    -1,          0.80,    -1,-1,960,720,    0 },
    { "spranger",    NULL,    NULL,    SPTAG(1),     1,    -1,          0.80,    -1,-1,-1,-1,    0 },
    { "copyq",       NULL,    NULL,	       0,	     1,	   -1,	         -1,	 -1,-1,600,400,	 0 },
};

/* layout(s) */
static const float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;     /* number of clients in master area */
static const int resizehints = 1;     /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "",      tile },    /* first entry is default */
    { "",      NULL },    /* no layout function means floating behavior */
    { "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2]       = "0";
static const char *dmenucmd[] = { "dmenu_run", NULL };

/* commands */
static const char *termcmd[]    = { "alacritty", NULL };
static const char *rofidrun[]   = { "rofi", "-show", "drun",NULL };
static const char *rofiwindow[] = { "rofi", "-show", "window",NULL };

static Key keys[] = {
    /* 特殊键                        虚拟键码     调用函数             参数 */

    /* 快速启动 */
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_r,      spawn,          {.v = rofidrun } },
    { MODKEY|ShiftMask,             XK_Tab,    spawn,          {.v = rofiwindow } },

    { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("~/.config/dwm/lock.sh" )},
    {Mod1Mask,                     XK_F4,          spawn,          SHCMD("~/.config/dwm/exit.sh" )},
    {ControlMask|Mod1Mask,         XK_Delete,      quit,           {0} },


    /* 全屏 */
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY|ShiftMask,             XK_b,      fullscreen,     {0} },

    /* 调整主窗口数量 */
    { MODKEY,                       XK_s,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

    /* 调整主副窗口纵比 */
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

    /* 调整聚集窗口位置 */
    { MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
    { MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },

    /* 退出窗口应用 */
    { MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

    /* 切换平铺方式 */
    { MODKEY,                       XK_x,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_c,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_v,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    /* 切换窗口位置 */
    { MODKEY,                                   XK_Return,     zoom,             {0} },
    { MODKEY|ControlMask|ShiftMask,             XK_j,      inplacerotate,  {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,             XK_k,      inplacerotate,  {.i = -1} },
    { MODKEY|ControlMask|ShiftMask,             XK_h,      inplacerotate,  {.i = +2} },
    { MODKEY|ControlMask|ShiftMask,             XK_l,      inplacerotate,  {.i = -2} },

    /* 全窗口合并 */
    { MODKEY,                       XK_grave,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_grave,      tag,            {.ui = ~0 } },
    
    /* 多屏幕*/
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    /* 隐藏取消 */
    { MODKEY,                       XK_i,      show,           {0} },
    { MODKEY,                       XK_o,      hide,           {0} },
    /* 模式切换 */
    { MODKEY|ShiftMask,             XK_z,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_x,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_c,      setcfact,       {.f =  0.00} },

    { MODKEY,                       XK_Tab,    view,           {0} },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)

    //透明度
    { MODKEY|ShiftMask,        XK_KP_Add,      changeopacity,    {.f = +0.1}},
    { MODKEY|ShiftMask,        XK_KP_Subtract, changeopacity,    {.f = -0.1}},

    //特殊窗口
    { MODKEY,                        XK_w,       spawndefault,   {0} },
    { MODKEY,                        XK_a,       togglescratch,  {.ui = 0 } },
    { MODKEY,                        XK_z,       togglescratch,  {.ui = 1 } },

    //窗口间隙
    { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
    { MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

    //悬浮调整窗口
    { MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
    { MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
    { MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
    { MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
    { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
    { MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
    { MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
    { MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
    { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
    { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
    { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
    { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
    { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
    { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
    { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
    { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

    //特殊键
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

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

    { ClkWinTitle,          0,              Button1,        togglewin,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },

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
