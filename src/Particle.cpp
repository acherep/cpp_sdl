#include "Particle.h"
#include <math.h>
#include <stdlib.h>

namespace acherep {
Particle::Particle() : m_x(0), m_y(0) {
  m_direction = 2 * M_PI * rand() / RAND_MAX;
  m_speed = MAX_SPEED * rand() / RAND_MAX;
}

void Particle::update(int timeInterval) {
  m_x += m_speed * cos(m_direction) * timeInterval;
  m_y += m_speed * sin(m_direction) * timeInterval;
}
}  // namespace acherep