#include "textures.h"
#include <cstdio>

unsigned char *load_texture_data(const char *path) {
  FILE *f = fopen(path, "rb");

  if (f == NULL) {
    std::cerr << "unable to load file" << std::endl;
  }

  int w, h, nr_channels;
  unsigned char *data = stbi_load_from_file(f, &w, &h, &nr_channels, 0);

  if (data == NULL) {
    std::cerr << "unable to load texture" << std::endl;
  }

  fclose(f);

  return data;
}

void free_texture_data(unsigned char *data) { stbi_image_free(data); }
