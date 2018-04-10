#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace acherep;

int main() {
  srand(time(NULL));
  Screen screen;

  if (screen.init() == false) {
    cout << "Error initializing SDL" << endl;
    return 1;
  }

  Swarm swarm;

  while (true) {
    const Particle* const pParticles = swarm.getParticles();
    int elapsed = SDL_GetTicks();

    swarm.update(elapsed);

    unsigned char red = (unsigned char)((sin(elapsed * 0.0001) + 1) * 128);
    unsigned char green = (unsigned char)((sin(elapsed * 0.0002) + 1) * 128);
    unsigned char blue = (unsigned char)((sin(elapsed * 0.0003) + 1) * 128);

    for (int i = 0; i < Swarm::NPARTICLES; i++) {
      Particle particle = pParticles[i];

      int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
      int y =
          particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

      screen.setPixel(x, y, red, green, blue);
    }
    screen.boxBlur();
    screen.update();
    if (screen.processEvents() == false) {
      break;
    }
  }

  screen.close();

  return 0;
}