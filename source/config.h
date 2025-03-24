#ifndef YTERM_CONFIG_H
#define YTERM_CONFIG_H

#include "sdl.h"
#include "util.h"
#include "components.h"
#include "textScreen.h"

#define CONFIG_FOLDER "/.config/yterm/"
#define CONFIG_FILE   "config.json"
#define THEME_FOLDER  "themes/"
#define FONTS_FOLDER  "fonts/"

const char* GetConfigPath(void);
void        LoadConfig(ColourScheme* colourScheme, Video* video);

#endif
