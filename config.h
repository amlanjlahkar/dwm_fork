/* appearance */
static const unsigned int borderpx      = 1;        /* border pixel of windows */
static const unsigned int gappx         = 8;        /* gaps between windows */
static const unsigned int snap          = 10;       /* snap pixel */
static const int showbar                = 1;        /* 0 means no bar */
static const int topbar                 = 1;        /* 0 means bottom bar */
static const int horizpadbar            = 10;       /* horizontal padding for statusbar */
static const int vertpadbar             = 16;       /* vertical padding for statusbar */
static const char *fonts[]              = { "Liberation Sans:style=Regular:size=8:antialias=true:autohint=true",
                                            "Noto Color Emoji:style=Regular:size=9",
                                            "Font Awesome 5 Free Solid:style=Solid:size=8" };

static const char col_statusbg[]        = "#e9ecef";
static const char col_statusfg[]        = "#495057";
static const char col_tagbg[]           = "#ced4da";
static const char col_aborder[]         = "#52b788";
static const char col_iborder[]         = "#343a40";
static const unsigned int baralpha      = 0xde;
static const unsigned int borderalpha   = 0xde;

static const char *colors[][3]      = {
    /*               fg            bg            border */
    [SchemeNorm] = { col_statusfg, col_statusbg, col_iborder },
    [SchemeSel]  = { col_statusfg, col_tagbg,    col_aborder },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg         border */
    [SchemeNorm] = { OPAQUE, baralpha,  borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha,  OPAQUE },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
    /* xprop(1):
     *   WM_CLASS(STRING) = instance, class
     *   WM_NAME(STRING) = title
     */

    /* class            instance        title           tags mask  isfloating   monitor */
    { "St",             NULL,           NULL,           0,         0,           -1 },
    { "alacritty",      NULL,           NULL,           0,         0,           -1 },
    { "Firefox",        "Navigator",    NULL,           2,         0,           -1 },
    { "Spacefm",        NULL,           NULL,           1 << 2,    0,           -1 },
    { "pinentry-qt",    NULL,           NULL,           0,         1,           -1 },
    { "Nsxiv",          "wallpapers",   NULL,           0,         1,           -1 },
    { "St",             "_spad",        NULL,           0,         1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol    arrange function */
    { "[]=",    tile    },    /* first entry is default */
    { "><>",    NULL    },    /* no layout function means floating behavior */
    { "[M]",    monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
    /* modifier                   key               function            argument */
    { ALTKEY,                     XK_b,             togglebar,          {0} },
    { MODKEY,                     XK_j,             focusstack,         {.i = +1 } },
    { MODKEY,                     XK_k,             focusstack,         {.i = -1 } },
    { MODKEY,                     XK_i,             incnmaster,         {.i = +1 } },
    { MODKEY,                     XK_d,             incnmaster,         {.i = -1 } },
    { MODKEY,                     XK_h,             setmfact,           {.f = -0.05} },
    { MODKEY,                     XK_l,             setmfact,           {.f = +0.05} },
    { MODKEY|ShiftMask,           XK_j,             movestack,          {.i = +1 } },
    { MODKEY|ShiftMask,           XK_k,             movestack,          {.i = -1 } },
    { MODKEY|ShiftMask,           XK_Return,        zoom,               {0} },
    { MODKEY,                     XK_Tab,           view,               {0} },
    { MODKEY|ShiftMask,           XK_c,             killclient,         {0} },
    { MODKEY,                     XK_t,             setlayout,          {.v = &layouts[0]} },
    { MODKEY,                     XK_f,             setlayout,          {.v = &layouts[1]} },
    { MODKEY,                     XK_m,             setlayout,          {.v = &layouts[2]} },
    { MODKEY,                     XK_space,         setlayout,          {0} },
    { MODKEY|ShiftMask,           XK_space,         togglefloating,     {0} },
    { MODKEY|ShiftMask,           XK_f,             togglefullscr,      {0} },
    { MODKEY,                     XK_0,             view,               {.ui = ~0 } },
    { MODKEY|ShiftMask,           XK_0,             tag,                {.ui = ~0 } },
    /* { MODKEY,                  XK_comma,         focusmon,           {.i = -1 } },
    { MODKEY,                     XK_period,        focusmon,           {.i = +1 } },
    { MODKEY|ShiftMask,           XK_comma,         tagmon,             {.i = -1 } },
    { MODKEY|ShiftMask,           XK_period,        tagmon,             {.i = +1 } }, */
    { MODKEY,                     XK_period,        shiftview,          {.i = +1 } },
    { MODKEY,                     XK_comma,         shiftview,          {.i = -1 } },
    { MODKEY,                     XK_minus,         scratchpad_show,    {0} },
    { MODKEY|ShiftMask,           XK_minus,         scratchpad_hide,    {0} },
    { MODKEY,                     XK_equal,         scratchpad_remove,  {0} },
    TAGKEYS(                      XK_1,             0)
    TAGKEYS(                      XK_2,             1)
    TAGKEYS(                      XK_3,             2)
    TAGKEYS(                      XK_4,             3)
    TAGKEYS(                      XK_5,             4)
    TAGKEYS(                      XK_6,             5)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click              event mask      button          function        argument */
    { ClkLtSymbol,        0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,        0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkStatusText,      0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,       MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,       MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,       MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,          0,              Button1,        view,           {0} },
    { ClkTagBar,          0,              Button3,        toggleview,     {0} },
    { ClkTagBar,          MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,          MODKEY,         Button3,        toggletag,      {0} },
};

