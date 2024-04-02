#include "textures.h"

Texture::Texture(const char *path) {
  FILE *f = fopen(path, "rb");

  if (f == NULL) {
    std::cerr << "unable to load file" << std::endl;
  }

  data = stbi_load_from_file(f, &width, &height, &nrOfChannels, 0);

  if (data == NULL) {
    std::cerr << "unable to load texture" << std::endl;
  }

  fclose(f);
}

Texture::~Texture() { stbi_image_free(data); }
