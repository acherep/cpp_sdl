#include <SDL2/SDL.h>
#include <iostream>
#include "Screen.h"

using namespace std;
using namespace acherep;

int main() {
  Screen screen;

  if (screen.init() == false) {
    cout << "Error initializing SDL" << endl;
    return 1;
  }

  while (true) {
    for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
      for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
        screen.setPixel(x, y, 128, 128, 0);
      }
    }

    screen.setPixel(400, 300, 255, 255, 255);
    screen.update();
    if (screen.processEvents() == false) {
      break;
    }
  }

  screen.close();

  return 0;
}