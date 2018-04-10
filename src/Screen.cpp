#include "Screen.h"

namespace acherep {

Screen::Screen()
    : m_window(NULL),
      m_renderer(NULL),
      m_texture(NULL),
      m_buffer(NULL),
      m_blur_buffer(NULL) {}

bool Screen::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  }

  m_window = SDL_CreateWindow("Particle Fire Explosion",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (m_window == NULL) {
    SDL_Quit();
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

  if (m_renderer == NULL) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  m_texture =
      SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (m_texture == NULL) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
  m_blur_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

  memset(m_buffer, INITIAL_SCREEN_COLOR,
         SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  memset(m_blur_buffer, INITIAL_SCREEN_COLOR,
         SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

  return true;
}

void Screen::update() {
  SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
  SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }

  Uint32 color = 0;
  color += red;
  color <<= 8;
  color += green;
  color <<= 8;
  color += blue;
  color <<= 8;
  color += 0xFF;

  m_buffer[y * SCREEN_WIDTH + x] = color;
}

bool Screen::processEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }
  }
  return true;
}

void Screen::boxBlur() {
  // Swap the buffers
  Uint32 *pTempBuffer;

  pTempBuffer = m_buffer;
  m_buffer = m_blur_buffer;
  m_blur_buffer = pTempBuffer;

  for (int y = 1; y < SCREEN_HEIGHT - 1; y++) {
    for (int x = 1; x < SCREEN_WIDTH - 1; x++) {
      // the idea is to average the color (red, green, blue) of the pixel and
      // pixels around it
      // 0 0 0
      // 0 1 0
      // 0 0 0
      int redTotal = 0;
      int greenTotal = 0;
      int blueTotal = 0;

      for (short row = -1; row <= 1; row++) {
        for (short column = -1; column <= 1; column++) {
          int currentX = x + column;
          int currentY = y + row;

          Uint32 color = m_blur_buffer[currentY * SCREEN_WIDTH + currentX];

          Uint8 red = color >> 24;
          Uint8 green = color >> 16;
          Uint8 blue = color >> 8;

          redTotal += red;
          greenTotal += green;
          blueTotal += blue;
        }
      }
      Uint8 red = redTotal / 9;
      Uint8 green = greenTotal / 9;
      Uint8 blue = blueTotal / 9;
      setPixel(x, y, red, green, blue);
    }
  }
}

void Screen::close() {
  delete[] m_buffer;
  delete[] m_blur_buffer;
  SDL_DestroyTexture(m_texture);
  SDL_DestroyRenderer(m_renderer);

  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

}  // namespace acherep
