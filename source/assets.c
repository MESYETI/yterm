#include "util.h"
#include "assets.h"
#include "config.h"

// assets
#include "assets/basil_8x8.h"
#include "assets/default_7x16.h"
#include "assets/trinity_12x18.h"

typedef struct {
	const char*    fileName;
	const uint8_t* contents;
	size_t         size;
} Asset;

void WriteAssets(void) {
	Asset assets[] = {
		{
			.fileName = "fonts/basil_8x8.bmp",
			.contents = assets_basil_8x8_bmp,
			.size     = assets_basil_8x8_bmp_len
		},
		{
			.fileName = "fonts/default_7x16.bmp",
			.contents = assets_default_7x16_bmp,
			.size     = assets_default_7x16_bmp_len
		},
		{
			.fileName = "fonts/trinity_12x18.bmp",
			.contents = assets_trinity_12x18_bmp,
			.size     = assets_trinity_12x18_bmp_len
		}
	};

	for (size_t i = 0; i < ARRAY_LEN(assets); ++ i) {
		Asset* asset = &assets[i];

		char assetPath[2048];
		strcpy(assetPath, GetConfigPath());
		strcat(assetPath, asset->fileName);

		FILE* file = fopen(assetPath, "wb");

		if (file == NULL) {
			FATAL("Failed to open file '%s': %s\n", assetPath, strerror(errno));
		}

		fwrite(asset->contents, 1, asset->size, file);
		fclose(file);
	}
}
