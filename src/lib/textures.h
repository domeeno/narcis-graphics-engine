#ifndef TEXTURES_H
#define TEXTURES_H

#include "../../include/stb/stb_image.h"
#include <iostream>

unsigned char *load_texture_data(const char *path);
void free_texture_data(unsigned char *data);

#endif // TEXTURES_H
