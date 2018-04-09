#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace acherep {
class Swarm {
 public:
  static const int NPARTICLES = 5000;

 private:
  Particle* m_pParticles;
  int m_lastTime;

 public:
  Swarm();
  ~Swarm();

  const Particle* getParticles() { return m_pParticles; };

  void update(int elapsed);
};
}  // namespace acherep

#endif  // SWARM_H_