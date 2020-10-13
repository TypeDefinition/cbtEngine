#pragma once

// Include CBT
#include "Input/cbtKeycode.h"

#ifdef CBT_SDL

// Include SDL
#include <SDL2/SDL_keycode.h>

NS_CBT_BEGIN

cbtKeycode ToCBTKeycode(SDL_Keycode _sdlKeycode)
{
    switch (_sdlKeycode)
    {
    case SDLK_UNKNOWN: return CBTK_UNKNOWN;

    case SDLK_RETURN: return CBTK_RETURN;
    case SDLK_ESCAPE: return CBTK_ESCAPE;
    case SDLK_BACKSPACE: return CBTK_BACKSPACE;
    case SDLK_TAB: return CBTK_TAB;
    case SDLK_SPACE: return CBTK_SPACE;
    case SDLK_EXCLAIM: return CBTK_EXCLAIM;
    case SDLK_QUOTEDBL: return CBTK_QUOTEDBL;
    case SDLK_HASH: return CBTK_HASH;
    case SDLK_PERCENT: return CBTK_PERCENT;
    case SDLK_DOLLAR: return CBTK_DOLLAR;
    case SDLK_AMPERSAND: return CBTK_AMPERSAND;
    case SDLK_QUOTE: return CBTK_QUOTE;
    case SDLK_LEFTPAREN: return CBTK_LEFTPAREN;
    case SDLK_RIGHTPAREN: return CBTK_RIGHTPAREN;
    case SDLK_ASTERISK: return CBTK_ASTERISK;
    case SDLK_PLUS: return CBTK_PLUS;
    case SDLK_COMMA: return CBTK_COMMA;
    case SDLK_MINUS: return CBTK_MINUS;
    case SDLK_PERIOD: return CBTK_PERIOD;
    case SDLK_SLASH: return CBTK_SLASH;
    case SDLK_0: return CBTK_0;
    case SDLK_1: return CBTK_1;
    case SDLK_2 : return CBTK_2;
    case SDLK_3 : return CBTK_3;
    case SDLK_4 : return CBTK_4;
    case SDLK_5 : return CBTK_5;
    case SDLK_6 : return CBTK_6;
    case SDLK_7 : return CBTK_7;
    case SDLK_8 : return CBTK_8;
    case SDLK_9 : return CBTK_9;
    case SDLK_COLON: return CBTK_COLON;
    case SDLK_SEMICOLON: return CBTK_SEMICOLON;
    case SDLK_LESS: return CBTK_LESS;
    case SDLK_EQUALS: return CBTK_EQUALS;
    case SDLK_GREATER: return CBTK_GREATER;
    case SDLK_QUESTION: return CBTK_QUESTION;
    case SDLK_AT: return CBTK_AT;

    // Skip uppercase letters

    case SDLK_LEFTBRACKET: return CBTK_LEFTBRACKET;
    case SDLK_BACKSLASH: return CBTK_BACKSLASH;
    case SDLK_RIGHTBRACKET: return CBTK_RIGHTBRACKET;
    case SDLK_CARET: return CBTK_CARET;
    case SDLK_UNDERSCORE: return CBTK_UNDERSCORE;
    case SDLK_BACKQUOTE: return CBTK_BACKQUOTE;
    case SDLK_a: return CBTK_a;
    case SDLK_b: return CBTK_b;
    case SDLK_c: return CBTK_c;
    case SDLK_d: return CBTK_d;
    case SDLK_e: return CBTK_e;
    case SDLK_f: return CBTK_f;
    case SDLK_g: return CBTK_g;
    case SDLK_h: return CBTK_h;
    case SDLK_i: return CBTK_i;
    case SDLK_j: return CBTK_j;
    case SDLK_k: return CBTK_k;
    case SDLK_l: return CBTK_l;
    case SDLK_m: return CBTK_m;
    case SDLK_n: return CBTK_n;
    case SDLK_o: return CBTK_o;
    case SDLK_p: return CBTK_p;
    case SDLK_q: return CBTK_q;
    case SDLK_r: return CBTK_r;
    case SDLK_s: return CBTK_s;
    case SDLK_t: return CBTK_t;
    case SDLK_u: return CBTK_u;
    case SDLK_v: return CBTK_v;
    case SDLK_w: return CBTK_w;
    case SDLK_x: return CBTK_x;
    case SDLK_y: return CBTK_y;
    case SDLK_z: return CBTK_z;

    case SDLK_CAPSLOCK: return CBTK_CAPSLOCK;

    case SDLK_F1: return CBTK_F1;
    case SDLK_F2: return CBTK_F2;
    case SDLK_F3: return CBTK_F3;
    case SDLK_F4: return CBTK_F4;
    case SDLK_F5: return CBTK_F5;
    case SDLK_F6: return CBTK_F6;
    case SDLK_F7: return CBTK_F7;;
    case SDLK_F8: return CBTK_F8;
    case SDLK_F9: return CBTK_F9;
    case SDLK_F10: return CBTK_F10;
    case SDLK_F11: return CBTK_F11;
    case SDLK_F12: return CBTK_F12;

    case SDLK_PRINTSCREEN: return CBTK_PRINTSCREEN;
    case SDLK_SCROLLLOCK: return CBTK_SCROLLLOCK;
    case SDLK_PAUSE: return CBTK_PAUSE;
    case SDLK_INSERT: return CBTK_INSERT;
    case SDLK_HOME: return CBTK_HOME;
    case SDLK_PAGEUP: return CBTK_PAGEUP;
    case SDLK_DELETE: return CBTK_DELETE;
    case SDLK_END: return CBTK_END;
    case SDLK_PAGEDOWN: return CBTK_PAGEDOWN;
    case SDLK_RIGHT: return CBTK_RIGHT;
    case SDLK_LEFT: return CBTK_LEFT;
    case SDLK_DOWN: return CBTK_DOWN;
    case SDLK_UP: return CBTK_UP;

    case SDLK_NUMLOCKCLEAR: return CBTK_NUMLOCKCLEAR;
    case SDLK_KP_DIVIDE: return CBTK_KP_DIVIDE;
    case SDLK_KP_MULTIPLY: return CBTK_KP_MULTIPLY;
    case SDLK_KP_MINUS: return CBTK_KP_MINUS;
    case SDLK_KP_PLUS: return CBTK_KP_PLUS;
    case SDLK_KP_ENTER: return CBTK_KP_ENTER;
    case SDLK_KP_1: return CBTK_KP_1;
    case SDLK_KP_2: return CBTK_KP_2;
    case SDLK_KP_3: return CBTK_KP_3;
    case SDLK_KP_4: return CBTK_KP_4;
    case SDLK_KP_5: return CBTK_KP_5;
    case SDLK_KP_6: return CBTK_KP_6;
    case SDLK_KP_7: return CBTK_KP_7;
    case SDLK_KP_8: return CBTK_KP_8;
    case SDLK_KP_9: return CBTK_KP_9;
    case SDLK_KP_0: return CBTK_KP_0;
    case SDLK_KP_PERIOD: return CBTK_KP_PERIOD;

    case SDLK_APPLICATION: return CBTK_APPLICATION;
    case SDLK_POWER: return CBTK_POWER;
    case SDLK_KP_EQUALS: return CBTK_KP_EQUALS;
    case SDLK_F13: return CBTK_F13;
    case SDLK_F14: return CBTK_F14;
    case SDLK_F15: return CBTK_F15;
    case SDLK_F16: return CBTK_F16;
    case SDLK_F17: return CBTK_F17;
    case SDLK_F18: return CBTK_F18;
    case SDLK_F19: return CBTK_F19;
    case SDLK_F20: return CBTK_F20;
    case SDLK_F21: return CBTK_F21;
    case SDLK_F22: return CBTK_F22;
    case SDLK_F23: return CBTK_F23;
    case SDLK_F24: return CBTK_F24;
    case SDLK_EXECUTE: return CBTK_EXECUTE;
    case SDLK_HELP: return CBTK_HELP;
    case SDLK_MENU: return CBTK_MENU;
    case SDLK_SELECT: return CBTK_SELECT;
    case SDLK_STOP: return CBTK_STOP;
    case SDLK_AGAIN: return CBTK_AGAIN;
    case SDLK_UNDO: return CBTK_UNDO;
    case SDLK_CUT: return CBTK_CUT;
    case SDLK_COPY: return CBTK_COPY;
    case SDLK_PASTE: return CBTK_PASTE;
    case SDLK_FIND: return CBTK_FIND;
    case SDLK_MUTE: return CBTK_MUTE;
    case SDLK_VOLUMEUP: return CBTK_VOLUMEUP;
    case SDLK_VOLUMEDOWN: return CBTK_VOLUMEDOWN;
    case SDLK_KP_COMMA: return CBTK_KP_COMMA;
    case SDLK_KP_EQUALSAS400: return CBTK_KP_EQUALSAS400;

    case SDLK_ALTERASE: return CBTK_ALTERASE;
    case SDLK_SYSREQ: return CBTK_SYSREQ;
    case SDLK_CANCEL: return CBTK_CANCEL;
    case SDLK_CLEAR: return CBTK_CLEAR;
    case SDLK_PRIOR: return CBTK_PRIOR;
    case SDLK_RETURN2: return CBTK_RETURN2;
    case SDLK_SEPARATOR: return CBTK_SEPARATOR;
    case SDLK_OUT: return CBTK_OUT;
    case SDLK_OPER: return CBTK_OPER;
    case SDLK_CLEARAGAIN: return CBTK_CLEARAGAIN;
    case SDLK_CRSEL: return CBTK_CRSEL;
    case SDLK_EXSEL: return CBTK_EXSEL;

    case SDLK_KP_00: return CBTK_KP_00;
    case SDLK_KP_000: return CBTK_KP_000;
    case SDLK_THOUSANDSSEPARATOR: return CBTK_THOUSANDSSEPARATOR;
    case SDLK_DECIMALSEPARATOR: return CBTK_DECIMALSEPARATOR;
    case SDLK_CURRENCYUNIT: return CBTK_CURRENCYUNIT;
    case SDLK_CURRENCYSUBUNIT: return CBTK_CURRENCYSUBUNIT;
    case SDLK_KP_LEFTPAREN: return CBTK_KP_LEFTPAREN;
    case SDLK_KP_RIGHTPAREN: return CBTK_KP_RIGHTPAREN;
    case SDLK_KP_LEFTBRACE: return CBTK_KP_LEFTBRACE;
    case SDLK_KP_RIGHTBRACE: return CBTK_KP_RIGHTBRACE;
    case SDLK_KP_TAB: return CBTK_KP_TAB;
    case SDLK_KP_BACKSPACE: return CBTK_KP_BACKSPACE;
    case SDLK_KP_A: return CBTK_KP_A;
    case SDLK_KP_B: return CBTK_KP_B;
    case SDLK_KP_C: return CBTK_KP_C;
    case SDLK_KP_D: return CBTK_KP_D;
    case SDLK_KP_E: return CBTK_KP_E;
    case SDLK_KP_F: return CBTK_KP_F;
    case SDLK_KP_XOR: return CBTK_KP_XOR;
    case SDLK_KP_POWER: return CBTK_KP_POWER;
    case SDLK_KP_PERCENT: return CBTK_KP_PERCENT;
    case SDLK_KP_LESS: return CBTK_KP_LESS;
    case SDLK_KP_GREATER: return CBTK_KP_GREATER;
    case SDLK_KP_AMPERSAND: return CBTK_KP_AMPERSAND;
    case SDLK_KP_DBLAMPERSAND: return CBTK_KP_DBLAMPERSAND;
    case SDLK_KP_VERTICALBAR: return CBTK_KP_VERTICALBAR;
    case SDLK_KP_DBLVERTICALBAR: return CBTK_KP_DBLVERTICALBAR;
    case SDLK_KP_COLON: return CBTK_KP_COLON;
    case SDLK_KP_HASH: return CBTK_KP_HASH;
    case SDLK_KP_SPACE: return CBTK_KP_SPACE;
    case SDLK_KP_AT: return CBTK_KP_AT;
    case SDLK_KP_EXCLAM: return CBTK_KP_EXCLAM;
    case SDLK_KP_MEMSTORE: return CBTK_KP_MEMSTORE;
    case SDLK_KP_MEMRECALL: return CBTK_KP_MEMRECALL;
    case SDLK_KP_MEMCLEAR: return CBTK_KP_MEMCLEAR;
    case SDLK_KP_MEMADD: return CBTK_KP_MEMADD;
    case SDLK_KP_MEMSUBTRACT: return CBTK_KP_MEMSUBTRACT;
    case SDLK_KP_MEMMULTIPLY: return CBTK_KP_MEMMULTIPLY;
    case SDLK_KP_MEMDIVIDE: return CBTK_KP_MEMDIVIDE;
    case SDLK_KP_PLUSMINUS: return CBTK_KP_PLUSMINUS;
    case SDLK_KP_CLEAR: return CBTK_KP_CLEAR;
    case SDLK_KP_CLEARENTRY: return CBTK_KP_CLEARENTRY;
    case SDLK_KP_BINARY: return CBTK_KP_BINARY;
    case SDLK_KP_OCTAL: return CBTK_KP_OCTAL;
    case SDLK_KP_DECIMAL: return CBTK_KP_DECIMAL;
    case SDLK_KP_HEXADECIMAL: return CBTK_KP_HEXADECIMAL;

    case SDLK_LCTRL: return CBTK_LCTRL;
    case SDLK_LSHIFT: return CBTK_LSHIFT;
    case SDLK_LALT: return CBTK_LALT;
    case SDLK_LGUI: return CBTK_LGUI;
    case SDLK_RCTRL: return CBTK_RCTRL;
    case SDLK_RSHIFT: return CBTK_RSHIFT;
    case SDLK_RALT: return CBTK_RALT;
    case SDLK_RGUI: return CBTK_RGUI;

    case SDLK_MODE: return CBTK_MODE;

    case SDLK_AUDIONEXT: return CBTK_AUDIONEXT;
    case SDLK_AUDIOPREV: return CBTK_AUDIOPREV;
    case SDLK_AUDIOSTOP: return CBTK_AUDIOSTOP;
    case SDLK_AUDIOPLAY: return CBTK_AUDIOPLAY;
    case SDLK_AUDIOMUTE: return CBTK_AUDIOMUTE;
    case SDLK_MEDIASELECT: return CBTK_MEDIASELECT;
    case SDLK_WWW: return CBTK_WWW;
    case SDLK_MAIL: return CBTK_MAIL;
    case SDLK_CALCULATOR: return CBTK_CALCULATOR;
    case SDLK_COMPUTER: return CBTK_COMPUTER;
    case SDLK_AC_SEARCH: return CBTK_AC_SEARCH;
    case SDLK_AC_HOME: return CBTK_AC_HOME;
    case SDLK_AC_BACK: return CBTK_AC_BACK;
    case SDLK_AC_FORWARD: return CBTK_AC_FORWARD;
    case SDLK_AC_STOP: return CBTK_AC_STOP;
    case SDLK_AC_REFRESH: return CBTK_AC_REFRESH;
    case SDLK_AC_BOOKMARKS: return CBTK_AC_BOOKMARKS;

    case SDLK_BRIGHTNESSDOWN: return CBTK_BRIGHTNESSDOWN;
    case SDLK_BRIGHTNESSUP: return CBTK_BRIGHTNESSUP;
    case SDLK_DISPLAYSWITCH: return CBTK_DISPLAYSWITCH;
    case SDLK_KBDILLUMTOGGLE: return CBTK_KBDILLUMTOGGLE;
    case SDLK_KBDILLUMDOWN: return CBTK_KBDILLUMDOWN;
    case SDLK_KBDILLUMUP: return CBTK_KBDILLUMUP;
    case SDLK_EJECT: return CBTK_EJECT;
    case SDLK_SLEEP: return CBTK_SLEEP;
    case SDLK_APP1: return CBTK_APP1;
    case SDLK_APP2: return CBTK_APP2;

    case SDLK_AUDIOREWIND: return CBTK_AUDIOREWIND;
    case SDLK_AUDIOFASTFORWARD: return CBTK_AUDIOFASTFORWARD;

    default: return CBTK_UNKNOWN;
    }
}

NS_CBT_END

#endif // CBT_SDL