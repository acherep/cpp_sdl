#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace acherep {
struct Particle {
  const static double MAX_SPEED = 0.0001;
  double m_x;
  double m_y;

  double m_speed;
  double m_direction;

  Particle();
  void update(int timeInterval);
};
}  // namespace acherep

#endif  // PARTICLE_H_