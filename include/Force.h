#ifndef FORCE_H
#define FORCE_H
class Particle;
enum ForceType { GRAVITY, ATTRACTOR };
class Force {
protected:
  float strength;
  bool active = true;

public:
  Force(float strength);
  virtual ~Force();
  virtual void applyForce(Particle &p, float dt) = 0;
  bool isActive() { return active; }
  void setActive(bool a) { active = a; }
};

#endif // !FORCE_H
