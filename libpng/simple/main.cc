#include <png.h>

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <cassert>

uint32_t xorshift32() {
  static uint32_t x = 314159265;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

struct RGBA_Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
  
  RGBA_Color() {
    uint32_t rand_val = xorshift32();
    uint8_t* color_vals = reinterpret_cast<uint8_t*>(&rand_val);
    red = color_vals[0];
    green = color_vals[1];
    blue = color_vals[2];
    alpha = 255;
  }
};

int main(void) {  
  png_image* image = new png_image;
  memset(image, '\0', sizeof(png_image));
  
  int width = 800;
  int height = 600;
  
  image->version = PNG_IMAGE_VERSION;
  image->width = width;
  image->height = height;
  image->format = PNG_FORMAT_RGBA;
  image->flags = 0;
  image->opaque = NULL;
  image->colormap_entries = 0;
  
  RGBA_Color* image_data = new RGBA_Color[height * width];
  
  int ret = png_image_write_to_file(
      image,
      "example.png",
      0,
      image_data,
      0,
      NULL
  );
  
  assert(ret == 1);
  
  png_image_free(image);
  delete image;
  
  return EXIT_SUCCESS;
}
