#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace acherep {
struct Particle {
 private:
  double m_speed;
  double m_direction;
  void init();

 public:
  const static double MAX_SPEED = 0.04;
  double m_x;
  double m_y;
  Particle();
  void update(int timeInterval);
};
}  // namespace acherep

#endif  // PARTICLE_H_