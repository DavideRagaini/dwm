/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx	= 2;	/* border pixel of windows */
static const unsigned int snap		= 15;	/* snap pixel */
static const unsigned int gappih	= 20;	/* horiz inner gap between windows */
static const unsigned int gappiv	= 10;	/* vert inner gap between windows */
static const unsigned int gappoh	= 10;	/* horiz outer gap between windows and screen edge */
static const unsigned int gappov	= 10;	/* vert outer gap between windows and screen edge */
static const int swallowfloating	= 1;	/* 1 means swallow floating windows by default */
static const int smartgaps		= 1;	/* 1 means no outer gap when there is only one window */
static const int showbar		= 1;	/* 0 means no bar */
static const int topbar			= 0;	/* 0 means bottom bar */
static const char *fonts[]		= { "Iosevka:size=12", "Inconsolata:size=12" };
static char dmenufont[]			= "Iosevka:size=26";
static char normbgcolor[]		= "#2F0B3A";
static char normbordercolor[]		= "#BD93F9";
static char normfgcolor[]		= "#cc00cc";
static char selfgcolor[]		= "#dddddd";
static char selbordercolor[]		= "#FF00FF";
static char selbgcolor[]		= "#571dc2";
static char *colors[][3] = {
			/* fg		bg		border	*/
	[SchemeNorm] = { normfgcolor,	normbgcolor,	normbordercolor },
	[SchemeSel] = { selfgcolor,	selbgcolor,	selbordercolor	},
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd0[] = {"alacritty", "--class", "sp-term", "-e", "tmux", "new-session", "-s", "dropdown", NULL };
const char *spcmd1[] = {"alacritty", "--class", "sp-calc", "--config-file", "/home/davide/.config/alacritty/calc.yml", "-e", "bc", "-lq", NULL };
const char *spcmd2[] = {"alacritty", "--class", "sp-audio", "--config-file", "/home/davide/.config/alacritty/small.yml", "-e", "pulsemixer", NULL };
const char *spcmd3[] = {"alacritty", "--class", "sp-mp", "-e", "mp", NULL };
const char *spcmd4[] = {"alacritty", "--class", "sp-lf", "-e", "tlf", NULL };
const char *spcmd5[] = {"alacritty", "--class", "sp-news", "-e", "newsboat", NULL };

static Sp scratchpads[] = {
	/* name		cmd */
	{"sp-term",	spcmd0},
	{"sp-calc",	spcmd1},
	{"sp-audio",	spcmd2},
	{"sp-mp",	spcmd3},
	{"sp-lf",	spcmd4},
	{"sp-news",	spcmd5},
};

/* tagging */
static const char *tags[] = { "1 ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance	title		tags mask isfloating isterminal noswallow monitor */
	{ "LibreWolf",	NULL,		NULL,		1,		0,	0,	0,	-1 },
	{ "qutebrowser",NULL,		NULL,		1,		0,	0,	0,	-1 },
	{ "Emacs",	NULL,		NULL,		1 << 1,		0,	0,	0,	-1 },
	{ "mpv",	NULL,		NULL,		1 << 8,		1,	0,	0,	-1 },
	{ TERMCLASS,	NULL,		NULL,		0,		0,	1,	0,	-1 },
	{ NULL,		NULL,		"Event Tester",	0,		0,	0,	1,	-1 },
	{ NULL,		"sp-term",	NULL,		SPTAG(0),	1,	1,	0,	-1 },
	{ NULL,		"sp-calc",	NULL,		SPTAG(1),	1,	1,	0,	-1 },
	{ NULL,		"sp-audio",	NULL,		SPTAG(2),	1,	1,	0,	-1 },
	{ NULL,		"sp-mp",	NULL,		SPTAG(3),	1,	1,	0,	-1 },
	{ NULL,		"sp-lf",	NULL,		SPTAG(4),	1,	1,	0,	-1 },
	{ NULL,		"sp-news",	NULL,		SPTAG(5),	1,	1,	0,	-1 },
	{ NULL,		"sp-gotop",	NULL,		SPTAG(6),	1,	1,	0,	-1 },
};

/* layout(s) */
static const float mfact = 0.50;	/* factor of master area size [0.05..0.95] */
static const int nmaster = 1;		/* number of clients in master area */
static const int resizehints = 1;	/* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1			/* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol	arrange function */
	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY,	view,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,		KEY,	toggleview,	{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,		KEY,	tag,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,	toggletag,	{.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,		XK_j,		ACTION##stack,		{.i = INC(+1) } }, \
	{ MOD,		XK_k,		ACTION##stack,		{.i = INC(-1) } }, \
	/* { MOD,	XK_grave,	ACTION##stack,		{.i = PREVSEL } }, \ */
	/* { MOD,	XK_q,		ACTION##stack,		{.i = 0 } }, \ */
	/* { MOD,	XK_a,		ACTION##stack,		{.i = 1 } }, \ */
	/* { MOD,	XK_z,		ACTION##stack,		{.i = 2 } }, \ */
	/* { MOD,	XK_x,		ACTION##stack,		{.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
/* static const char *termcmd[] = {TERMINAL, "-e", "tmux", NULL }; */

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier		key		function	argument */
	STACKKEYS(MODKEY,		focus)
	STACKKEYS(MODKEY|ShiftMask,	push)
	/* { MODKEY|ShiftMask,	XK_Escape,	spawn,	SHCMD("") }, */
	{ MODKEY,		XK_grave,	spawn,	SHCMD("dmenuunicode") },
	TAGKEYS(	XK_1,	0)
	TAGKEYS(	XK_2,	1)
	TAGKEYS(	XK_3,	2)
	TAGKEYS(	XK_4,	3)
	TAGKEYS(	XK_5,	4)
	TAGKEYS(	XK_6,	5)
	TAGKEYS(	XK_7,	6)
	TAGKEYS(	XK_8,	7)
	TAGKEYS(	XK_9,	8)
	{ MODKEY,	XK_0,	view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,		XK_BackSpace,	spawn,		SHCMD("timeOnPc shutdown") },
	{ MODKEY|ShiftMask,	XK_BackSpace,	spawn,		SHCMD("timeOnPc") },

	{ MODKEY,		XK_Tab,		swapfocus,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_Tab,		view,		{0} },
	{ MODKEY,		XK_q,		killclient,	{0} },
	{ MODKEY,		XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY,		XK_e,		spawn,		SHCMD("emacs") },
	{ MODKEY,		XK_r,		togglescratch,	{.ui = 4} },
	{ MODKEY,		XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,	XK_t,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY,		XK_y,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,	XK_y,		setlayout,	{.v = &layouts[3]} },
	{ MODKEY,		XK_u,		setlayout,	{.v = &layouts[4]} },
	{ MODKEY|ShiftMask,	XK_u,		setlayout,	{.v = &layouts[5]} },
	{ MODKEY,		XK_i,		setlayout,	{.v = &layouts[6]} },
	{ MODKEY|ShiftMask,	XK_i,		setlayout,	{.v = &layouts[7]} },
	{ MODKEY,		XK_o,		incnmaster,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_o,		incnmaster,	{.i = -1 } },
	{ MODKEY,		XK_p,		spawn,		SHCMD("dmpv") },
	/* { MODKEY,		XK_bracketleft,		spawn,	SHCMD("") }, */
	/* { MODKEY,		XK_bracketright,	spawn,	SHCMD("") }, */
	{ MODKEY,		XK_backslash,		view,	{0} },

	{ MODKEY,		XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,	XK_a,		defaultgaps,	{0} },
	{ MODKEY,		XK_s,		togglesticky,	{0} },
	{ MODKEY,		XK_d,		spawn,		{.v = dmenucmd } },
	{ MODKEY|ShiftMask,	XK_d,		spawn,		SHCMD("via") },
	{ MODKEY,		XK_f,		togglefullscr,	{0} },
	{ MODKEY|ShiftMask,	XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,		XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,	XK_g,		shifttag,	{ .i = -1 } },
	{ MODKEY,		XK_h,		setmfact,	{.f = -0.05} },

	{ MODKEY,		XK_l,		setmfact,	{.f = +0.05} },
	{ MODKEY,		XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,	XK_semicolon,	shifttag,	{ .i = 1 } },
	{ MODKEY,		XK_apostrophe,	togglescratch,	{.ui = 1} },
	{ MODKEY,		XK_Return,	togglescratch,	{.ui = 0 } },
	/* { MODKEY|ShiftMask,	XK_Return,	spawn,		{.v = termcmd } }, */

	{ MODKEY,		XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY,		XK_x,		incrgaps,	{.i = -3 } },
	{ MODKEY,		XK_c,		spawn,		SHCMD("clip-file") },
	/* { MODKEY,		XK_v,		spawn,		SHCMD("") }, */
	{ MODKEY,		XK_b,		togglebar,	{0} },
	{ MODKEY,		XK_n,		togglescratch,	{.ui = 5} },
	{ MODKEY,		XK_m,		togglescratch,	{.ui = 3} },
	{ MODKEY,		XK_comma,	spawn,		SHCMD("dmpc toggle") },
	{ MODKEY,		XK_period,	spawn,		SHCMD("tppctl play-pause") },

	{ MODKEY,		XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,		XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_Right,	tagmon,		{.i = +1 } },

	{ MODKEY,		XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,	XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,		XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,	XK_Page_Down,	shifttag,	{ .i = +1 } },
	{ MODKEY,		XK_Insert,	spawn,		SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },

	/* { MODKEY,		XK_F1,		spawn,		SHCMD("") }, */
	{ MODKEY,		XK_F2,		spawn,		SHCMD("killall -q dwmblocks; setsid dwmblocks &") },
	{ MODKEY,		XK_F3,		spawn,		SHCMD("wifi toggle && sleep 10 && pkill -RTMIN+16 dwmblocks") },
	/* { 0,			XF86XK_WWAN,	spawn,		SHCMD("") }, */
	{ MODKEY|ShiftMask,	XK_F3,		spawn,		SHCMD("t-bluetooth") },
	/* { MODKEY,		XF86XK_WWAN,	spawn,		SHCMD("") }, */
	/* { MODKEY,		XK_F3,		spawn,		SHCMD("") }, */
	/* { MODKEY,		XK_F4,		spawn,		SHCMD("") }, */
	{ MODKEY,		XK_F5,		spawn,		SHCMD("xrdb ~/.config/Xresources") },
	{ MODKEY|ShiftMask,	XK_F5,		spawn,		SHCMD("xrdb -remove ~/.config/Xresources") },
	/* { MODKEY,		XK_F6,		spawn,		SHCMD("") }, */
	{ MODKEY,		XK_F7,		spawn,		SHCMD("i3lock -e -f -c 1d2021 -i ~/.config/Icons/lockscreen.png; xset dpms force off") },
	/* { MODKEY,		XK_F8,		spawn,		SHCMD("") }, */
	{ MODKEY,		XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,		XK_F10,		spawn,		SHCMD("dmenuumount") },
	/* { MODKEY,		XK_F11,		spawn,		SHCMD("") }, */
	{ MODKEY,		XK_F12,		spawn,		SHCMD(TERMINAL " -e sudo nmtui") },
	{ MODKEY|ShiftMask,	XK_F12,		xrdb,		{.v = NULL } },
	{ MODKEY,		XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,	XK_space,	togglefloating,	{0} },

	{ 0,			XK_Print,	spawn,		SHCMD("maim F$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,		XK_Print,	spawn,		SHCMD("maimpick") },
	{ MODKEY,		XK_Delete,	togglescratch,	{.ui = 6} },
	/* { MODKEY,		XK_Scroll_Lock,	spawn,		SHCMD("") }, */

	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pulsemixer --toggle-mute; kill -44 $(pidof dwmblocks)") },
	{ MODKEY, XF86XK_AudioMute,	togglescratch,	{.ui = 2} },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("amixer sset -q Master 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("amixer sset -q Master 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("dmpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("dmpc next") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("dmpc toggle") },
	{ MODKEY, XF86XK_AudioPlay,	spawn,		SHCMD("tppctl") },
	{ MODKEY|ShiftMask, XF86XK_AudioPlay,	spawn,	SHCMD("tppctl; dmpc toggle") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	/* { 0, XF86XK_AudioRewind,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_AudioForward,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_AudioMedia,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_PowerOff,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Calculator,	spawn,		SHCMD("") }, */
	/* { MODKEY, XF86XK_Calculator,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Sleep,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_WWW,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_DOS,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_ScreenSaver,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_TaskPane,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Mail,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_MyComputer,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_HomePage,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Search,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Favorites,	togglescratch,	{.ui = 0 } }, */
	/* { 0, XF86XK_Launch5,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Launch6,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Launch7,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Launch8,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Launch9,		spawn,		SHCMD("") }, */
	/* { 0, XF86XK_Display,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	/* { 0, XF86XK_TouchpadOff,	spawn,		SHCMD("") }, */
	/* { 0, XF86XK_TouchpadOn,	spawn,		SHCMD("") }, */
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY, XF86XK_MonBrightnessUp,spawn,		SHCMD("xbacklight -inc 5; pkill -RTMIN+6 dwmblocks") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY, XF86XK_MonBrightnessDown,spawn,	SHCMD("xbacklight -dec 5; pkill -RTMIN+6 dwmblocks") },

	/* { MODKEY|Mod4Mask,			XK_h,	incrgaps,	{.i = +1 } }, */
	/* { MODKEY|Mod4Mask,			XK_l,	incrgaps,	{.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,		XK_h,	incrogaps,	{.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,		XK_l,	incrogaps,	{.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,	XK_h,	incrigaps,	{.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,	XK_l,	incrigaps,	{.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,		XK_0,	defaultgaps,	{0} }, */
	/* { MODKEY,				XK_y,	incrihgaps,	{.i = +1 } }, */
	/* { MODKEY,				XK_o,	incrihgaps,	{.i = -1 } }, */
	/* { MODKEY|ControlMask,		XK_y,	incrivgaps,	{.i = +1 } }, */
	/* { MODKEY|ControlMask,		XK_o,	incrivgaps,	{.i = -1 } }, */
	/* { MODKEY|Mod4Mask,			XK_y,	incrohgaps,	{.i = +1 } }, */
	/* { MODKEY|Mod4Mask,			XK_o,	incrohgaps,	{.i = -1 } }, */
	/* { MODKEY|ShiftMask,			XK_y,	incrovgaps,	{.i = +1 } }, */
	/* { MODKEY|ShiftMask,			XK_o,	incrovgaps,	{.i = -1 } }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click		event mask	button		function	argument */
	{ ClkWinTitle,		0,		Button2,	zoom,		{0} },
	{ ClkStatusText,	0,		Button1,	sigdwmblocks,	{.i = 1} },
	{ ClkStatusText,	0,		Button2,	sigdwmblocks,	{.i = 2} },
	{ ClkStatusText,	0,		Button3,	sigdwmblocks,	{.i = 3} },
	{ ClkStatusText,	0,		Button4,	sigdwmblocks,	{.i = 4} },
	{ ClkStatusText,	0,		Button5,	sigdwmblocks,	{.i = 5} },
	{ ClkStatusText,	ShiftMask,	Button1,	sigdwmblocks,	{.i = 6} },
	{ ClkStatusText,	ShiftMask,	Button3,	spawn,		SHCMD(TERMINAL " -e nvim ~/.config/dwmblocks/config.h") },
	{ ClkClientWin, 	MODKEY,		Button1,	movemouse,	{0} },
	{ ClkClientWin, 	MODKEY,		Button2,	defaultgaps, 	{0} },
	{ ClkClientWin, 	MODKEY,		Button3,	resizemouse, 	{0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,	 	0,		Button1,	view,		{0} },
	{ ClkTagBar,	 	0,		Button3,	toggleview,	{0} },
	{ ClkTagBar,	 	MODKEY,		Button1,	tag,		{0} },
	{ ClkTagBar,	 	MODKEY,		Button3,	toggletag,	{0} },
	{ ClkTagBar,	 	0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,	 	0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};

