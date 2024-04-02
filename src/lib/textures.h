#ifndef TEXTURES_H
#define TEXTURES_H

#include "../../include/stb/stb_image.h"
#include <iostream>


class Texture
{
  public:
    int width, height, nrOfChannels;
    unsigned char *data;
    Texture(const char *path);
    ~Texture();
};

#endif // TEXTURES_H
