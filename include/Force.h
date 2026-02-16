#ifndef FORCE_H
#define FORCE_H
class Particle;
class Renderer;
enum ForceType { GRAVITY, ATTRACTOR };
class Force {
protected:
  float strength;
  bool active = true;

public:
  Force(float strength);
  virtual ~Force();
  virtual void applyForce(Particle &p, float dt) = 0;
  virtual void render(Renderer &renderer) const {};

  bool isActive() { return active; }
  void setActive(bool a) { active = a; }

  void setStrength(float new_strength);
};

#endif // !FORCE_H
