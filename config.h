#define TERMINAL "st"
#define TERMCLASS "St"
#define FONT_SIZE "10"
#define TOUCHPAD 0
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
#define FONT(name,size,style) name":size="size":style="style":antialias=true:autohint=true"
static const char *fonts[]          = {
    FONT("Fantasque Sans Mono", FONT_SIZE, "Bold"),
    FONT("Liberation Mono", FONT_SIZE, "Bold"),
    FONT("monospace", FONT_SIZE, "Bold"),
    FONT("SymbolsNerdFont", FONT_SIZE, "Bold"),
    FONT("FontAwesome", FONT_SIZE, "Bold"),
    FONT("Weather Icons", FONT_SIZE, "Bold"),
    FONT("Material Icons", FONT_SIZE, "Bold"),
    FONT("file-icons", FONT_SIZE, "Bold"),
    FONT("github-octicons", FONT_SIZE, "Bold"),
    FONT("all-the-icons", FONT_SIZE, "Bold") };
static const char dmenufont[]       = FONT("Fantasque Sans Mono", "12", "Bold");
static const char normbgcolor[]     = "#2F0B3A";
static const char normbordercolor[] = "#BD93F9";
static const char normfgcolor[]     = "#FF00FF";
static const char selfgcolor[]      = "#FFFFFF";
static const char selbordercolor[]  = "#FF00FF";
static const char selbgcolor[]      = "#571DC2";
static const char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;

#define FTERM(name,size, ...) { TERMINAL, "-n", name, "-g", size, "-e", __VA_ARGS__, NULL }
const char *spcmd0[] = FTERM("sp-trm", "170x50", "tterm");
const char *spcmd1[] = FTERM("sp-tlf", "170x50", "tlf");
const char *spcmd2[] = FTERM("sp-clc", "60x30",  "wcalc","-P","-1","-c","-q","--ints","-C","-p","-r","--remember");
const char *spcmd3[] = FTERM("sp-pmx", "120x20", "pulsemixer");
const char *spcmd4[] = FTERM("sp-nws", "150x50", "newsboat");
const char *spcmd5[] = FTERM("sp-mpl", "160x50", "mp");
const char *spcmd6[] = FTERM("sp-alm", "120x20", "sp-alm");
const char *spcmd7[] = {"Eagenda"};

static Sp scratchpads[] = {
   /* name        cmd  */
    {"sp-trm",    spcmd0},
    {"sp-tlf",    spcmd1},
    {"sp-clc",    spcmd2},
    {"sp-pmx",    spcmd3},
    {"sp-nws",    spcmd4},
    {"sp-mpl",    spcmd5},
    {"sp-alm",    spcmd6},
    {"Eagenda",   spcmd7},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class    instance    title    tags mask    iscentered    isfloating    monitor */
    { "MATLAB R2019b - academic use",  NULL,  NULL,    1<<1,  0,  0,  -1 },
    { "Microsoft Teams - Preview",     NULL,  NULL,    1<<5,  0,  0,  -1 },
    { TERMCLASS,          NULL,     NULL,       0,        0,    0,    -1 },
    { "librewolf",        NULL,     NULL,       2,        0,    0,    -1 },
    { "qutebrowser",      NULL,     NULL,       2,        0,    0,    -1 },
    { "KeePassXC",        NULL,     NULL,       2,        0,    0,    -1 },
    { "Chromium",         NULL,     NULL,    1<<7,        0,    0,    -1 },
    { "Psensor",          NULL,     NULL,    1<<7,        0,    0,    -1 },
    { "calibre",          NULL,     NULL,    1<<7,        0,    0,    -1 },
    { "obs",              NULL,     NULL,    1<<7,        0,    0,    -1 },
    { "TelegramDesktop",  NULL,     NULL,    1<<6,        0,    0,    -1 },
    { "easyeffects",      NULL,     NULL,    1<<6,        1,    1,    -1 },
    { "Ferdi",            NULL,     NULL,    1<<5,        0,    0,    -1 },
    { "GNU Octave",       NULL,     NULL,    1<<5,        0,    0,    -1 },
    { "Tex-match",        NULL,     NULL,    1<<4,        0,    1,    -1 },
    { "Gimp",             NULL,     NULL,    1<<3,        0,    0,    -1 },
    { "Inkscape",         NULL,     NULL,    1<<3,        0,    0,    -1 },
    { "FreeCAD",          NULL,     NULL,    1<<3,        0,    0,    -1 },
    { "OpenSCAD",         NULL,     NULL,    1<<3,        0,    0,    -1 },
    { "tabbed",           NULL,     NULL,    1<<2,        0,    0,    -1 },
    { "Zathura",          NULL,     NULL,    1<<2,        0,    0,    -1 },
    { NULL,           "emacs",      NULL,       1,        0,    0,    -1 },
    { NULL,           "mpvFloat",   NULL,    1<<8,        0,    1,    -1 },
    { NULL,           "mpvAlarm",   NULL,       0,        1,    1,    -1 },
    { NULL,/* mpv */  "gl",         NULL,    1<<8,        0,    0,    -1 },
    { NULL,           "fzfmenu",    NULL,       0,        1,    1,    -1 },
    { NULL,           "sp-trm",     NULL,    SPTAG(0),    1,    1,    -1 },
    { NULL,           "sp-tlf",     NULL,    SPTAG(1),    1,    1,    -1 },
    { NULL,           "sp-clc",     NULL,    SPTAG(2),    1,    1,    -1 },
    { NULL,           "sp-pmx",     NULL,    SPTAG(3),    1,    1,    -1 },
    { NULL,           "sp-nws",     NULL,    SPTAG(4),    1,    1,    -1 },
    { NULL,           "sp-mpl",     NULL,    SPTAG(5),    1,    1,    -1 },
    { NULL,           "sp-alm",     NULL,    SPTAG(6),    1,    1,    -1 },
    { NULL,           NULL,     "Eagenda",   SPTAG(7),    1,    1,    -1 },
    { NULL,           NULL,     "Event Tester",     0,    0,    0,    -1 },
    { "LibreWolf",    NULL,     "Library",          0,    1,    1,    -1 },
    { "LibreWolf",    NULL,     "About LibreWolf",  0,    1,    1,    -1 },
};

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
/* layout(s) */
static const float mfact = 0.50;       /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;        /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
    { "H[]",      deck },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { "HHH",      grid },
    { "###",      nrowgrid },
    { "---",      horizgrid },
    { ":::",      gaplessgrid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "[M]",      monocle },
    { "><>",      NULL },    /* no layout function means floating behavior */
    { NULL,       NULL },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_history", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"
static Key keys[] = {
    /* modifier            key             function         argument */
    /* { MODKEY|ShiftMask,    XK_Escape,      spawn,           SHCMD("") }, */
    { MODKEY,              XK_grave,       spawn,           SHCMD("dunstctl close") },
    { MODKEY|ShiftMask,    XK_grave,       spawn,           SHCMD("dunstctl history-pop") },
    { MODKEY,              XK_0,           view,            {.ui = ~0 } },
    { MODKEY|ShiftMask,    XK_0,           tag,             {.ui = ~0 } },
    { MODKEY,              XK_BackSpace,   spawn,           SHCMD("sysact Shutdown") },
    { MODKEY|ShiftMask,    XK_BackSpace,   spawn,           SHCMD("sysact") },

    { MODKEY,              XK_Tab,         view,            {0} },
    { MODKEY|ShiftMask,    XK_Tab,         spawn,           SHCMD("dunstctl history-pop") },
    { MODKEY,              XK_q,           killclient,      {0} },
    /* { MODKEY|ShiftMask,    XK_q,           quit,            {0} }, */
    { MODKEY,              XK_w,           spawn,           SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,    XK_w,           spawn,           SHCMD("$BROWSER2") },
    { MODKEY|ControlMask,  XK_w,           spawn,           SHCMD("librewolf --private-window") },
    { MODKEY,              XK_e,           togglescratch,   {.ui = 7} },
    { MODKEY|ShiftMask,    XK_e,           spawn,           SHCMD("emacsclient -c -a 'emacs'") },
    { MODKEY,              XK_r,           togglescratch,   {.ui = 1} },
    { MODKEY,              XK_t,           setlayout,       {.v = &layouts[0]} },
    { MODKEY|ShiftMask,    XK_t,           setlayout,       {.v = &layouts[1]} },
    { MODKEY|ControlMask,  XK_t,           setlayout,       {.v = &layouts[8]} },
    { MODKEY,              XK_y,           setlayout,       {.v = &layouts[2]} },
    { MODKEY|ShiftMask,    XK_y,           setlayout,       {.v = &layouts[3]} },
    { MODKEY|ControlMask,  XK_y,           setlayout,       {.v = &layouts[9]} },
    { MODKEY,              XK_u,           setlayout,       {.v = &layouts[4]} },
    { MODKEY|ShiftMask,    XK_u,           setlayout,       {.v = &layouts[5]} },
    { MODKEY|ControlMask,  XK_u,           setlayout,       {.v = &layouts[10]} },
    { MODKEY,              XK_i,           setlayout,       {.v = &layouts[6]} },
    { MODKEY|ShiftMask,    XK_i,           setlayout,       {.v = &layouts[7]} },
    { MODKEY|ControlMask,  XK_i,           setlayout,       {.v = &layouts[11]} },
    { MODKEY,              XK_o,           incnmaster,      {.i = +1 } },
    { MODKEY|ShiftMask,    XK_o,           incnmaster,      {.i = -1 } },
    { MODKEY,              XK_p,           spawn,           SHCMD("dmpv") },
    { MODKEY,              XK_bracketleft, spawn,           SHCMD("dmenuunicode") },
    /* { MODKEY,              XK_bracketright, spawn,           SHCMD("") }, */
    { MODKEY,              XK_backslash,   view,            {0} },

    { MODKEY,              XK_a,           togglescratch,   {.ui = 6} },
    /* { MODKEY|ShiftMask,    XK_a,          shifttag,          { .i = -1 } }, */
    { MODKEY,              XK_s,           togglesticky,    {0} },
    { MODKEY,              XK_d,           spawn,           {.v = dmenucmd } },
    { MODKEY|ShiftMask,    XK_d,           spawn,           SHCMD("via -r") },
    { MODKEY|ControlMask,  XK_d,           spawn,           SHCMD("via -a") },
    { MODKEY,              XK_f,           togglefullscr,   {0} },
    { MODKEY|ShiftMask,    XK_f,           setlayout,       {.v = &layouts[13]} },
    { MODKEY|ControlMask,  XK_f,           setlayout,       {.v = &layouts[12]} },
    { MODKEY,              XK_g,           togglegaps,      {0} },
    { MODKEY|ShiftMask,    XK_g,           defaultgaps,     {0} },
    { MODKEY,              XK_h,           setmfact,        {.f = -0.05} },
    { MODKEY|ShiftMask,    XK_h,           tagmon,          {.i = -1 } },
    { MODKEY|ControlMask,  XK_h,           focusmon,        {.i = -1 } },
    { MODKEY,              XK_j,           focusstack,      {.i = +1 } },
    { MODKEY|ShiftMask,    XK_j,           movestack,       {.i = +1 } },
    { MODKEY|ControlMask,  XK_j,           focusmon,        {.i = +1 } },
    { MODKEY,              XK_k,           focusstack,      {.i = -1 } },
    { MODKEY|ShiftMask,    XK_k,           movestack,       {.i = -1 } },
    { MODKEY|ControlMask,  XK_k,           focusmon,        {.i = -1 } },
    { MODKEY,              XK_l,           setmfact,        {.f = +0.05} },
    { MODKEY|ShiftMask,    XK_l,           tagmon,          {.i = +1 } },
    { MODKEY|ControlMask,  XK_l,           focusmon,        {.i = +1 } },
    /* { MODKEY,              XK_semicolon,  shiftview,        { .i = 1 } }, */
    /* { MODKEY|ShiftMask,    XK_semicolon,  shifttag,         { .i = 1 } }, */
    { MODKEY,              XK_apostrophe,  togglescratch,   {.ui = 2} },
    { MODKEY,              XK_Return,      togglescratch,   {.ui = 0 } },
    { MODKEY|ShiftMask,    XK_Return,      spawn,           {.v = termcmd } },

    { MODKEY,              XK_z,           incrgaps,        {.i = +3 } },
    { MODKEY,              XK_x,           incrgaps,        {.i = -3 } },
    { MODKEY,              XK_c,           spawn,           SHCMD("clip-file") },
    /* { MODKEY,              XK_v,           spawn,           SHCMD("") }, */
    { MODKEY,              XK_b,           togglebar,       {0} },
    { MODKEY,              XK_n,           togglescratch,   {.ui = 4} },
    { MODKEY,              XK_m,           togglescratch,   {.ui = 5} },
    { MODKEY|ShiftMask,    XK_m,           spawn,           SHCMD("pkill spotifyd; pkill librespot; pkill spotify-tui") },
    { MODKEY,              XK_comma,       spawn,           SHCMD("dmpc toggle") },
    { MODKEY,              XK_period,      spawn,           SHCMD("tppctl toggle") },
    { MODKEY|ShiftMask,    XK_period,      spawn,           SHCMD("tppctl invert") },
    { MODKEY|ControlMask,  XK_period,      spawn,           SHCMD("tppctl pauseall") },
    { MODKEY,              XK_slash,       spawn,           SHCMD("mprisctl play-pause") },

    { MODKEY,              XK_Up,          spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -39 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,    XK_Up,          spawn,           SHCMD("output-audio") },
    { MODKEY,              XK_Down,        spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -39 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,    XK_Down,        spawn,           SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -39 $(pidof dwmblocks)") },
    { MODKEY,              XK_Left,        spawn,           SHCMD("tppctl seek -10") },
    { MODKEY|ShiftMask,    XK_Left,        spawn,           SHCMD("dmpc prev") },
    { MODKEY,              XK_Right,       spawn,           SHCMD("tppctl seek +10") },
    { MODKEY|ShiftMask,    XK_Right,       spawn,           SHCMD("dmpc next") },

    /* { MODKEY,              XK_Page_Up,     shiftview,       { .i = -1 } }, */
    /* { MODKEY|ShiftMask,    XK_Page_Up,     shifttag,        { .i = -1 } }, */
    /* { MODKEY,              XK_Page_Down,   shiftview,       { .i = +1 } }, */
    /* { MODKEY|ShiftMask,    XK_Page_Down,   shifttag,        { .i = +1 } }, */
    { MODKEY,              XK_Insert,      spawn,           SHCMD("clipmenu") },
    { MODKEY|ShiftMask,    XK_Insert,      spawn,           SHCMD("notify-send \" Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },

    /* { MODKEY,              XK_F1,          spawn,           SHCMD("") }, */
    /* { MODKEY,              XK_F2,          spawn,           SHCMD("") }, */
    { MODKEY,              XK_F3,          spawn,           SHCMD("wifi-toggle && pkill -RTMIN+3 dwmblocks") },
    { MODKEY|ShiftMask,    XK_F3,          spawn,           SHCMD("bluetooth toggle && pkill -RTMIN+4 dwmblocks") },
    { MODKEY,              XK_F5,          spawn,           SHCMD("xrdb -load ~/.config/x11/Xresources_Light && notify-send 'Light Mode'") },
    { MODKEY|ShiftMask,    XK_F5,          spawn,           SHCMD("xrdb -load ~/.config/x11/Xresources && notify-send 'Default Mode'") },
    { MODKEY,              XK_F6,          togglescratch,   {.ui = 3 } },
    { MODKEY,              XK_F7,          spawn,           SHCMD("i3lock -e -f -c 1d2021 -i ~/Storage/Pictures/lockscreen.png; xset dpms force off") },
    { MODKEY,              XK_F8,          spawn,           SHCMD("t-tlp") },
    { MODKEY,              XK_F9,          spawn,           SHCMD("dmenumount") },
    { MODKEY,              XK_F10,         spawn,           SHCMD("dmenuumount") },
    { MODKEY,              XK_F11,         spawn,           SHCMD("dmpc prev") },
    { MODKEY|ShiftMask,    XK_F11,         spawn,           SHCMD("tppclt seek -10") },
    { MODKEY,              XK_F12,         spawn,           SHCMD("dmpc next") },
    { MODKEY|ShiftMask,    XK_F12,         spawn,           SHCMD("tppclt seek 10") },
    /* { MODKEY|ShiftMask,    XK_F12,         xrdb,            {.v = NULL } }, */
    { MODKEY,              XK_space,       zoom,            {0} },
    { MODKEY|ShiftMask,    XK_space,       togglefloating,  {0} },

    {0,                    XK_Print,       spawn,      SHCMD("maimpick") },
    { MODKEY,              XK_Print,       spawn,      SHCMD("maim ~/Storage/F$(date '+%y%m%d-%H%M-%S').png") },
    { MODKEY|ShiftMask,    XK_Print,       spawn,      SHCMD("maimpick") },
    /* { MODKEY,              XK_Delete,      togglescratch,   {.ui = 6} }, */
    /* { MODKEY,              XK_Scroll_Lock, spawn,           SHCMD("") }, */

    { 0,        XF86XK_AudioMute,          spawn,           SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -39 $(pidof dwmblocks)") },
    { MODKEY,   XF86XK_AudioMute,          spawn,           SHCMD("output-audio") },
    { 0,        XF86XK_AudioRaiseVolume,   spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -39 $(pidof dwmblocks)") },
    { 0,        XF86XK_AudioLowerVolume,   spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -39 $(pidof dwmblocks)") },
    /* { 0,        XF86XK_AudioMute,          spawn,           SHCMD("pulsemixer --toggle-mute; kill -44 $(pidof dwmblocks)") }, */
    /* { MODKEY,   XF86XK_AudioMute,          togglescratch,   {.ui = 3} }, */
    /* { 0,           XF86XK_AudioRaiseVolume,spawn,           SHCMD("pulsemixer --change-volume +5; kill -44 $(pidof dwmblocks)") }, */
    /* { 0,           XF86XK_AudioLowerVolume,spawn,           SHCMD("pulsemixer --change-volume -5; kill -44 $(pidof dwmblocks)") }, */
    { 0,        XF86XK_AudioPrev,          spawn,           SHCMD("dmpc prev") },
    { MODKEY,   XF86XK_AudioPrev,          spawn,           SHCMD("tppctl seek -10") },
    { 0,        XF86XK_AudioNext,          spawn,           SHCMD("dmpc next") },
    { MODKEY,   XF86XK_AudioNext,          spawn,           SHCMD("tppctl seek 10") },
    { 0,        XF86XK_AudioPlay,          spawn,           SHCMD("tppctl invert") },
    { MODKEY,   XF86XK_AudioPlay,          spawn,           SHCMD("dmpc toggle") },
    { 0,        XF86XK_AudioStop,          togglescratch,   {.ui = 3 } },

    /* { 0,        XF86XK_AudioRewind,        spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_AudioForward,       spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_AudioMedia,         spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_PowerOff,           spawn,           SHCMD("") }, */
    { 0,        XF86XK_Calculator,         togglescratch,   {.ui = 2} },
    /* { MODKEY,   XF86XK_Calculator,         spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_Sleep,              spawn,           SHCMD("") }, */
    { 0,        XF86XK_WWW,                spawn,           SHCMD("wifi-toggle && pkill -RTMIN+3 dwmblocks") },
    { 0,        XF86XK_WWAN,               spawn,           SHCMD("wifi-toggle && pkill -RTMIN+3 dwmblocks") },
    /* { 0,        XF86XK_DOS,                spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_ScreenSaver,        spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_TaskPane,           spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_Mail,               spawn,           SHCMD("ferdi") }, */
    /* { 0,        XF86XK_MyComputer,         spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_Battery,            spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_HomePage,           spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_Search,             spawn,           SHCMD("") }, */
    { 0,        XF86XK_Favorites,             spawn,           SHCMD("remaps") },
    /* { 0,        XF86XK_Launch5,            spawn,           SHCMD("") }, */
    /* { 0,        XF86XK_Launch6,            spawn,           SHCMD("") }, */
    { 0,        XF86XK_Launch7,           togglescratch,    {.ui = 3} },
    { 0,        XF86XK_Launch8,           spawn,            SHCMD("dmpc prev") },
    { MODKEY,   XF86XK_Launch8,           spawn,            SHCMD("tppctl seek -10") },
    { 0,        XF86XK_Launch9,           spawn,            SHCMD("dmpc next") },
    { MODKEY,   XF86XK_Launch9,           spawn,            SHCMD("tppctl seek 10") },
    /* {0,         XF86XK_Back,              shiftview,        {.i = -1} }, */
    /* {0,         XF86XK_Forward,           shiftview,        {.i = 1} }, */

    /* { 0,        XF86XK_Display,           spawn,            SHCMD("") }, */
    { 0,        XF86XK_TouchpadToggle,    spawn,            SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    /* { 0,        XF86XK_TouchpadOff,       spawn,            SHCMD("") }, */
    /* { 0,        XF86XK_TouchpadOn,        spawn,            SHCMD("") }, */
    { 0,        XF86XK_MonBrightnessUp,   spawn,            SHCMD("xbacklight -inc 15; pkill -RTMIN+6 dwmblocks") },
    { MODKEY,   XF86XK_MonBrightnessUp,   spawn,            SHCMD("xbacklight -inc 5; pkill -RTMIN+6 dwmblocks") },
    { 0,        XF86XK_MonBrightnessDown, spawn,            SHCMD("xbacklight -dec 15; pkill -RTMIN+6 dwmblocks") },
    { MODKEY,   XF86XK_MonBrightnessDown, spawn,            SHCMD("xbacklight -dec 5; pkill -RTMIN+6 dwmblocks") },
    TAGKEYS(                        XK_1,                   0)
    TAGKEYS(                        XK_2,                   1)
    TAGKEYS(                        XK_3,                   2)
    TAGKEYS(                        XK_4,                   3)
    TAGKEYS(                        XK_5,                   4)
    TAGKEYS(                        XK_6,                   5)
    TAGKEYS(                        XK_7,                   6)
    TAGKEYS(                        XK_8,                   7)
    TAGKEYS(                        XK_9,                   8)
    { MODKEY|Mod1Mask,              XK_u,    incrgaps,      {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_u,    incrgaps,      {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_i,    incrigaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_i,    incrigaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_o,    incrogaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_o,    incrogaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_6,    incrihgaps,    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_6,    incrihgaps,    {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_7,    incrivgaps,    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_7,    incrivgaps,    {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_8,    incrohgaps,    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_8,    incrohgaps,    {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_9,    incrovgaps,    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_9,    incrovgaps,    {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_0,    togglegaps,    {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_0,    defaultgaps,   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    #if TOUCHPAD
    { ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
    #endif
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
