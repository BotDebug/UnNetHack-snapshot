/*  SCCS Id: @(#)getline.c  3.4 2002/10/06  */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

#ifdef TTY_GRAPHICS

#if !defined(MAC)
#define NEWAUTOCOMP
#endif

#include "wintty.h"
#include "func_tab.h"

char morc = 0;  /* tell the outside world what char you chose */
static boolean suppress_history;
static boolean ext_cmd_getlin_hook(char *);

typedef boolean (*getlin_hook_proc)(char *);

static void hooked_tty_getlin(const char*, char*, getlin_hook_proc);
extern int extcmd_via_menu(void); /* cmd.c */

extern char erase_char, kill_char; /* from appropriate tty.c file */

/*
 * Read a line closed with '\n' into the array char bufp[BUFSZ].
 * (The '\n' is not stored. The string is closed with a '\0'.)
 * Reading can be interrupted by an escape ('\033') - now the
 * resulting string is "\033".
 */
void
tty_getlin(const char *query, char *bufp)
{
    suppress_history = FALSE;
    hooked_tty_getlin(query, bufp, (getlin_hook_proc) 0);
}

static void
hooked_tty_getlin(const char *query, char *bufp, getlin_hook_proc hook)
{
    char *obufp = bufp;
    int c;
    struct WinDesc *cw = wins[WIN_MESSAGE];
    boolean doprev = 0;

    if(ttyDisplay->toplin == 1 && !(cw->flags & WIN_STOP)) more();
    cw->flags &= ~WIN_STOP;
    ttyDisplay->toplin = 3; /* special prompt state */
    ttyDisplay->inread++;
    pline("%s ", query);
    *obufp = 0;
    for(;;) {
        (void) fflush(stdout);
        Sprintf(toplines, "%s ", query);
        Strcat(toplines, obufp);
        if((c = Getchar()) == EOF) {
#ifndef NEWAUTOCOMP
            *bufp = 0;
#endif /* not NEWAUTOCOMP */
            break;
        }
        if (c == '\033') {
            /* player pressed cursor keys, clear input string */
            if (obufp[0] != '\0') {
                obufp[0] = 0;
                bufp = obufp;
                tty_clear_nhwindow(WIN_MESSAGE);
                cw->maxcol = cw->maxrow;
                addtopl(query);
                addtopl(" ");
                addtopl(obufp);
            } else {
                *obufp = c;
                obufp[1] = 0;
                break;
            }
        }
        if (ttyDisplay->intr) {
            ttyDisplay->intr--;
            *bufp = 0;
        }
        if(c == '\020') { /* ctrl-P */
            if (iflags.prevmsg_window != 's') {
                int sav = ttyDisplay->inread;
                ttyDisplay->inread = 0;
                (void) tty_doprev_message();
                ttyDisplay->inread = sav;
                tty_clear_nhwindow(WIN_MESSAGE);
                cw->maxcol = cw->maxrow;
                addtopl(query);
                addtopl(" ");
                *bufp = 0;
                addtopl(obufp);
            } else {
                if (!doprev)
                    (void) tty_doprev_message(); /* need two initially */
                (void) tty_doprev_message();
                doprev = 1;
                continue;
            }
        } else if (doprev && iflags.prevmsg_window == 's') {
            tty_clear_nhwindow(WIN_MESSAGE);
            cw->maxcol = cw->maxrow;
            doprev = 0;
            addtopl(query);
            addtopl(" ");
            *bufp = 0;
            addtopl(obufp);
        }
        if(c == erase_char || c == '\b') {
            if(bufp != obufp) {
#ifdef NEWAUTOCOMP
                char *i;

#endif /* NEWAUTOCOMP */
                bufp--;
#ifndef NEWAUTOCOMP
                putsyms("\b \b");/* putsym converts \b */
#else /* NEWAUTOCOMP */
                putsyms("\b");
                for (i = bufp; *i; ++i) putsyms(" ");
                for (; i > bufp; --i) putsyms("\b");
                *bufp = 0;
#endif /* NEWAUTOCOMP */
            } else tty_nhbell();
#if defined(apollo)
        } else if(c == '\n' || c == '\r') {
#else
        } else if(c == '\n') {
#endif
#ifndef NEWAUTOCOMP
            *bufp = 0;
#endif /* not NEWAUTOCOMP */
            break;
        } else if(' ' <= (unsigned char) c && c != '\177' &&
                  (bufp-obufp < BUFSZ-1 && bufp-obufp < COLNO)) {
            /* avoid isprint() - some people don't have it
               ' ' is not always a printing char */
#ifdef NEWAUTOCOMP
            char *i = eos(bufp);

#endif /* NEWAUTOCOMP */
            *bufp = c;
            bufp[1] = 0;
            putsyms(bufp);
            bufp++;
            if (hook && (*hook)(obufp)) {
                putsyms(bufp);
#ifndef NEWAUTOCOMP
                bufp = eos(bufp);
#else /* NEWAUTOCOMP */
                /* pointer and cursor left where they were */
                for (i = bufp; *i; ++i) putsyms("\b");
            } else if (i > bufp) {
                char *s = i;

                /* erase rest of prior guess */
                for (; i > bufp; --i) putsyms(" ");
                for (; s > bufp; --s) putsyms("\b");
#endif /* NEWAUTOCOMP */
            }
        } else if(c == kill_char || c == '\177') { /* Robert Viduya */
            /* this test last - @ might be the kill_char */
#ifndef NEWAUTOCOMP
            while(bufp != obufp) {
                bufp--;
                putsyms("\b \b");
            }
#else /* NEWAUTOCOMP */
            for (; *bufp; ++bufp) putsyms(" ");
            for (; bufp != obufp; --bufp) putsyms("\b \b");
            *bufp = 0;
#endif /* NEWAUTOCOMP */
        } else
            tty_nhbell();
    }
    ttyDisplay->toplin = 2;     /* nonempty, no --More-- required */
    ttyDisplay->inread--;
    clear_nhwindow(WIN_MESSAGE);    /* clean up after ourselves */
}

void
xwaitforspace(const char *s) /**< chars allowed besides return */
{
    int c, x = ttyDisplay ? (int) ttyDisplay->dismiss_more : '\n';

    morc = 0;

    while((c = tty_nhgetch()) != '\n') {
        if(iflags.cbreak) {
            if ((s && index(s, c)) || c == x) {
                morc = (char) c;
                break;
            }
            tty_nhbell();
        }
        if (c == -1) break; /* lost terminal or other error */
    }

}

/*
 * Implement extended command completion by using this hook into
 * tty_getlin.  Check the characters already typed, if they uniquely
 * identify an extended command, expand the string to the whole
 * command.
 *
 * Return TRUE if we've extended the string at base.  Otherwise return FALSE.
 * Assumptions:
 *
 *  + we don't change the characters that are already in base
 *  + base has enough room to hold our string
 */
static boolean
ext_cmd_getlin_hook(char *base)
{
    int oindex, com_index;

    com_index = -1;
    for (oindex = 0; extcmdlist[oindex].ef_txt != (char *)0; oindex++) {
        if (extcmdlist[oindex].flags & CMD_NOT_AVAILABLE) {
            continue;
        }
        if ((extcmdlist[oindex].flags & AUTOCOMPLETE) &&
             !(!wizard && (extcmdlist[oindex].flags & WIZMODECMD)) &&
             !strncmpi(base, extcmdlist[oindex].ef_txt, strlen(base))) {
            if (com_index == -1) {
                /* no matches yet */
                com_index = oindex;
            } else {
                /* more than 1 match */
                return FALSE;
            }
        }
    }
    if (com_index >= 0) {
        Strcpy(base, extcmdlist[com_index].ef_txt);
        return TRUE;
    }

    return FALSE; /* didn't match anything */
}

/*
 * Read in an extended command, doing command line completion.  We
 * stop when we have found enough characters to make a unique command.
 */
int
tty_get_ext_cmd(void)
{
    int i;
    char buf[BUFSZ];

    if (iflags.extmenu) return extcmd_via_menu();

    suppress_history = TRUE;
    /* maybe a runtime option? */
    /* hooked_tty_getlin("#", buf, flags.cmd_comp ? ext_cmd_getlin_hook : (getlin_hook_proc) 0); */
#ifdef REDO
    hooked_tty_getlin("#", buf, in_doagain ? (getlin_hook_proc)0
                      : ext_cmd_getlin_hook);
#else
    hooked_tty_getlin("#", buf, ext_cmd_getlin_hook);
#endif
    (void) mungspaces(buf);
    if (buf[0] == 0 || buf[0] == '\033') return -1;

    for (i = 0; extcmdlist[i].ef_txt != (char *)0; i++)
        if (!strcmpi(buf, extcmdlist[i].ef_txt)) break;

#ifdef REDO
    if (!in_doagain) {
        int j;
        for (j = 0; buf[j]; j++)
            savech(buf[j]);
        savech('\n');
    }
#endif

    if (extcmdlist[i].ef_txt == (char *)0) {
        pline("%s: unknown extended command.", buf);
        i = -1;
    }

    return i;
}

#endif /* TTY_GRAPHICS */

/*getline.c*/
