/* NetHack 3.5	amimenu.c	$NHDT-Date$  $NHDT-Branch$:$NHDT-Revision$ */
/* NetHack 3.5	amimenu.c	$Date: 2009/05/06 10:48:29 $  $Revision: 1.3 $ */
/*    SCCS Id: @(#)amimenu.c    3.5    1996/02/04		   */
/*    Copyright (c) Olaf 'Rhialto' Seibert, 1989		   */
/*    Copyright (c) Kenneth Lorber, Bethesda, Maryland, 1992, 1993, 1996 */
/*    Copyright (c) Janne Salmij�rvi, 2000 */
/* NetHack may be freely redistributed.  See license for details.  */

/*  Originally by John Toebes.  */

/*  GadTools menus by jhsa */

struct NewMenu GTHackMenu[] = {
    { NM_TITLE, "Commands",                                0, 0, 0, 0},
    {  NM_ITEM, "?   Display help menu",                   0, 0, 0, (void *)'?'},
    {  NM_ITEM, "&   Explain a command",                   0, 0, 0, (void *)'&'},
    {  NM_ITEM, "O   Set options",                         0, 0, 0, (void *)'O'},
    {  NM_ITEM, "!   AmigaDos command",                    0, 0, 0, (void *)'!'},
    {  NM_ITEM, "v   Version number",                      0, 0, 0, (void *)'v'},
    {  NM_ITEM, "V   Long version and game history",       0, 0, 0, (void *)'V'},
    {  NM_ITEM, "^R  Redraw screen",                       0, 0, 0, (void *)022},
    {  NM_ITEM, "^P  Repeat previous messages",            0, 0, 0, (void *)020},
    {  NM_ITEM, "M-q #quit the game",                      0, 0, 0, (void *)(128+'q')},
    {  NM_ITEM, "S   Save the game",                       0, 0, 0, (void *)'S'},
    { NM_TITLE, "Inventory",                               0, 0, 0, 0},
    {  NM_ITEM, "i   Inventory",                           0, 0, 0, (void *)'i'},
    {  NM_ITEM, "p   Pay your bill",                       0, 0, 0, (void *)'p'},
    {  NM_ITEM, "d   Drop an object",                      0, 0, 0, (void *)'d'},
    {  NM_ITEM, "D   Drop several things",                 0, 0, 0, (void *)'D'},
    {  NM_ITEM, ",   Pickup an object",                    0, 0, 0, (void *)','},
    {  NM_ITEM, "@   Toggle pickup",                       0, 0, 0, (void *)'@'},
    {  NM_ITEM, "/   Identify something",                  0, 0, 0, (void *)'/'},
    {  NM_ITEM, "C   Christen a monster",                  0, 0, 0, (void *)'C'},
    {  NM_ITEM, "+   List known spells",                   0, 0, 0, (void *)'+'},
    {  NM_ITEM, "$   Your gold",                           0, 0, 0, (void *)'$'},
    { NM_TITLE, "Actions",                                 0, 0, 0, 0},
    {  NM_ITEM, "a   Apply/use something",                 0, 0, 0, (void *)'a'},
    {  NM_ITEM, "e   Eat something",                       0, 0, 0, (void *)'e'},
    {  NM_ITEM, "f   Fire ammunition",                     0, 0, 0, (void *)'f'},
    {  NM_ITEM, "F   Fight a monster",                     0, 0, 0, (void *)'F'},
    {  NM_ITEM, "q   Quaff a monster",                     0, 0, 0, (void *)'q'},
    {  NM_ITEM, "r   Read scroll/book",                    0, 0, 0, (void *)'r'},
    {  NM_ITEM, "t   Throw something",                     0, 0, 0, (void *)'t'},
    {  NM_ITEM, "z   Zap a wand",                          0, 0, 0, (void *)'z'},
    {  NM_ITEM, "Z   Cast a spell",                        0, 0, 0, (void *)'Z'},
    { NM_TITLE, "Preparations",                            0, 0, 0, 0},
    {  NM_ITEM, "A   Remove all armor",                    0, 0, 0, (void *)'A'},
    {  NM_ITEM, "P   Put on a ring",                       0, 0, 0, (void *)'P'},
    {  NM_ITEM, "R   Remove ring",                         0, 0, 0, (void *)'R'},
    {  NM_ITEM, "Q   Select ammunition for quiver",        0, 0, 0, (void *)'Q'},
    {  NM_ITEM, "T   Take off armor",                      0, 0, 0, (void *)'T'},
    {  NM_ITEM, "w   Wield a weapon",                      0, 0, 0, (void *)'w'},
    {  NM_ITEM, "W   Wear armor",                          0, 0, 0, (void *)'W'},
    {  NM_ITEM, "x   Swap wielded and secondary weapons",  0, 0, 0, (void *)'x'},
    {  NM_ITEM, ")   Current weapon",                      0, 0, 0, (void *)')'},
    {  NM_ITEM, "[   Current armor",                       0, 0, 0, (void *)'['},
    {  NM_ITEM, "=   Current rings",                       0, 0, 0, (void *)'='},
    {  NM_ITEM,"\"   Current amulet",                      0, 0, 0, (void *)'"'},
    {  NM_ITEM, "(   Current tools",                       0, 0, 0, (void *)'('},
    {  NM_ITEM, "*   Current equipment",                   0, 0, 0, (void *)'*'},
    { NM_TITLE, "Movement",                                0, 0, 0, 0},
    {  NM_ITEM, "o   Open door",                           0, 0, 0, (void *)'o'},
    {  NM_ITEM, "c   Close door",                          0, 0, 0, (void *)'c'},
    {  NM_ITEM, "^D  Kick door",                           0, 0, 0, (void *)004},
    {  NM_ITEM, "s   Search",                              0, 0, 0, (void *)'s'},
    {  NM_ITEM, "<   Go up stairs",                        0, 0, 0, (void *)'<'},
    {  NM_ITEM, ">   Go down stairs",                      0, 0, 0, (void *)'>'},
    {  NM_ITEM, "^T  Teleport",                            0, 0, 0, (void *)024},
    {  NM_ITEM, ".   Wait a moment",                       0, 0, 0, (void *)'.'},
    {  NM_ITEM, "E   Engrave message on floor",            0, 0, 0, (void *)'E'},
    { NM_TITLE, "Extended",                                0, 0, 0, 0},
    {  NM_ITEM, "M-a  #adjust inventory letters",          0, 0, 0, (void *)(128+'a')},
    {  NM_ITEM, "M-c  #chat with someone",                 0, 0, 0, (void *)(128+'c')},
    {  NM_ITEM, "M-d  #dip an object into something",      0, 0, 0, (void *)(128+'d')},
#ifdef WEAPON_SKILLS
    {  NM_ITEM, "M-e  #enhance weapon skills",             0, 0, 0, (void *)(128+'e')},
#endif
    {  NM_ITEM, "M-f  #force a lock",                      0, 0, 0, (void *)(128+'f')},
    {  NM_ITEM, "M-i  #invoke an object's special powers", 0, 0, 0, (void *)(128+'i')},
    {  NM_ITEM, "M-j  #jump to another location",          0, 0, 0, (void *)(128+'j')},
    {  NM_ITEM, "M-l  #loot a box on the floor",           0, 0, 0, (void *)(128+'l')},
    {  NM_ITEM, "M-m  Use a #monster's special ability",   0, 0, 0, (void *)(128+'m')},
    {  NM_ITEM, "M-n  #name an item or type of object",    0, 0, 0, (void *)(128+'n')},
    {  NM_ITEM, "M-o  #offer a sacrifice to the gods",     0, 0, 0, (void *)(128+'o')},
    {  NM_ITEM, "M-p  #pray to the gods for help",         0, 0, 0, (void *)(128+'p')},
    {  NM_ITEM, "M-q  #quit the game",                     0, 0, 0, (void *)(128+'q')},
    {  NM_ITEM, "M-r  #rub a lamp",                        0, 0, 0, (void *)(128+'r')},
    {  NM_ITEM, "M-s  #sit down",                          0, 0, 0, (void *)(128+'s')},
    {  NM_ITEM, "M-t  #turn undead",                       0, 0, 0, (void *)(128+'t')},
    {  NM_ITEM, "M-u  #untrap something",                  0, 0, 0, (void *)(128+'u')},
    {  NM_ITEM, "M-v  Long #version information",          0, 0, 0, (void *)(128+'v')},
    {  NM_ITEM, "M-w  #wipe off your face",                0, 0, 0, (void *)(128+'w')},
    {  NM_ITEM, "     Your #conduct",                      0, 0, 0, (void *)'#'}, /* "#co\n" */
    {  NM_ITEM, "     #ride your steed",                   0, 0, 0, (void *)'#'}, /* "#ri\n" */
    {  NM_ITEM, "M-2  Switch #twoweapon mode on/off",      0, 0, 0, (void *)(128+'2')},
    {  NM_END,  NULL,                                      0, 0, 0, 0}
};