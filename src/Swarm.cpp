#include "Swarm.h"

namespace acherep {
Swarm::Swarm() : m_lastTime(0) { m_pParticles = new Particle[NPARTICLES]; }
Swarm::~Swarm() { delete[] m_pParticles; }

void Swarm::update(int elapsed) {
  int timeInterval = elapsed - m_lastTime;
  for (int i = 0; i < Swarm::NPARTICLES; i++) {
    m_pParticles[i].update(timeInterval);
  }
  m_lastTime = elapsed;
};
}  // namespace acherep