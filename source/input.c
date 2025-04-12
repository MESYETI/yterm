#include "util.h"
#include "input.h"

bool ShiftPressed(const bool* keys) {
	return (keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT])? true : false;
}

static char* KeyToSequence(SDL_Scancode key) {
	const bool* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_LCTRL] && ShiftPressed(keys)) {
		switch (key) {
			case SDL_SCANCODE_BACKSPACE: return DupString("\x08");
			case SDL_SCANCODE_RETURN:    return DupString("\n");
			case SDL_SCANCODE_F1:        return DupString("\x1b[1;6P");
			case SDL_SCANCODE_F2:        return DupString("\x1b[1;6Q");
			case SDL_SCANCODE_F3:        return DupString("\x1bOR");
			case SDL_SCANCODE_F4:        return DupString("\x1b[1;6S");
			case SDL_SCANCODE_F5:        return DupString("\x1b[15;6~");
			case SDL_SCANCODE_F6:        return DupString("\x1b[17;6~");
			case SDL_SCANCODE_F7:        return DupString("\x1b[18;6~");
			case SDL_SCANCODE_F8:        return DupString("\x1b[19;6~");
			case SDL_SCANCODE_F9:        return DupString("\x1b[20;6~");
			case SDL_SCANCODE_F10:       return DupString("\x1b[21;6~");
			case SDL_SCANCODE_F11:       return DupString("\x1b[23;6~");
			case SDL_SCANCODE_F12:       return DupString("\x1b[24;6~");
			case SDL_SCANCODE_UP:        return DupString("\x1b[1;6A");
			case SDL_SCANCODE_DOWN:      return DupString("\x1b[1;6B");
			case SDL_SCANCODE_RIGHT:     return DupString("\x1b[1;6C");
			case SDL_SCANCODE_LEFT:      return DupString("\x1b[1;6D");
			default:                     return NULL;
		}
	}
	else if (keys[SDL_SCANCODE_LCTRL]) {
		switch (key) {
			case SDL_SCANCODE_BACKSPACE: return DupString("\x7F");
			case SDL_SCANCODE_RETURN:    return DupString("\n");
			case SDL_SCANCODE_F1:        return DupString(""); // lxterminal does nothing for these?
			case SDL_SCANCODE_F2:        return DupString("");
			case SDL_SCANCODE_F3:        return DupString("");
			case SDL_SCANCODE_F4:        return DupString("");
			case SDL_SCANCODE_F5:        return DupString("\x1b[15;5~");
			case SDL_SCANCODE_F6:        return DupString("\x1b[17;5~");
			case SDL_SCANCODE_F7:        return DupString("\x1b[18;5~");
			case SDL_SCANCODE_F8:        return DupString("\x1b[19;5~");
			case SDL_SCANCODE_F9:        return DupString("\x1b[20;5~");
			case SDL_SCANCODE_F10:       return DupString("\x1b[21;5~");
			case SDL_SCANCODE_F11:       return DupString("\x1b[23;5~");
			case SDL_SCANCODE_F12:       return DupString("\x1b[24;5~");
			case SDL_SCANCODE_A:         return CharToString('A' & 0x1F);
			case SDL_SCANCODE_B:         return CharToString('B' & 0x1F);
			case SDL_SCANCODE_C:         return CharToString('C' & 0x1F);
			case SDL_SCANCODE_D:         return CharToString('D' & 0x1F);
			case SDL_SCANCODE_E:         return CharToString('E' & 0x1F);
			case SDL_SCANCODE_F:         return CharToString('F' & 0x1F);
			case SDL_SCANCODE_G:         return CharToString('G' & 0x1F);
			case SDL_SCANCODE_H:         return CharToString('H' & 0x1F);
			case SDL_SCANCODE_I:         return CharToString('I' & 0x1F);
			case SDL_SCANCODE_J:         return CharToString('J' & 0x1F);
			case SDL_SCANCODE_K:         return CharToString('K' & 0x1F);
			case SDL_SCANCODE_L:         return CharToString('L' & 0x1F);
			case SDL_SCANCODE_M:         return CharToString('M' & 0x1F);
			case SDL_SCANCODE_N:         return CharToString('N' & 0x1F);
			case SDL_SCANCODE_O:         return CharToString('O' & 0x1F);
			case SDL_SCANCODE_P:         return CharToString('P' & 0x1F);
			case SDL_SCANCODE_Q:         return CharToString('Q' & 0x1F);
			case SDL_SCANCODE_R:         return CharToString('R' & 0x1F);
			case SDL_SCANCODE_S:         return CharToString('S' & 0x1F);
			case SDL_SCANCODE_T:         return CharToString('T' & 0x1F);
			case SDL_SCANCODE_U:         return CharToString('U' & 0x1F);
			case SDL_SCANCODE_V:         return CharToString('V' & 0x1F);
			case SDL_SCANCODE_W:         return CharToString('W' & 0x1F);
			case SDL_SCANCODE_X:         return CharToString('X' & 0x1F);
			case SDL_SCANCODE_Y:         return CharToString('Y' & 0x1F);
			case SDL_SCANCODE_Z:         return CharToString('Z' & 0x1F);
			case SDL_SCANCODE_UP:        return DupString("\x1b[1;5A");
			case SDL_SCANCODE_DOWN:      return DupString("\x1b[1;5B");
			case SDL_SCANCODE_RIGHT:     return DupString("\x1b[1;5C");
			case SDL_SCANCODE_LEFT:      return DupString("\x1b[1;5D");
			default:                     return NULL;
		}
	}
	else if (ShiftPressed(keys)) {
		switch (key) {
			case SDL_SCANCODE_BACKSPACE: return DupString("\x7F");
			case SDL_SCANCODE_RETURN:    return DupString("\n");
			case SDL_SCANCODE_F1:        return DupString("\x1b[1;2P");
			case SDL_SCANCODE_F2:        return DupString("\x1b[1;2Q");
			case SDL_SCANCODE_F3:        return DupString("\x1b[1;2R");
			case SDL_SCANCODE_F4:        return DupString("\x1b[1;2S");
			case SDL_SCANCODE_F5:        return DupString("\x1b[15;2~");
			case SDL_SCANCODE_F6:        return DupString("\x1b[17;2~");
			case SDL_SCANCODE_F7:        return DupString("\x1b[18;2~");
			case SDL_SCANCODE_F8:        return DupString("\x1b[19;2~");
			case SDL_SCANCODE_F9:        return DupString("\x1b[20;2~");
			case SDL_SCANCODE_F10:       return DupString("\x1b[21;2~");
			case SDL_SCANCODE_F11:       return DupString("\x1b[23;2~");
			case SDL_SCANCODE_F12:       return DupString("\x1b[24;2~");
			case SDL_SCANCODE_UP:        return DupString("\x1b[1;2A");
			case SDL_SCANCODE_DOWN:      return DupString("\x1b[1;2B");
			case SDL_SCANCODE_RIGHT:     return DupString("\x1b[1;2C");
			case SDL_SCANCODE_LEFT:      return DupString("\x1b[1;2D");
			default:                     return NULL;
		}
	}
	else {
		switch (key) {
			case SDL_SCANCODE_BACKSPACE: return DupString("\x08");
			case SDL_SCANCODE_RETURN:    return DupString("\n");
			case SDL_SCANCODE_F1:        return DupString("\x1bOP");
			case SDL_SCANCODE_F2:        return DupString("\x1bOQ");
			case SDL_SCANCODE_F3:        return DupString("\x1bOR");
			case SDL_SCANCODE_F4:        return DupString("\x1bOS");
			case SDL_SCANCODE_F5:        return DupString("\x1b[15~");
			case SDL_SCANCODE_F6:        return DupString("\x1b[17~");
			case SDL_SCANCODE_F7:        return DupString("\x1b[18~");
			case SDL_SCANCODE_F8:        return DupString("\x1b[19~");
			case SDL_SCANCODE_F9:        return DupString("\x1b[20~");
			case SDL_SCANCODE_F10:       return DupString("\x1b[21~");
			case SDL_SCANCODE_F11:       return DupString("\x1b[23~");
			case SDL_SCANCODE_F12:       return DupString("\x1b[24~");
			case SDL_SCANCODE_UP:        return DupString("\x1b[A");
			case SDL_SCANCODE_DOWN:      return DupString("\x1b[B");
			case SDL_SCANCODE_RIGHT:     return DupString("\x1b[C");
			case SDL_SCANCODE_LEFT:      return DupString("\x1b[D");
			default:                     return NULL;
		}
	}
}

void HandleInputEvent(SDL_Event* e, Terminal* terminal) {
	switch (e->type) {
		case SDL_EVENT_TEXT_INPUT: {
			write(terminal->pty.master, e->text.text, strlen(e->text.text));
			break;
		}
		case SDL_EVENT_KEY_DOWN: {
			char* sequence = KeyToSequence(e->key.scancode);

			if (sequence == NULL) {
				break;
			}

			write(terminal->pty.master, sequence, strlen(sequence));
			free(sequence);
			break;
		}
	}
}
