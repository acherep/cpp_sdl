#include "Particle.h"
#include <math.h>
#include <stdlib.h>

namespace acherep {
Particle::Particle() { init(); }

void Particle::init() {
  m_x = 0;
  m_y = 0;
  m_direction = 2 * M_PI * rand() / RAND_MAX;
  m_speed = MAX_SPEED * rand() / RAND_MAX;

  m_speed = m_speed * m_speed;
}

void Particle::update(int timeInterval) {
  // rotation
  m_direction += timeInterval * 0.0003;

  m_x += m_speed * cos(m_direction) * timeInterval;
  m_y += m_speed * sin(m_direction) * timeInterval;
  // reinitialize the particle when it runs out of the edge of the screen
  if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
    init();
  }
  // randomly reinitialize the particle
  if (rand() < RAND_MAX / 100) {
    init();
  }
}
}  // namespace acherep