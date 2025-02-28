/* See LICENSE file for copyright and license details. */

/* Helper macros for spawning commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int swallowfloating         = 0;   /* 1 means swallow floating windows by default */
static const int scalepreview            = 4;        /* Tag preview scaling */
static int nomodbuttons                  = 1;   /* allow client mouse button bindings that have no modifier */
static const unsigned int gappih         = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 30;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int usealtbar               = 0;        /* 1 means use non-dwm status bar */
static const char *altbarclass           = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd             = "$HOME/bar.sh"; /* Alternate bar launch command */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab                 = showtab_auto;        /* Default tab bar show mode */
static const int toptab                  = False;               /* False means bottom tab bar */
static const int bar_height              = 0;   /* 0 means derive from font, >= 1 explicit height */
static int floatposgrid_x                = 5;  /* float grid columns */
static int floatposgrid_y                = 5;  /* float grid rows */
static const char slopspawnstyle[]       = "-t 0 -c 0.92,0.85,0.69,0.3 -o"; /* do NOT define -f (format) here */
static const char slopresizestyle[]      = "-t 0 -c 0.92,0.85,0.69,0.3"; /* do NOT define -f (format) here */
static const int riodraw_borders         = 0;  /* 0 or 1, indicates whether the area drawn using slop includes the window borders */
static const int riodraw_matchpid        = 1;  /* 0 or 1, indicates whether to match the PID of the client that was spawned with riospawn */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = -1;
static const unsigned int systrayspacing = 9;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

/* The format in which the tag is written when named. E.g. %d: %.12s will write the tag number
 * followed the first 12 characters of the given string. You can also just use "%d: %s" here. */
#define NAMETAG_FORMAT "%d: %.12s"
/* The maximum amount of bytes reserved for each tag text. */
#define MAX_TAGLEN 16
/* The command to run (via popen). This can be tailored by adding a prompt, passing other command
 * line arguments or providing name options. Optionally you can use other dmenu like alternatives
 * like rofi -dmenu. */
#define NAMETAG_COMMAND "dmenu < /dev/null"

/* alt-tab configuration */
static const unsigned int tabmodkey        = 0x40; /* (Alt) when this key is held down the alt-tab functionality stays active. Must be the same modifier as used to run alttabstart */
static const unsigned int tabcyclekey      = 0x17; /* (Tab) when this key is hit the menu moves one position forward in client stack. Must be the same key as used to run alttabstart */
static const unsigned int tabposy          = 1;    /* tab position on Y axis, 0 = top, 1 = center, 2 = bottom */
static const unsigned int tabposx          = 1;    /* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxwtab          = 600;  /* tab menu width */
static const unsigned int maxhtab          = 200;  /* tab menu height */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char font[]                 = "Liberation Mono 10";
static const char dmenufont[]            = "Liberation Mono:size=10";


static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#ffffff"; // Normal bar text color (foreground).
static char normbgcolor[]                = "#000000"; // Normal bar background color.
static char normbordercolor[]            = "#000000"; // Normal border color (not used in the snippet).
static char normfloatcolor[]             = "#01d080"; // Normal floating window color.

static char selfgcolor[]                 = "#930000"; // Selected window text color (foreground).
static char selbgcolor[]                 = "#000000"; // Selected window background color.
static char selbordercolor[]             = "#ffffff"; // Selected window border color.
static char selfloatcolor[]              = "#005577"; // Selected floating window color.

static char titlenormfgcolor[]           = "#000000"; // Normal title bar text color (foreground).
static char titlenormbgcolor[]           = "#ffffff"; // Normal title bar background color.
static char titlenormbordercolor[]       = "#ffffff"; // Normal title bar border color.
static char titlenormfloatcolor[]        = "#ffffff"; // Normal title bar color for floating windows.

static char titleselfgcolor[]            = "#000000"; // Selected title bar text color (foreground).
static char titleselbgcolor[]            = "#ffffff"; // Selected title bar background color.
static char titleselbordercolor[]        = "#ffffff"; // Selected title bar border color.
static char titleselfloatcolor[]         = "#ffffff"; // Selected title bar color for floating windows.

static char tagsnormfgcolor[]            = "#000000"; // Normal tag text color (foreground).
static char tagsnormbgcolor[]            = "#ffffff"; // Normal tag background color.
static char tagsnormbordercolor[]        = "#930000"; // Normal tag border color.
static char tagsnormfloatcolor[]         = "#ffffff"; // Normal tag color for floating windows.

static char tagsselfgcolor[]             = "#000000"; // Selected tag text color (foreground).
static char tagsselbgcolor[]             = "#ffffff"; // Selected tag background color.
static char tagsselbordercolor[]         = "#000000"; // Selected tag border color.
static char tagsselfloatcolor[]          = "#000000"; // Selected tag color for floating windows.

static char hidnormfgcolor[]             = "#005577"; // Hidden window text color (foreground).
static char hidselfgcolor[]              = "#000000"; // Hidden selected window text color (foreground).
static char hidnormbgcolor[]             = "#222222"; // Hidden window background color.
static char hidselbgcolor[]              = "#222222"; // Hidden selected window background color.

static char urgfgcolor[]                 = "#bbbbbb"; // Urgent window text color (foreground).
static char urgbgcolor[]                 = "#222222"; // Urgent window background color.
static char urgbordercolor[]             = "#ff0000"; // Urgent window border color.
static char urgfloatcolor[]              = "#db8fd9"; // Urgent window color for floating windows.

static char scratchselfgcolor[]          = "#FFF7D4";
static char scratchselbgcolor[]          = "#77547E";
static char scratchselbordercolor[]      = "#894B9F";
static char scratchselfloatcolor[]       = "#894B9F";

static char scratchnormfgcolor[]         = "#FFF7D4";
static char scratchnormbgcolor[]         = "#664C67";
static char scratchnormbordercolor[]     = "#77547E";
static char scratchnormfloatcolor[]      = "#77547E";

static char normTTBbgcolor[]             = "#000000";
static char normLTRbgcolor[]             = "#000000";
static char normMONObgcolor[]            = "#000033";
static char normGRIDbgcolor[]            = "#ffffff";
static char normGRD1bgcolor[]            = "#ffffff";
static char normGRD2bgcolor[]            = "#003300";
static char normGRDMbgcolor[]            = "#ffffff";
static char normHGRDbgcolor[]            = "#ffffff";
static char normDWDLbgcolor[]            = "#000000";
static char normSPRLbgcolor[]            = "#000000";
static char normfloatbgcolor[]           = "#000000";
static char actTTBbgcolor[]              = "#000000";
static char actLTRbgcolor[]              = "#000000";
static char actMONObgcolor[]             = "#000000";
static char actGRIDbgcolor[]             = "#000000";
static char actGRD1bgcolor[]             = "#000000";
static char actGRD2bgcolor[]             = "#000000";
static char actGRDMbgcolor[]             = "#000000";
static char actHGRDbgcolor[]             = "#000000";
static char actDWDLbgcolor[]             = "#000000";
static char actSPRLbgcolor[]             = "#000000";
static char actfloatbgcolor[]            = "#000000";
static char selTTBbgcolor[]              = "#ffffff";
static char selLTRbgcolor[]              = "#000000";
static char selMONObgcolor[]             = "#000000";
static char selGRIDbgcolor[]             = "#000000";
static char selGRD1bgcolor[]             = "#000000";
static char selGRD2bgcolor[]             = "#000000";
static char selGRDMbgcolor[]             = "#000000";
static char selHGRDbgcolor[]             = "#000000";
static char selDWDLbgcolor[]             = "#000000";
static char selSPRLbgcolor[]             = "#000000";
static char selfloatbgcolor[]            = "#000000";

static const unsigned int baralpha = 0;
static const unsigned int borderalpha = 0;
static const unsigned int alphas[][3] = {
	/*                       fg      bg        border     */
	[SchemeNorm]         = { OPAQUE, baralpha, OPAQUE },
	[SchemeSel]          = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleNorm]    = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleSel]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidNorm]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidSel]       = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]          = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActTTB]   = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActLTR]   = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActMONO]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActGRID]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActGRD1]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActGRD2]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActGRDM]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActHGRD]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActDWDL]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActSPRL]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexActFloat] = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaTTB]   = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaLTR]   = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaMONO]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaGRID]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaGRD1]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaGRD2]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaGRDM]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaHGRD]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaDWDL]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaSPRL]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexInaFloat] = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelTTB]   = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelLTR]   = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelMONO]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelGRID]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelGRD1]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelGRD2]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelGRDM]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelHGRD]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelDWDL]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelSPRL]  = { OPAQUE, baralpha, borderalpha },
	[SchemeFlexSelFloat] = { OPAQUE, baralpha, borderalpha },
};
static const char title_bg_dark[]   = "#303030";
static const char title_bg_light[]  = "#fdfdfd";
static const int color_ptrs[][ColCount] = {

        /*                       fg      bg      border  float */
  
	[SchemeNorm]         = { -1,     0,      0,       7 }, // normfgcolor, normbgcolor, normbordercolor, normfloatcolork
	[SchemeSel]          = { -1,     -1,     -1,     10 }, // selfgcolor,  selbgcolor,  selbordercolor,  selfloatcolor
	[SchemeTitleNorm]    = { 6,      -1,     -1,     -1 }, // titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor
	[SchemeTitleSel]     = { 12,     -1,     -1,      -1 }, // titleselfgcolor, titleselbgcolor, titleselbordercolor, titleselfloatcolor
	[SchemeTagsNorm]     = { 7,      0,      0,      -1 }, // tagsnormfgcolor, tagsnormbgcolor, tagsnormbordercolor, tagsnormfloatcolor
	[SchemeTagsSel]      = { 0,     -1,      -1,     -1 }, // tagsselfgcolor, tagsselbgcolor,   tagsselbordercolor, tagsselfloatcolor
	[SchemeHidNorm]      = { 5,      0,      0,      -1 }, // hidnormfgcolor, hidnormbgcolor, c000000,  c000000
	[SchemeHidSel]       = { 6,      -1,     -1,     -1 }, // urgfgcolor, urgbgcolor, urgbordercolor, urgfloatcolor
	[SchemeUrg]          = { 9,      0,      9,      15 }, // urgfgcolor, urgbgcolor, urgbordercolor, urgfloatcolor

};

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
	[SchemeScratchSel]  = { scratchselfgcolor, scratchselbgcolor, scratchselbordercolor, scratchselfloatcolor },
	[SchemeScratchNorm] = { scratchnormfgcolor, scratchnormbgcolor, scratchnormbordercolor, scratchnormfloatcolor },
	[SchemeFlexActTTB]   = { titleselfgcolor,  actTTBbgcolor,    actTTBbgcolor,        c000000 },
	[SchemeFlexActLTR]   = { titleselfgcolor,  actLTRbgcolor,    actLTRbgcolor,        c000000 },
	[SchemeFlexActMONO]  = { titleselfgcolor,  actMONObgcolor,   actMONObgcolor,       c000000 },
	[SchemeFlexActGRID]  = { titleselfgcolor,  actGRIDbgcolor,   actGRIDbgcolor,       c000000 },
	[SchemeFlexActGRD1]  = { titleselfgcolor,  actGRD1bgcolor,   actGRD1bgcolor,       c000000 },
	[SchemeFlexActGRD2]  = { titleselfgcolor,  actGRD2bgcolor,   actGRD2bgcolor,       c000000 },
	[SchemeFlexActGRDM]  = { titleselfgcolor,  actGRDMbgcolor,   actGRDMbgcolor,       c000000 },
	[SchemeFlexActHGRD]  = { titleselfgcolor,  actHGRDbgcolor,   actHGRDbgcolor,       c000000 },
	[SchemeFlexActDWDL]  = { titleselfgcolor,  actDWDLbgcolor,   actDWDLbgcolor,       c000000 },
	[SchemeFlexActSPRL]  = { titleselfgcolor,  actSPRLbgcolor,   actSPRLbgcolor,       c000000 },
	[SchemeFlexActFloat] = { titleselfgcolor,  actfloatbgcolor,  actfloatbgcolor,      c000000 },
	[SchemeFlexInaTTB]   = { titlenormfgcolor, normTTBbgcolor,   normTTBbgcolor,       c000000 },
	[SchemeFlexInaLTR]   = { titlenormfgcolor, normLTRbgcolor,   normLTRbgcolor,       c000000 },
	[SchemeFlexInaMONO]  = { titlenormfgcolor, normMONObgcolor,  normMONObgcolor,      c000000 },
	[SchemeFlexInaGRID]  = { titlenormfgcolor, normGRIDbgcolor,  normGRIDbgcolor,      c000000 },
	[SchemeFlexInaGRD1]  = { titlenormfgcolor, normGRD1bgcolor,  normGRD1bgcolor,      c000000 },
	[SchemeFlexInaGRD2]  = { titlenormfgcolor, normGRD2bgcolor,  normGRD2bgcolor,      c000000 },
	[SchemeFlexInaGRDM]  = { titlenormfgcolor, normGRDMbgcolor,  normGRDMbgcolor,      c000000 },
	[SchemeFlexInaHGRD]  = { titlenormfgcolor, normHGRDbgcolor,  normHGRDbgcolor,      c000000 },
	[SchemeFlexInaDWDL]  = { titlenormfgcolor, normDWDLbgcolor,  normDWDLbgcolor,      c000000 },
	[SchemeFlexInaSPRL]  = { titlenormfgcolor, normSPRLbgcolor,  normSPRLbgcolor,      c000000 },
	[SchemeFlexInaFloat] = { titlenormfgcolor, normfloatbgcolor, normfloatbgcolor,     c000000 },
	[SchemeFlexSelTTB]   = { titleselfgcolor,  selTTBbgcolor,    selTTBbgcolor,        c000000 },
	[SchemeFlexSelLTR]   = { titleselfgcolor,  selLTRbgcolor,    selLTRbgcolor,        c000000 },
	[SchemeFlexSelMONO]  = { titleselfgcolor,  selMONObgcolor,   selMONObgcolor,       c000000 },
	[SchemeFlexSelGRID]  = { titleselfgcolor,  selGRIDbgcolor,   selGRIDbgcolor,       c000000 },
	[SchemeFlexSelGRD1]  = { titleselfgcolor,  selGRD1bgcolor,   selGRD1bgcolor,       c000000 },
	[SchemeFlexSelGRD2]  = { titleselfgcolor,  selGRD2bgcolor,   selGRD2bgcolor,       c000000 },
	[SchemeFlexSelGRDM]  = { titleselfgcolor,  selGRDMbgcolor,   selGRDMbgcolor,       c000000 },
	[SchemeFlexSelHGRD]  = { titleselfgcolor,  selHGRDbgcolor,   selHGRDbgcolor,       c000000 },
	[SchemeFlexSelDWDL]  = { titleselfgcolor,  selDWDLbgcolor,   selDWDLbgcolor,       c000000 },
	[SchemeFlexSelSPRL]  = { titleselfgcolor,  selSPRLbgcolor,   selSPRLbgcolor,       c000000 },
	[SchemeFlexSelFloat] = { titleselfgcolor,  selfloatbgcolor,  selfloatbgcolor,      c000000 },
};

static char *statuscolors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

static const char *layoutmenu_cmd = "layoutmenu.sh";

static const Launcher launchers[] = {
	/* icon to display      command        */
    { "i",               CMD("tabbed", "-e", "surf") },
	{ "t",               CMD("st") },	
};

static const char *const autostart[] = {
  	"pkill", "-f", "dunst", NULL,
  	"pkill", "-f", "jamesdsp", NULL,
   	"pkill", "-f", "jamesdsp", NULL,
    "pkill", "-f", "riseup", NULL,
    "pkill", "-f", "riseup", NULL,
    "spmenu", "-cu", NULL,	
    "emacs", "--daemon", NULL,
    "systemctl", "--user", "enable", "--now", "hintsd", NULL,
    "picom", NULL,
    "nitrogen", "--restore", NULL,
  	"dwmbar", NULL,
	"bumbaclot", NULL,
	"xban", NULL,
	"sxhkd", NULL,	
  	"pasystray", NULL, 
	"nm-applet", NULL,
	"vesktop", NULL,
	"jamesdsp", NULL,
	NULL	
};

static const char *scratchpadcmd[] = {"s", "st", "-n", "spterm", NULL};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char tagicons[][NUMTAGS][MAX_TAGLEN] =
{
	[DEFAULT_TAGS]        = { "ª♀", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "Firefox", .tags = 1 << 7)
	RULE(.instance = "spterm", .scratchkey = 's', .isfloating = 1)
};

static const MonitorRule monrules[] = {
	/* monitor  tag   layout  mfact  nmaster  showbar  topbar */
	{  1,       -1,   2,      -1,    -1,      -1,      -1     }, // use a different layout for the second monitor
	{  -1,      -1,   0,      -1,    -1,      -1,      -1     }, // default
};

static const Inset default_inset = {
	.x = 0,
	.y = 0,
	.w = 0,
	.h = 0,
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_launcher,           draw_launcher,          click_launcher,          NULL,                    "launcher" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status2d,           draw_status2d,          click_statuscmd,         NULL,                    "status2d" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_xkb,                draw_xkb,               click_xkb,               NULL,                    "xkb" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_flexwintitle,       draw_flexwintitle,      click_flexwintitle,      NULL,                    "flexwintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int nstack      = 0;    /* number of clients in primary stack area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#define FORCE_VSPLIT 1

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */
/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

static const Layout layouts[] = {
	/* symbol     arrange function, { nmaster, nstack, layout, master axis, stack axis, secondary stack axis, symbol func } */
	{ "[]=",      flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL } }, // default tile layout
 	{ "><>",      NULL,             {0} },    /* no layout function means floating behavior */
	{ "[M]",      flextile,         { -1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL } }, // monocle
	{ "|||",      flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // columns (col) layout
	{ ">M>",      flextile,         { -1, -1, FLOATING_MASTER, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // floating master
	{ "[D]",      flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL } }, // deck
	{ "TTT",      flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // bstack
	{ "===",      flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // bstackhoriz
	{ "|M|",      flextile,         { -1, -1, SPLIT_CENTERED_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, TOP_TO_BOTTOM, NULL } }, // centeredmaster
	{ "-M-",      flextile,         { -1, -1, SPLIT_CENTERED_HORIZONTAL, TOP_TO_BOTTOM, LEFT_TO_RIGHT, LEFT_TO_RIGHT, NULL } }, // centeredmaster horiz
	{ ":::",      flextile,         { -1, -1, NO_SPLIT, GAPPLESSGRID, GAPPLESSGRID, 0, NULL } }, // gappless grid
	{ "[\\]",     flextile,         { -1, -1, NO_SPLIT, DWINDLE, DWINDLE, 0, NULL } }, // fibonacci dwindle
	{ "(@)",      flextile,         { -1, -1, NO_SPLIT, SPIRAL, SPIRAL, 0, NULL } }, // fibonacci spiral
	{ "[T]",      flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TATAMI, 0, NULL } }, // tatami mats
	{ "[]=",      tile,             {0} },
	{ "[M]",      monocle,          {0} },
	{ "TTT",      bstack,           {0} },
	{ "===",      bstackhoriz,      {0} },
	{ "|M|",      centeredmaster,   {0} },
	{ ">M>",      centeredfloatingmaster, {0} },
	{ "|||",      col,              {0} },
	{ "[D]",      deck,             {0} },
	{ "(@)",      spiral,           {0} },
	{ "[\\]",     dwindle,          {0} },
	{ "HHH",      grid,             {0} },
	{ "---",      horizgrid,        {0} },
	{ ":::",      gaplessgrid,      {0} },
	{ "###",      nrowgrid,         {0} },
};

/* xkb frontend */
static const char *xkb_layouts[]  = {
	"en",
	"ru",
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod4Mask|ShiftMask,    KEY,      swaptags,       {.ui = 1 << TAG} },

/* commands */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};

static const char *dmenucmd2[] = {
  "spmenu", NULL
};

static const char *spmenu[] = { "spmenu", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *aupup[] = { "playerctl", "--player=mpd,spotify,%any,chromium", "volume", "0.1+", NULL };
static const char *sendgrave[] = { "xdotool", "key", "grave", NULL };
static const char *aupdwn[] = { "playerctl", "--player=mpd,spotify,%any,chromium", "volume", "0.1-", NULL };
static const char *aupplay[] = { "playerctl", "--player=mpd,spotify,%any,chromium", "play-pause", NULL };

static const char *austop[] = { "playerctl", "--player=mpd,spotify,%any,chromium", "stop", NULL };
static const char *auprev[] = { "playerctl", "--player=mpd,spotify,%any,chromium", "previous", NULL } ;
static const char *aunext[] = { "playerctl", "--player=mpd,spotify,%any,chromium", "next", NULL } ;

static const char *volup[] =  { "amixer", "-D", "pulse", "sset", "Master", "5%+", NULL};
static const char *voldown[] =  { "amixer", "-D", "pulse", "sset", "Master", "5%-", NULL};
static const char *brightnessu[]   = { "brightnessctl", "set", "20%+", NULL };
static const char *brightnessd[] = { "brightnessctl",  "set", "20%-", NULL };
static const char *rofiwin[] = { "rofi", "-show", "window", NULL };
static const char *slock[] = { "slock", NULL };

static const char *printscr[] = { "spectacle", "-r", NULL };

//static const char *termcmd[]  = { "st", NULL };

static const char *rofi[] = { "rofi", "-show", "drun", NULL };

/* This defines the name of the executable that handles the bar (used for signalling purposes) */
#define STATUSBAR "dwmblocks"

static const Key keys[] = {
	/* modifier                     key            function                argument */
  	{ 0,                            XF86XK_AudioLowerVolume,  spawn,        {.v = voldown }},
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,        {.v = volup }},
	{ MODKEY,                       XF86XK_AudioRaiseVolume,  spawn,        {.v = aupup }},
	{ MODKEY,                       XF86XK_AudioLowerVolume,  spawn,        {.v = aupdwn }},
	{ 0,                            XF86XK_AudioPlay,         spawn,        {.v = aupplay }},
	{ 0,                            XF86XK_AudioStop,         spawn,        {.v = austop }},
	{ 0,                            XF86XK_AudioPrev,         spawn,        {.v = auprev }},
	{ 0,                            XF86XK_AudioNext,         spawn,        {.v = aunext }}, 
    //	{ MODKEY,                       XK_grave,                 spawn,        {.v = sendgrave }},
	{ 0,				XF86XK_MonBrightnessUp,   spawn,	{.v = brightnessu }},
	{ 0,				XF86XK_MonBrightnessDown, spawn,	{.v = brightnessd }},
	{ 0,                            XK_Print,                 spawn,        {.v = printscr }},
	{ ControlMask|MODKEY,           XK_l,                     spawn,        {.v = slock    }},
	{ 0,                            XK_Super_L,          spawn,                  {.v = dmenucmd2 } },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,                  {.v = termcmd } },
	//	{ MODKEY|ControlMask,           XK_p,          riospawnsync,           {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_Return,     riospawn,               {.v = termcmd } },
	{ MODKEY,                       XK_s,          rioresize,              {0} },
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY|ShiftMask,             XK_b,          toggletopbar,           {0} },
	{ MODKEY|ControlMask,           XK_b,          tabmode,                {-1} },
	{ MODKEY|ControlMask,           XK_space,      focusmaster,            {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_Left,       focusdir,               {.i = 0 } }, // left
	{ MODKEY,                       XK_Right,      focusdir,               {.i = 1 } }, // right
	{ MODKEY,                       XK_Up,         focusdir,               {.i = 2 } }, // up
	{ MODKEY,                       XK_Down,       focusdir,               {.i = 3 } }, // down
	{ MODKEY|ControlMask,           XK_Left,       placedir,               {.i = 0 } }, // left
	{ MODKEY|ControlMask,           XK_Right,      placedir,               {.i = 1 } }, // right
	{ MODKEY|ControlMask,           XK_Up,         placedir,               {.i = 2 } }, // up
	{ MODKEY|ControlMask,           XK_Down,       placedir,               {.i = 3 } }, // down
	{ MODKEY,                       XK_s,          swapfocus,              {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_j,          rotatestack,            {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_k,          rotatestack,            {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_j,          inplacerotate,          {.i = +2 } }, // same as rotatestack
	{ MODKEY|Mod4Mask,              XK_k,          inplacerotate,          {.i = -2 } }, // same as reotatestack
	{ MODKEY|Mod4Mask|ShiftMask,    XK_j,          inplacerotate,          {.i = +1} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_k,          inplacerotate,          {.i = -1} },
	{ MODKEY|ControlMask,           XK_j,          pushdown,               {0} },
	{ MODKEY|ControlMask,           XK_k,          pushup,                 {0} },
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_i,          incnstack,              {.i = +1 } },
	{ MODKEY|ControlMask,           XK_u,          incnstack,              {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,          setcfact,               {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_e,          aspectresize,           {.i = +24} },
	{ MODKEY|ControlMask|ShiftMask, XK_r,          aspectresize,           {.i = -24} },
	{ MODKEY|Mod4Mask,              XK_Down,       moveresize,             {.v = "0x 25y 0w 0h" } },
	{ MODKEY|Mod4Mask,              XK_Up,         moveresize,             {.v = "0x -25y 0w 0h" } },
	{ MODKEY|Mod4Mask,              XK_Right,      moveresize,             {.v = "25x 0y 0w 0h" } },
	{ MODKEY|Mod4Mask,              XK_Left,       moveresize,             {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Down,       moveresize,             {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Up,         moveresize,             {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Right,      moveresize,             {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Left,       moveresize,             {.v = "0x 0y -25w 0h" } },
	//	{ MODKEY,                       XK_x,          transfer,               {0} },
	//	{ MODKEY|ControlMask,           XK_x,          transferall,            {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_a,          updateinset,            {.v = &default_inset } },
	{ MODKEY,                       XK_Return,     zoom,                   {0} },
	{ MODKEY|Mod4Mask,              XK_u,          incrgaps,               {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,          incrigaps,              {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,          incrogaps,              {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,          togglegaps,             {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	{ Mod1Mask,                     XK_Tab,        spawn,            {.v = rofiwin } },
	{ MODKEY|ShiftMask,             XK_Left,       shifttag,               { .i = -1 } }, // note keybinding conflict with focusadjacenttag tagtoleft
	{ MODKEY|ShiftMask,             XK_Right,      shifttag,               { .i = +1 } }, // note keybinding conflict with focusadjacenttag tagtoright
	{ MODKEY|ShiftMask|ControlMask, XK_Left,       shifttagclients,        { .i = -1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_Right,      shifttagclients,        { .i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,       shiftboth,              { .i = -1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoleft placedir
	{ MODKEY|ControlMask,           XK_Right,      shiftboth,              { .i = +1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoright placedir
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Left,       shiftswaptags,          { .i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_Right,      shiftswaptags,          { .i = +1 } },
	{ MODKEY|ControlMask,           XK_z,          showhideclient,         {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_x,          killunsel,              {0} },
	{ MODKEY|ShiftMask,             XK_r,          self_restart,           {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {1} },
	{ MODKEY,                       XK_u,          focusurgent,            {0} },
	{ MODKEY,                       XK_o,          winview,                {0} },
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,          setlayout,              {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_t,          rotatelayoutaxis,       {.i = +1 } },   /* flextile, 1 = layout axis */
	{ MODKEY|ControlMask,           XK_Tab,        rotatelayoutaxis,       {.i = +2 } },   /* flextile, 2 = master axis */
	{ MODKEY|ControlMask|ShiftMask, XK_Tab,        rotatelayoutaxis,       {.i = +3 } },   /* flextile, 3 = stack axis */
	{ MODKEY|ControlMask|Mod1Mask,  XK_Tab,        rotatelayoutaxis,       {.i = +4 } },   /* flextile, 4 = secondary stack axis */
	{ MODKEY|Mod5Mask,              XK_t,          rotatelayoutaxis,       {.i = -1 } },   /* flextile, 1 = layout axis */
	{ MODKEY|Mod5Mask,              XK_Tab,        rotatelayoutaxis,       {.i = -2 } },   /* flextile, 2 = master axis */
	{ MODKEY|Mod5Mask|ShiftMask,    XK_Tab,        rotatelayoutaxis,       {.i = -3 } },   /* flextile, 3 = stack axis */
	{ MODKEY|Mod5Mask|Mod1Mask,     XK_Tab,        rotatelayoutaxis,       {.i = -4 } },   /* flextile, 4 = secondary stack axis */
	{ MODKEY|ControlMask,           XK_Return,     mirrorlayout,           {0} },          /* flextile, flip master and stack areas */
	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_h,          togglehorizontalmax,    {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,          togglehorizontalmax,    {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_j,          toggleverticalmax,      {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,          toggleverticalmax,      {0} },
	{ MODKEY|ControlMask,           XK_m,          togglemax,              {0} },
	{ MODKEY|ShiftMask,             XK_Escape,     togglenomodbuttons,     {0} },
    //	{ MODKEY,                       XK_grave,      togglescratch,          {.v = scratchpadcmd } },
    //	{ MODKEY|ControlMask,           XK_grave,      setscratch,             {.v = scratchpadcmd } },
    //	{ MODKEY|ShiftMask,             XK_grave,      removescratch,          {.v = scratchpadcmd } },
	{ MODKEY|Mod4Mask,              XK_space,      unfloatvisible,         {0} },
	{ MODKEY|ShiftMask,             XK_t,          unfloatvisible,         {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,          fullscreen,             {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,           {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
	//	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	//	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	//	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	//	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	//	{ MODKEY|Mod4Mask|ShiftMask,    XK_comma,      tagallmon,              {.i = +1 } },
	//	{ MODKEY|Mod4Mask|ShiftMask,    XK_period,     tagallmon,              {.i = -1 } },
	//	{ MODKEY|Mod4Mask|ControlMask,  XK_comma,      tagswapmon,             {.i = +1 } },
	//	{ MODKEY|Mod4Mask|ControlMask,  XK_period,     tagswapmon,             {.i = -1 } },
	{ MODKEY,                       XK_n,          togglealttag,           {0} },
	{ MODKEY|ShiftMask,             XK_n,          nametag,                {0} },
	/* Note that due to key limitations the below example kybindings are defined with a Mod3Mask,
	 * which is not always readily available. Refer to the patch wiki for more details. */
	/* Client position is limited to monitor window area */
	{ Mod3Mask,                     XK_u,            floatpos,               {.v = "-26x -26y" } }, // ↖
	{ Mod3Mask,                     XK_i,            floatpos,               {.v = "  0x -26y" } }, // ↑
	{ Mod3Mask,                     XK_o,            floatpos,               {.v = " 26x -26y" } }, // ↗
	{ Mod3Mask,                     XK_j,            floatpos,               {.v = "-26x   0y" } }, // ←
	{ Mod3Mask,                     XK_l,            floatpos,               {.v = " 26x   0y" } }, // →
	{ Mod3Mask,                     XK_m,            floatpos,               {.v = "-26x  26y" } }, // ↙
	//	{ Mod3Mask,                     XK_comma,        floatpos,               {.v = "  0x  26y" } }, // ↓
	//	{ Mod3Mask,                     XK_period,       floatpos,               {.v = " 26x  26y" } }, // ↘
	/* Absolute positioning (allows moving windows between monitors) */
	{ Mod3Mask|ControlMask,         XK_u,            floatpos,               {.v = "-26a -26a" } }, // ↖
	{ Mod3Mask|ControlMask,         XK_i,            floatpos,               {.v = "  0a -26a" } }, // ↑
	{ Mod3Mask|ControlMask,         XK_o,            floatpos,               {.v = " 26a -26a" } }, // ↗
	{ Mod3Mask|ControlMask,         XK_j,            floatpos,               {.v = "-26a   0a" } }, // ←
	{ Mod3Mask|ControlMask,         XK_l,            floatpos,               {.v = " 26a   0a" } }, // →
	{ Mod3Mask|ControlMask,         XK_m,            floatpos,               {.v = "-26a  26a" } }, // ↙
	//	{ Mod3Mask|ControlMask,         XK_comma,        floatpos,               {.v = "  0a  26a" } }, // ↓
	//	{ Mod3Mask|ControlMask,         XK_period,       floatpos,               {.v = " 26a  26a" } }, // ↘
	/* Resize client, client center position is fixed which means that client expands in all directions */
	{ Mod3Mask|ShiftMask,           XK_u,            floatpos,               {.v = "-26w -26h" } }, // ↖
	{ Mod3Mask|ShiftMask,           XK_i,            floatpos,               {.v = "  0w -26h" } }, // ↑
	{ Mod3Mask|ShiftMask,           XK_o,            floatpos,               {.v = " 26w -26h" } }, // ↗
	{ Mod3Mask|ShiftMask,           XK_j,            floatpos,               {.v = "-26w   0h" } }, // ←
	{ Mod3Mask|ShiftMask,           XK_k,            floatpos,               {.v = "800W 800H" } }, // ·
	{ Mod3Mask|ShiftMask,           XK_l,            floatpos,               {.v = " 26w   0h" } }, // →
	{ Mod3Mask|ShiftMask,           XK_m,            floatpos,               {.v = "-26w  26h" } }, // ↙
	//	{ Mod3Mask|ShiftMask,           XK_comma,        floatpos,               {.v = "  0w  26h" } }, // ↓
	//	{ Mod3Mask|ShiftMask,           XK_period,       floatpos,               {.v = " 26w  26h" } }, // ↘
	/* Client is positioned in a floating grid, movement is relative to client's current position */
	{ Mod3Mask|Mod1Mask,            XK_u,            floatpos,               {.v = "-1p -1p" } }, // ↖
	{ Mod3Mask|Mod1Mask,            XK_i,            floatpos,               {.v = " 0p -1p" } }, // ↑
	{ Mod3Mask|Mod1Mask,            XK_o,            floatpos,               {.v = " 1p -1p" } }, // ↗
	{ Mod3Mask|Mod1Mask,            XK_j,            floatpos,               {.v = "-1p  0p" } }, // ←
	{ Mod3Mask|Mod1Mask,            XK_k,            floatpos,               {.v = " 0p  0p" } }, // ·
	{ Mod3Mask|Mod1Mask,            XK_l,            floatpos,               {.v = " 1p  0p" } }, // →
	{ Mod3Mask|Mod1Mask,            XK_m,            floatpos,               {.v = "-1p  1p" } }, // ↙
	//	{ Mod3Mask|Mod1Mask,            XK_comma,        floatpos,               {.v = " 0p  1p" } }, // ↓
	//	{ Mod3Mask|Mod1Mask,            XK_period,       floatpos,               {.v = " 1p  1p" } }, // ↘
	{ MODKEY|ControlMask,           XK_minus,      setborderpx,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_plus,       setborderpx,            {.i = +1 } },
	{ MODKEY|ControlMask,           XK_numbersign, setborderpx,            {.i = 0 } },
	//	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,            {.i = -1 } },
	//	{ MODKEY|ControlMask,           XK_period,     cyclelayout,            {.i = +1 } },
	//	TAGKEYS(                        XK_1,                                  0)
	//	TAGKEYS(                        XK_2,                                  1)
	//	TAGKEYS(                        XK_3,                                  2)
	//	TAGKEYS(                        XK_4,                                  3)
	//	TAGKEYS(                        XK_5,                                  4)
	//	TAGKEYS(                        XK_6,                                  5)
	//	TAGKEYS(                        XK_7,                                  6)
	//	TAGKEYS(                        XK_8,                                  7)
	//	TAGKEYS(                        XK_9,                                  8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */

	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,                   Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,                   Button3,        showhideclient, {0} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,                   Button2,        sigstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,                   Button3,        sigstatusbar,   {.i = 3 } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,              Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,              Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,              Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,              Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button3,        dragcfact,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button1,        dragmfact,      {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,                   Button1,        focuswin,       {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static const Signal signals[] = {
	/* signum                    function */
	{ "focusstack",              focusstack },
	{ "setmfact",                setmfact },
	{ "togglebar",               togglebar },
	{ "toggletopbar",            toggletopbar },
	{ "incnmaster",              incnmaster },
	{ "togglefloating",          togglefloating },
	{ "focusmon",                focusmon },
	{ "floatpos",                floatpos },
	{ "focusurgent",             focusurgent },
	{ "swapfocus",               swapfocus },
	{ "rotatestack",             rotatestack },
	{ "inplacerotate",           inplacerotate },
	{ "pushdown",                pushdown },
	{ "pushup",                  pushup },
	{ "incnstack",               incnstack },
	{ "rotatelayoutaxis",        rotatelayoutaxis },
	{ "setlayoutaxisex",         setlayoutaxisex },
	{ "mirrorlayout",            mirrorlayout },
	{ "setcfact",                setcfact },
	{ "nametag",                 nametag },
	{ "transfer",                transfer },
	{ "transferall",             transferall },
	{ "tagmon",                  tagmon },
	{ "zoom",                    zoom },
	{ "incrgaps",                incrgaps },
	{ "incrigaps",               incrigaps },
	{ "incrogaps",               incrogaps },
	{ "incrihgaps",              incrihgaps },
	{ "incrivgaps",              incrivgaps },
	{ "incrohgaps",              incrohgaps },
	{ "incrovgaps",              incrovgaps },
	{ "togglegaps",              togglegaps },
	{ "defaultgaps",             defaultgaps },
	{ "setgaps",                 setgapsex },
	{ "view",                    view },
	{ "viewall",                 viewallex },
	{ "viewex",                  viewex },
	{ "toggleview",              toggleview },
	{ "showhideclient",          showhideclient },
	{ "shiftboth",               shiftboth },
	{ "shifttag",                shifttag },
	{ "shifttagclients",         shifttagclients },
	{ "shiftswaptags",           shiftswaptags },
	{ "self_restart",            self_restart },
	{ "togglesticky",            togglesticky },
	{ "setborderpx",             setborderpx },
	{ "cyclelayout",             cyclelayout },
	{ "toggleviewex",            toggleviewex },
	{ "tag",                     tag },
	{ "tagall",                  tagallex },
	{ "tagex",                   tagex },
	{ "toggletag",               toggletag },
	{ "toggletagex",             toggletagex },
	{ "tagallmon",               tagallmon },
	{ "tagswapmon",              tagswapmon},
	{ "togglealttag",            togglealttag },
	{ "fullscreen",              fullscreen },
	{ "togglehorizontalmax",     togglehorizontalmax },
	{ "toggleverticalmax",       toggleverticalmax },
	{ "togglemax",               togglemax },
	{ "unfloatvisible",          unfloatvisible },
	{ "killclient",              killclient },
	{ "winview",                 winview },
	{ "quit",                    quit },
	{ "setlayout",               setlayout },
	{ "setlayoutex",             setlayoutex },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
	IPCCOMMAND( focusmon, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( focusstack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incnmaster, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( killclient, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( quit, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setlayoutsafe, 1, {ARG_TYPE_PTR} ),
	IPCCOMMAND( setmfact, 1, {ARG_TYPE_FLOAT} ),
	IPCCOMMAND( setstatus, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( tag, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( tagmon, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( togglebar, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( toggletopbar, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( togglefloating, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( toggletag, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( toggleview, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( view, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( zoom, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( togglealttag, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setcfact, 1, {ARG_TYPE_FLOAT} ),
	IPCCOMMAND( cyclelayout, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( floatpos, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( fullscreen, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( incnstack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( rotatelayoutaxis, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( setlayoutaxisex, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( mirrorlayout, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( focusurgent, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( inplacerotate, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglehorizontalmax, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( toggleverticalmax, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( togglemax, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( moveresize, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( nametag, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( rioresize, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( pushdown, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( pushup, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( rotatestack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( self_restart, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setborderpx, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( showhideclient, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( shiftboth, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( shifttag, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( shifttagclients, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( shiftswaptags, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglesticky, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( swapfocus, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( tagallmon, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( tagswapmon, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( transfer, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( transferall, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( unfloatvisible, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( incrgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrigaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrogaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrihgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrivgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrohgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrovgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglegaps, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( defaultgaps, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setgapsex, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( winview, 1, {ARG_TYPE_NONE} ),
};
