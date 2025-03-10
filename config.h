/* See LICENSE file for copyright and license details. */

#include "theme.h"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *colors[][3]      = {
	/*               					fg         bg       border   */
	[SchemeNorm] 			= { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  			= { col_gray4, col_mauve, col_mauve },
	[SchemeStatus]  	= { col_gray3, col_gray1, col_black }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  	= { col_black, col_mauve, col_black }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_gray3, col_gray1, col_black }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  	= { col_gray4, col_gray1, col_black }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_gray3, col_gray1, col_black }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      col },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 			= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_mauve, "-sf", col_black, NULL };
static const char *termcmd[]  			= { "alacritty", NULL };
static const char *browsercmd[]  		= { "librewolf", NULL };
static const char *discordcmd[]  		= { "discord", NULL };
static const char *chatterinocmd[]  = { "chatterino", NULL };
static const char *flameshotcmd[]		= { "flameshot", "gui", NULL};
static const char *upvol[]   				= { "amixer", "set", "Master", "2%+",     NULL };
static const char *downvol[] 				= { "amixer", "set", "Master", "2%-",     NULL };
static const char *mutevol[] 				= { "amixer", "set", "Master", "toggle", NULL };
#include "exitdwm.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0, 														XK_Print,	 spawn,					 {.v = flameshotcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY, 											XK_b,      spawn,      		 {.v = browsercmd } },
	{ MODKEY, 											XK_d,      spawn,      		 {.v = discordcmd } },
	{ MODKEY, 											XK_c,      spawn,      		 {.v = chatterinocmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_h,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_g,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask, 						XK_b, 		 spawn,       	 SHCMD("xdotool type $(grep -v '^#' ~/.config/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
	{ MODKEY|ShiftMask|ControlMask, XK_b,      spawn,       	 {.v = (const char*[]){ "/bin/dwm-bookmark", NULL } } },
	{ MODKEY|ShiftMask,							XK_x,      spawn,       	 SHCMD("awk -i inplace -v rmv=\"$(grep -v '^#' ~/.config/snippets | dmenu -i -l 50 | cut -d' ' -f1)\" '!index($0,rmv)' ~/.config/snippets") },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,							XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,  		 focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_l, 		 focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,							XK_p,      exitdwm,     	 {0} },
	{ MODKEY,												XK_q,      quit,           {1} }, 
	{ MODKEY|ShiftMask,             XK_Up,   	 spawn,          {.v = upvol   } },
	{ MODKEY|ShiftMask,             XK_Down,   spawn,          {.v = downvol } },
	{ MODKEY|ShiftMask|ControlMask, XK_m,      spawn,          {.v = mutevol } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

// autostart
static const char *const autostart[] = {
	"feh", "--bg-scale", "/usr/share/dwm/wallpaper.png", NULL,
	"killall", "dunst", NULL,
	"type", "dunst", "&&", "dunst", NULL, /* only launch dunst if the binary exists */
	"slstatus", NULL,
	NULL
};


