#include <time.h>
#include <stdarg.h>
#include "util.h"
#include "safe.h"

void DumpSequence(char* seq) {
	for (size_t i = 0; i < strlen(seq); ++ i) {
		switch (seq[i]) {
			case '\x1b': {
				fputs("\\e", stdout);
				break;
			}
			default: {
				putchar(seq[i]);
			}
		}
	}
	putchar('\n');
}

bool StringStartsWith(char* str, char* with) {
	if (strlen(with) > strlen(str)) {
		return false;
	}

	return memcmp(str, with, strlen(with)) == 0;
}

bool StringIsNumeric(char* str) {
	for (size_t i = 0; i < strlen(str); ++ i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}

	return true;
}

char* DupString(char* str) {
	char* ret = SafeMalloc(strlen(str) + 1);
	strcpy(ret, str);
	return ret;
}

char* CharToString(char ch) {
	char ret[] = {ch, 0};
	return DupString(ret);
}

bool HexToColour(const char* colour, SDL_Color* ret) {
	assert(ret != NULL);

	char* ptr;
	uint32_t colour32 = (uint32_t) strtol(colour, &ptr, 16);
	if (*ptr != '\0')
		return false;

	ret->r = (colour32 >> 16) & 0xFF;
	ret->g = (colour32 >> 8)  & 0xFF;
	ret->b = colour32         & 0xFF;
	ret->a = 255;

	return true;
}

char* GetUserShell(void) {
	struct passwd* data = getpwuid(geteuid());

	if (data == NULL) {
		perror("getpwuid");
		FATAL("Failed to get passwd data");
	}

	return data->pw_shell;
}
void Log(const char* format, ...) { // most of this is taken from vsprintf(3)
	int     n    = 0;
	size_t  size = 0;
	char*   ret  = NULL;
	va_list ap;

	// Determine required size
	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		return;
	}

	size = n + 1; // One extra byte for '\0'
	ret = (char*) SafeMalloc(size);
	if (ret == NULL) {
		return;
	}

	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		free(ret);
		return;
	}

	time_t     rawTime;
	struct tm* tm;
	
	time(&rawTime);
	tm = localtime(&rawTime);
	
	printf("[%.2d:%.2d:%.2d] %s\n", tm->tm_hour, tm->tm_min, tm->tm_sec, ret);
	free(ret);
}

void Error(const char* format, ...) { // most of this is taken from vsprintf(3)
	int     n    = 0;
	size_t  size = 0;
	char*   ret  = NULL;
	va_list ap;

	// Determine required size
	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		return;
	}

	size = n + 1; // One extra byte for '\0'
	ret = (char*) SafeMalloc(size);
	if (ret == NULL) {
		return;
	}

	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		free(ret);
		return;
	}

	time_t     rawTime;
	struct tm* tm;
	
	time(&rawTime);
	tm = localtime(&rawTime);
	
	printf("[%.2d:%.2d:%.2d] %s\n", tm->tm_hour, tm->tm_min, tm->tm_sec, ret);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", ret, NULL);
	exit(1);
}
