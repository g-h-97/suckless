/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=32", "JoyPixels:pixelsize=32:antialias=true:autohint=true"};
static const char dmenufont[]       = "monospace:size=32";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

// static const char progs[4][24] = {"firefoxdeveloperedition",
                                    // "Gimp",
                                    // "Virt-manager",
                                    // "st"};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                    instance  title     tags mask  isfloating  isterminal  noswallow  monitor */
    { "Virt-manager",               NULL,   NULL,   1 << 8,         0,          0,          -1,        -1 },
//  { "firefoxdeveloperedition",    NULL,   NULL,   1 << 7,         0,          0,          -1,        -1 },
//  { "IceCat",                     NULL,   NULL,   1 << 7,         0,          0,          -1,        -1 },
//  { "LibreWolf",                  NULL,   NULL,   1 << 3,         0,          0,          -1,        -1 },
	{ "Tor Browser",                NULL,   NULL,   1 << 6,         0,          0,          -1,        -1 },
	{ "Brave-browser",              NULL,   NULL,   1 << 1,         0,          0,          -1,        -1 },
	{ "Gimp",                       NULL,   NULL,   1 << 5,         1,          0,           0,        -1 },
	{ "Transmission-gtk",           NULL,   NULL,   1 << 4,         0,          0,          -1,        -1 },
	{ "st",                         NULL,   NULL,       0,          0,          1,          -1,        -1 },
	{ NULL,                         NULL, "Event Tester", 0,        1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
//static const char *tabtermcmd[]  = { "tabbed", "-c", "-r 2", "st", "-w", "''", NULL };
static const char *flameshot[] = { "flshot", NULL };
static const char *clipmenu[] = { "clipmenu", NULL };
static const char *slock[] = { "slock", NULL };


#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key                 function        argument */
  { 0,                      XF86XK_AudioLowerVolume,    spawn,          SHCMD("amixer -qM set Master 10%-")},
  { 0,                      XF86XK_AudioRaiseVolume,    spawn,          SHCMD("amixer -qM set Master 10%+")},
  { ShiftMask,              XF86XK_AudioLowerVolume,    spawn,          SHCMD("xbacklight -5")},
  { ShiftMask,              XF86XK_AudioRaiseVolume,    spawn,          SHCMD("xbacklight +5")},
  { ShiftMask|ControlMask,  XF86XK_AudioLowerVolume,    spawn,          SHCMD("xbacklight 0")},
  { ShiftMask|ControlMask,  XF86XK_AudioRaiseVolume,    spawn,          SHCMD("xbacklight 50")},
  { 0,                      XF86XK_MonBrightnessDown,   spawn,          SHCMD("xbacklight -5")},
  { 0,                      XF86XK_MonBrightnessUp,     spawn,          SHCMD("xbacklight +5")},
  { MODKEY,                       XK_c,                 spawn,          {.v = clipmenu } },
  { 0,                            XK_Print,             spawn,          {.v = flameshot } },
	{ MODKEY,                       XK_p,               spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,          spawn,          {.v = termcmd } },
//	{ Mod4Mask|ShiftMask,          XK_Return,          spawn,          {.v = tabtermcmd } },
	{ MODKEY,                       XK_b,               togglebar,      {0} },
	{ MODKEY,                       XK_j,               focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,               focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_s,               swapfocus,      {.i = -1 } },
	{ MODKEY,                       XK_i,               incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,               incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,               setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,          zoom,           {0} },
	{ MODKEY,                       XK_Tab,             view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,               killclient,     {0} },
	{ MODKEY,                       XK_t,               setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,               setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,               setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_f,               fullscreen,     {0} },
	{ MODKEY,                       XK_u,               setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,               setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,           setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,           togglefloating, {0} },
	{ MODKEY,                       XK_Down,            moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,              moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,           moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,            moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,            moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,              moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,           moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,            moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,              moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,            moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,            moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,           moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,              moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,            moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,            moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,           moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,               view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,           focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,           setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,           setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,           setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                               0)
	TAGKEYS(                        XK_2,                               1)
	TAGKEYS(                        XK_3,                               2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                               4)
	TAGKEYS(                        XK_6,                               5)
	TAGKEYS(                        XK_7,                               6)
	TAGKEYS(                        XK_8,                               7)
	TAGKEYS(                        XK_9,                               8)
	{ MODKEY|ShiftMask,             XK_l,               spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,             XK_q,               quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

