/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#666666";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#8696c6";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

// Old Auto-Tags from Xmonad
//
//myManageHook = composeAll
    //[className =? "MPlayer"        --> doFloat,
     //className =? "Gimp"           --> doFloat,
     //resource  =? "desktop_window" --> doIgnore,
     //resource  =? "kdesktop"       --> doIgnore,
     //className =? "Firefox"   --> doShift "4",
     //className =? "Dwb"   --> doShift "3",
     //className =? "Openscad"  --> doShift "7",
     //className =? "Eagle"     --> doShift "6",
     //className =? "guvcview"     --> doShift "6",
     //className =? "Guvcview"     --> doShift "6",
     //className =? "Gerbv"     --> doShift "7",
     //className =? "Fritzing"  --> doShift "6",
     //className =? "replicatorg-app-Base"   --> doShift "7",
     //className =? "Gvim"     --> doShift "2",     
     //className =? "Emacs"     --> doShift "2",     
     //className =? "Evince"    --> doShift "5",
     //className =? "Zathura"    --> doShift "5",
     //className =? "Skype"     --> doShift "7",
     //className =? "Gnumeric"  --> doShift "7",
     //className =? "VirtualBox"--> doShift "9",
     //className =? "Claws-mail" --> doShift "4",
     //className =? "Slic3r"  --> doShift "8"

 //]

/* tagging */
static const char *tags[] = { 
	"1: Tasks", 
	"2: Edit", 
	"3: Web", 
	"4: Mail", 
	"5: PDF", 
	"6: Design", 
	"7: Music", 
	"8: 3DP", 
	"9: Remote"
};
 
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       "tasks",       1 << 0,       False,       -1 },
		
	{ "Gvim",      NULL,       NULL,       1 << 1,       False,       -1 },

	{ "Firefox", "Navigator",  NULL,       1 << 2,       False,       -1 },
	{ "Dwb",      NULL,       NULL,       1 << 2,       False,       -1 },

	{ NULL,       NULL,       "imap",       1 << 3,       False,       -1 },
	{ NULL,       NULL,       "mutt",       1 << 3,       False,       -1 },
	{ "Claws-mail",     NULL,       NULL,       1 << 3,       False,       -1 },

	{ "Zathura",  NULL,       NULL,       1 << 4,       False,       -1 },
	{ "MuPDF",  NULL,       NULL,       1 << 4,       False,       -1 },

	{ "Eagle",    NULL,       NULL,       1 << 5,       False,       -1 },
	{"Inkscape",  NULL,	  NULL,	      1 << 5,       False,        +1 },
	{ "Gimp",     NULL,       NULL,       1 << 5,       True,        +1 },
	{ "Kicad",    NULL,       NULL,       1 << 5,       False,       -1 },

	{ NULL,       NULL,       "mpc",       1 << 6,       False,       -1 },

	{ NULL,    NULL,       "Slic3r",       1 << 7,       False,       -1 },
	{ NULL,    NULL,       "Pronterface",       1 << 7,       False,       -1 },
	{ "Openscad",    NULL,       NULL,       1 << 7,       False,       -1 },
	
	{ NULL,       NULL,       "twitter",       1 << 8,       False,       -1 },
	{ NULL,       NULL,       "preposterous",       1 << 8,       False,       -1 },
	{ "VirtualBox",       NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

#include "keepfloatingposition.c"

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
//static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };

static const char *dwb[] = { "dwb", NULL, NULL, NULL, "Dwb" };
static const char *firefox[] = { "firefox", NULL, NULL, NULL, "Mozilla Firefox" };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      runorraise,     {.v = dwb } },
	{ MODKEY|ShiftMask,              XK_d,      runorraise,     {.v = firefox } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_comma,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_period,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_i,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkMonNum,            0,              Button1,        focusmon,       {.i = +1} },
	{ ClkMonNum,            0,              Button3,        focusmon,       {.i = -1} },
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
