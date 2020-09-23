#pragma once

// Include CBT
#include "Input/CBTKeycode.h"

#ifdef CBT_SDL

// Include SDL
#include "SDL_keycode.h"

NS_CBT_BEGIN

CBTKeycode ToCBTKeycode(SDL_Keycode _sdlKeycode)
{
    switch (_sdlKeycode)
    {
    case SDL_KeyCode::SDLK_UNKNOWN: return CBTK_UNKNOWN;

    case SDL_KeyCode::SDLK_RETURN: return CBTK_RETURN;
    case SDL_KeyCode::SDLK_ESCAPE: return CBTK_ESCAPE;
    case SDL_KeyCode::SDLK_BACKSPACE: return CBTK_BACKSPACE;
    case SDL_KeyCode::SDLK_TAB: return CBTK_TAB;
    case SDL_KeyCode::SDLK_SPACE: return CBTK_SPACE;
    case SDL_KeyCode::SDLK_EXCLAIM: return CBTK_EXCLAIM;
    case SDL_KeyCode::SDLK_QUOTEDBL: return CBTK_QUOTEDBL;
    case SDL_KeyCode::SDLK_HASH: return CBTK_HASH;
    case SDL_KeyCode::SDLK_PERCENT: return CBTK_PERCENT;
    case SDL_KeyCode::SDLK_DOLLAR: return CBTK_DOLLAR;
    case SDL_KeyCode::SDLK_AMPERSAND: return CBTK_AMPERSAND;
    case SDL_KeyCode::SDLK_QUOTE: return CBTK_QUOTE;
    case SDL_KeyCode::SDLK_LEFTPAREN: return CBTK_LEFTPAREN;
    case SDL_KeyCode::SDLK_RIGHTPAREN: return CBTK_RIGHTPAREN;
    case SDL_KeyCode::SDLK_ASTERISK: return CBTK_ASTERISK;
    case SDL_KeyCode::SDLK_PLUS: return CBTK_PLUS;
    case SDL_KeyCode::SDLK_COMMA: return CBTK_COMMA;
    case SDL_KeyCode::SDLK_MINUS: return CBTK_MINUS;
    case SDL_KeyCode::SDLK_PERIOD: return CBTK_PERIOD;
    case SDL_KeyCode::SDLK_SLASH: return CBTK_SLASH;
    case SDL_KeyCode::SDLK_0: return CBTK_0;
    case SDL_KeyCode::SDLK_1: return CBTK_1;
    case SDL_KeyCode::SDLK_2 : return CBTK_2;
    case SDL_KeyCode::SDLK_3 : return CBTK_3;
    case SDL_KeyCode::SDLK_4 : return CBTK_4;
    case SDL_KeyCode::SDLK_5 : return CBTK_5;
    case SDL_KeyCode::SDLK_6 : return CBTK_6;
    case SDL_KeyCode::SDLK_7 : return CBTK_7;
    case SDL_KeyCode::SDLK_8 : return CBTK_8;
    case SDL_KeyCode::SDLK_9 : return CBTK_9;
    case SDL_KeyCode::SDLK_COLON: return CBTK_COLON;
    case SDL_KeyCode::SDLK_SEMICOLON: return CBTK_SEMICOLON;
    case SDL_KeyCode::SDLK_LESS: return CBTK_LESS;
    case SDL_KeyCode::SDLK_EQUALS: return CBTK_EQUALS;
    case SDL_KeyCode::SDLK_GREATER: return CBTK_GREATER;
    case SDL_KeyCode::SDLK_QUESTION: return CBTK_QUESTION;
    case SDL_KeyCode::SDLK_AT: return CBTK_AT;

    // Skip uppercase letters

    case SDL_KeyCode::SDLK_LEFTBRACKET: return CBTK_LEFTBRACKET;
    case SDL_KeyCode::SDLK_BACKSLASH: return CBTK_BACKSLASH;
    case SDL_KeyCode::SDLK_RIGHTBRACKET: return CBTK_RIGHTBRACKET;
    case SDL_KeyCode::SDLK_CARET: return CBTK_CARET;
    case SDL_KeyCode::SDLK_UNDERSCORE: return CBTK_UNDERSCORE;
    case SDL_KeyCode::SDLK_BACKQUOTE: return CBTK_BACKQUOTE;
    case SDL_KeyCode::SDLK_a: return CBTK_a;
    case SDL_KeyCode::SDLK_b: return CBTK_b;
    case SDL_KeyCode::SDLK_c: return CBTK_c;
    case SDL_KeyCode::SDLK_d: return CBTK_d;
    case SDL_KeyCode::SDLK_e: return CBTK_e;
    case SDL_KeyCode::SDLK_f: return CBTK_f;
    case SDL_KeyCode::SDLK_g: return CBTK_g;
    case SDL_KeyCode::SDLK_h: return CBTK_h;
    case SDL_KeyCode::SDLK_i: return CBTK_i;
    case SDL_KeyCode::SDLK_j: return CBTK_j;
    case SDL_KeyCode::SDLK_k: return CBTK_k;
    case SDL_KeyCode::SDLK_l: return CBTK_l;
    case SDL_KeyCode::SDLK_m: return CBTK_m;
    case SDL_KeyCode::SDLK_n: return CBTK_n;
    case SDL_KeyCode::SDLK_o: return CBTK_o;
    case SDL_KeyCode::SDLK_p: return CBTK_p;
    case SDL_KeyCode::SDLK_q: return CBTK_q;
    case SDL_KeyCode::SDLK_r: return CBTK_r;
    case SDL_KeyCode::SDLK_s: return CBTK_s;
    case SDL_KeyCode::SDLK_t: return CBTK_t;
    case SDL_KeyCode::SDLK_u: return CBTK_u;
    case SDL_KeyCode::SDLK_v: return CBTK_v;
    case SDL_KeyCode::SDLK_w: return CBTK_w;
    case SDL_KeyCode::SDLK_x: return CBTK_x;
    case SDL_KeyCode::SDLK_y: return CBTK_y;
    case SDL_KeyCode::SDLK_z: return CBTK_z;

    case SDL_KeyCode::SDLK_CAPSLOCK: return CBTK_CAPSLOCK;

    case SDL_KeyCode::SDLK_F1: return CBTK_F1;
    case SDL_KeyCode::SDLK_F2: return CBTK_F2;
    case SDL_KeyCode::SDLK_F3: return CBTK_F3;
    case SDL_KeyCode::SDLK_F4: return CBTK_F4;
    case SDL_KeyCode::SDLK_F5: return CBTK_F5;
    case SDL_KeyCode::SDLK_F6: return CBTK_F6;
    case SDL_KeyCode::SDLK_F7: return CBTK_F7;;
    case SDL_KeyCode::SDLK_F8: return CBTK_F8;
    case SDL_KeyCode::SDLK_F9: return CBTK_F9;
    case SDL_KeyCode::SDLK_F10: return CBTK_F10;
    case SDL_KeyCode::SDLK_F11: return CBTK_F11;
    case SDL_KeyCode::SDLK_F12: return CBTK_F12;

    case SDL_KeyCode::SDLK_PRINTSCREEN: return CBTK_PRINTSCREEN;
    case SDL_KeyCode::SDLK_SCROLLLOCK: return CBTK_SCROLLLOCK;
    case SDL_KeyCode::SDLK_PAUSE: return CBTK_PAUSE;
    case SDL_KeyCode::SDLK_INSERT: return CBTK_INSERT;
    case SDL_KeyCode::SDLK_HOME: return CBTK_HOME;
    case SDL_KeyCode::SDLK_PAGEUP: return CBTK_PAGEUP;
    case SDL_KeyCode::SDLK_DELETE: return CBTK_DELETE;
    case SDL_KeyCode::SDLK_END: return CBTK_END;
    case SDL_KeyCode::SDLK_PAGEDOWN: return CBTK_PAGEDOWN;
    case SDL_KeyCode::SDLK_RIGHT: return CBTK_RIGHT;
    case SDL_KeyCode::SDLK_LEFT: return CBTK_LEFT;
    case SDL_KeyCode::SDLK_DOWN: return CBTK_DOWN;
    case SDL_KeyCode::SDLK_UP: return CBTK_UP;

    case SDL_KeyCode::SDLK_NUMLOCKCLEAR: return CBTK_NUMLOCKCLEAR;
    case SDL_KeyCode::SDLK_KP_DIVIDE: return CBTK_KP_DIVIDE;
    case SDL_KeyCode::SDLK_KP_MULTIPLY: return CBTK_KP_MULTIPLY;
    case SDL_KeyCode::SDLK_KP_MINUS: return CBTK_KP_MINUS;
    case SDL_KeyCode::SDLK_KP_PLUS: return CBTK_KP_PLUS;
    case SDL_KeyCode::SDLK_KP_ENTER: return CBTK_KP_ENTER;
    case SDL_KeyCode::SDLK_KP_1: return CBTK_KP_1;
    case SDL_KeyCode::SDLK_KP_2: return CBTK_KP_2;
    case SDL_KeyCode::SDLK_KP_3: return CBTK_KP_3;
    case SDL_KeyCode::SDLK_KP_4: return CBTK_KP_4;
    case SDL_KeyCode::SDLK_KP_5: return CBTK_KP_5;
    case SDL_KeyCode::SDLK_KP_6: return CBTK_KP_6;
    case SDL_KeyCode::SDLK_KP_7: return CBTK_KP_7;
    case SDL_KeyCode::SDLK_KP_8: return CBTK_KP_8;
    case SDL_KeyCode::SDLK_KP_9: return CBTK_KP_9;
    case SDL_KeyCode::SDLK_KP_0: return CBTK_KP_0;
    case SDL_KeyCode::SDLK_KP_PERIOD: return CBTK_KP_PERIOD;

    case SDL_KeyCode::SDLK_APPLICATION: return CBTK_APPLICATION;
    case SDL_KeyCode::SDLK_POWER: return CBTK_POWER;
    case SDL_KeyCode::SDLK_KP_EQUALS: return CBTK_KP_EQUALS;
    case SDL_KeyCode::SDLK_F13: return CBTK_F13;
    case SDL_KeyCode::SDLK_F14: return CBTK_F14;
    case SDL_KeyCode::SDLK_F15: return CBTK_F15;
    case SDL_KeyCode::SDLK_F16: return CBTK_F16;
    case SDL_KeyCode::SDLK_F17: return CBTK_F17;
    case SDL_KeyCode::SDLK_F18: return CBTK_F18;
    case SDL_KeyCode::SDLK_F19: return CBTK_F19;
    case SDL_KeyCode::SDLK_F20: return CBTK_F20;
    case SDL_KeyCode::SDLK_F21: return CBTK_F21;
    case SDL_KeyCode::SDLK_F22: return CBTK_F22;
    case SDL_KeyCode::SDLK_F23: return CBTK_F23;
    case SDL_KeyCode::SDLK_F24: return CBTK_F24;
    case SDL_KeyCode::SDLK_EXECUTE: return CBTK_EXECUTE;
    case SDL_KeyCode::SDLK_HELP: return CBTK_HELP;
    case SDL_KeyCode::SDLK_MENU: return CBTK_MENU;
    case SDL_KeyCode::SDLK_SELECT: return CBTK_SELECT;
    case SDL_KeyCode::SDLK_STOP: return CBTK_STOP;
    case SDL_KeyCode::SDLK_AGAIN: return CBTK_AGAIN;
    case SDL_KeyCode::SDLK_UNDO: return CBTK_UNDO;
    case SDL_KeyCode::SDLK_CUT: return CBTK_CUT;
    case SDL_KeyCode::SDLK_COPY: return CBTK_COPY;
    case SDL_KeyCode::SDLK_PASTE: return CBTK_PASTE;
    case SDL_KeyCode::SDLK_FIND: return CBTK_FIND;
    case SDL_KeyCode::SDLK_MUTE: return CBTK_MUTE;
    case SDL_KeyCode::SDLK_VOLUMEUP: return CBTK_VOLUMEUP;
    case SDL_KeyCode::SDLK_VOLUMEDOWN: return CBTK_VOLUMEDOWN;
    case SDL_KeyCode::SDLK_KP_COMMA: return CBTK_KP_COMMA;
    case SDL_KeyCode::SDLK_KP_EQUALSAS400: return CBTK_KP_EQUALSAS400;

    case SDL_KeyCode::SDLK_ALTERASE: return CBTK_ALTERASE;
    case SDL_KeyCode::SDLK_SYSREQ: return CBTK_SYSREQ;
    case SDL_KeyCode::SDLK_CANCEL: return CBTK_CANCEL;
    case SDL_KeyCode::SDLK_CLEAR: return CBTK_CLEAR;
    case SDL_KeyCode::SDLK_PRIOR: return CBTK_PRIOR;
    case SDL_KeyCode::SDLK_RETURN2: return CBTK_RETURN2;
    case SDL_KeyCode::SDLK_SEPARATOR: return CBTK_SEPARATOR;
    case SDL_KeyCode::SDLK_OUT: return CBTK_OUT;
    case SDL_KeyCode::SDLK_OPER: return CBTK_OPER;
    case SDL_KeyCode::SDLK_CLEARAGAIN: return CBTK_CLEARAGAIN;
    case SDL_KeyCode::SDLK_CRSEL: return CBTK_CRSEL;
    case SDL_KeyCode::SDLK_EXSEL: return CBTK_EXSEL;

    case SDL_KeyCode::SDLK_KP_00: return CBTK_KP_00;
    case SDL_KeyCode::SDLK_KP_000: return CBTK_KP_000;
    case SDL_KeyCode::SDLK_THOUSANDSSEPARATOR: return CBTK_THOUSANDSSEPARATOR;
    case SDL_KeyCode::SDLK_DECIMALSEPARATOR: return CBTK_DECIMALSEPARATOR;
    case SDL_KeyCode::SDLK_CURRENCYUNIT: return CBTK_CURRENCYUNIT;
    case SDL_KeyCode::SDLK_CURRENCYSUBUNIT: return CBTK_CURRENCYSUBUNIT;
    case SDL_KeyCode::SDLK_KP_LEFTPAREN: return CBTK_KP_LEFTPAREN;
    case SDL_KeyCode::SDLK_KP_RIGHTPAREN: return CBTK_KP_RIGHTPAREN;
    case SDL_KeyCode::SDLK_KP_LEFTBRACE: return CBTK_KP_LEFTBRACE;
    case SDL_KeyCode::SDLK_KP_RIGHTBRACE: return CBTK_KP_RIGHTBRACE;
    case SDL_KeyCode::SDLK_KP_TAB: return CBTK_KP_TAB;
    case SDL_KeyCode::SDLK_KP_BACKSPACE: return CBTK_KP_BACKSPACE;
    case SDL_KeyCode::SDLK_KP_A: return CBTK_KP_A;
    case SDL_KeyCode::SDLK_KP_B: return CBTK_KP_B;
    case SDL_KeyCode::SDLK_KP_C: return CBTK_KP_C;
    case SDL_KeyCode::SDLK_KP_D: return CBTK_KP_D;
    case SDL_KeyCode::SDLK_KP_E: return CBTK_KP_E;
    case SDL_KeyCode::SDLK_KP_F: return CBTK_KP_F;
    case SDL_KeyCode::SDLK_KP_XOR: return CBTK_KP_XOR;
    case SDL_KeyCode::SDLK_KP_POWER: return CBTK_KP_POWER;
    case SDL_KeyCode::SDLK_KP_PERCENT: return CBTK_KP_PERCENT;
    case SDL_KeyCode::SDLK_KP_LESS: return CBTK_KP_LESS;
    case SDL_KeyCode::SDLK_KP_GREATER: return CBTK_KP_GREATER;
    case SDL_KeyCode::SDLK_KP_AMPERSAND: return CBTK_KP_AMPERSAND;
    case SDL_KeyCode::SDLK_KP_DBLAMPERSAND: return CBTK_KP_DBLAMPERSAND;
    case SDL_KeyCode::SDLK_KP_VERTICALBAR: return CBTK_KP_VERTICALBAR;
    case SDL_KeyCode::SDLK_KP_DBLVERTICALBAR: return CBTK_KP_DBLVERTICALBAR;
    case SDL_KeyCode::SDLK_KP_COLON: return CBTK_KP_COLON;
    case SDL_KeyCode::SDLK_KP_HASH: return CBTK_KP_HASH;
    case SDL_KeyCode::SDLK_KP_SPACE: return CBTK_KP_SPACE;
    case SDL_KeyCode::SDLK_KP_AT: return CBTK_KP_AT;
    case SDL_KeyCode::SDLK_KP_EXCLAM: return CBTK_KP_EXCLAM;
    case SDL_KeyCode::SDLK_KP_MEMSTORE: return CBTK_KP_MEMSTORE;
    case SDL_KeyCode::SDLK_KP_MEMRECALL: return CBTK_KP_MEMRECALL;
    case SDL_KeyCode::SDLK_KP_MEMCLEAR: return CBTK_KP_MEMCLEAR;
    case SDL_KeyCode::SDLK_KP_MEMADD: return CBTK_KP_MEMADD;
    case SDL_KeyCode::SDLK_KP_MEMSUBTRACT: return CBTK_KP_MEMSUBTRACT;
    case SDL_KeyCode::SDLK_KP_MEMMULTIPLY: return CBTK_KP_MEMMULTIPLY;
    case SDL_KeyCode::SDLK_KP_MEMDIVIDE: return CBTK_KP_MEMDIVIDE;
    case SDL_KeyCode::SDLK_KP_PLUSMINUS: return CBTK_KP_PLUSMINUS;
    case SDL_KeyCode::SDLK_KP_CLEAR: return CBTK_KP_CLEAR;
    case SDL_KeyCode::SDLK_KP_CLEARENTRY: return CBTK_KP_CLEARENTRY;
    case SDL_KeyCode::SDLK_KP_BINARY: return CBTK_KP_BINARY;
    case SDL_KeyCode::SDLK_KP_OCTAL: return CBTK_KP_OCTAL;
    case SDL_KeyCode::SDLK_KP_DECIMAL: return CBTK_KP_DECIMAL;
    case SDL_KeyCode::SDLK_KP_HEXADECIMAL: return CBTK_KP_HEXADECIMAL;

    case SDL_KeyCode::SDLK_LCTRL: return CBTK_LCTRL;
    case SDL_KeyCode::SDLK_LSHIFT: return CBTK_LSHIFT;
    case SDL_KeyCode::SDLK_LALT: return CBTK_LALT;
    case SDL_KeyCode::SDLK_LGUI: return CBTK_LGUI;
    case SDL_KeyCode::SDLK_RCTRL: return CBTK_RCTRL;
    case SDL_KeyCode::SDLK_RSHIFT: return CBTK_RSHIFT;
    case SDL_KeyCode::SDLK_RALT: return CBTK_RALT;
    case SDL_KeyCode::SDLK_RGUI: return CBTK_RGUI;

    case SDL_KeyCode::SDLK_MODE: return CBTK_MODE;

    case SDL_KeyCode::SDLK_AUDIONEXT: return CBTK_AUDIONEXT;
    case SDL_KeyCode::SDLK_AUDIOPREV: return CBTK_AUDIOPREV;
    case SDL_KeyCode::SDLK_AUDIOSTOP: return CBTK_AUDIOSTOP;
    case SDL_KeyCode::SDLK_AUDIOPLAY: return CBTK_AUDIOPLAY;
    case SDL_KeyCode::SDLK_AUDIOMUTE: return CBTK_AUDIOMUTE;
    case SDL_KeyCode::SDLK_MEDIASELECT: return CBTK_MEDIASELECT;
    case SDL_KeyCode::SDLK_WWW: return CBTK_WWW;
    case SDL_KeyCode::SDLK_MAIL: return CBTK_MAIL;
    case SDL_KeyCode::SDLK_CALCULATOR: return CBTK_CALCULATOR;
    case SDL_KeyCode::SDLK_COMPUTER: return CBTK_COMPUTER;
    case SDL_KeyCode::SDLK_AC_SEARCH: return CBTK_AC_SEARCH;
    case SDL_KeyCode::SDLK_AC_HOME: return CBTK_AC_HOME;
    case SDL_KeyCode::SDLK_AC_BACK: return CBTK_AC_BACK;
    case SDL_KeyCode::SDLK_AC_FORWARD: return CBTK_AC_FORWARD;
    case SDL_KeyCode::SDLK_AC_STOP: return CBTK_AC_STOP;
    case SDL_KeyCode::SDLK_AC_REFRESH: return CBTK_AC_REFRESH;
    case SDL_KeyCode::SDLK_AC_BOOKMARKS: return CBTK_AC_BOOKMARKS;

    case SDL_KeyCode::SDLK_BRIGHTNESSDOWN: return CBTK_BRIGHTNESSDOWN;
    case SDL_KeyCode::SDLK_BRIGHTNESSUP: return CBTK_BRIGHTNESSUP;
    case SDL_KeyCode::SDLK_DISPLAYSWITCH: return CBTK_DISPLAYSWITCH;
    case SDL_KeyCode::SDLK_KBDILLUMTOGGLE: return CBTK_KBDILLUMTOGGLE;
    case SDL_KeyCode::SDLK_KBDILLUMDOWN: return CBTK_KBDILLUMDOWN;
    case SDL_KeyCode::SDLK_KBDILLUMUP: return CBTK_KBDILLUMUP;
    case SDL_KeyCode::SDLK_EJECT: return CBTK_EJECT;
    case SDL_KeyCode::SDLK_SLEEP: return CBTK_SLEEP;
    case SDL_KeyCode::SDLK_APP1: return CBTK_APP1;
    case SDL_KeyCode::SDLK_APP2: return CBTK_APP2;

    case SDL_KeyCode::SDLK_AUDIOREWIND: return CBTK_AUDIOREWIND;
    case SDL_KeyCode::SDLK_AUDIOFASTFORWARD: return CBTK_AUDIOFASTFORWARD;

    default: return CBTK_UNKNOWN;
    }
}

NS_CBT_END

#endif // CBT_SDL