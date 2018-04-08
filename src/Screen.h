#ifndef SCREEN_H_

#define SCREEN_H_

#include <SDL2/SDL.h>

namespace acherep {

class Screen {
 public:
  static const int SCREEN_WIDTH = 800;
  static const int SCREEN_HEIGHT = 600;
  static const int SCREEN_COLOR = 0;

 private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
  Uint32 *m_buffer;

 public:
  Screen();
  bool init();
  void update();
  void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
  bool processEvents();
  void close();
};

}  // namespace acherep

#endif  // SCREEN_H_