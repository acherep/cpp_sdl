#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace acherep {
struct Particle {
  double m_x;
  double m_y;

  double xspeed;
  double yspeed;

 public:
  Particle();
  void update();
};
}  // namespace acherep

#endif  // PARTICLE_H_