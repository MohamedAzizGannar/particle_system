#include "Force.h"

Force::Force(float strength) : strength(strength) {}
Force::~Force() = default;
void Force::setStrength(float new_strength) { strength = new_strength; }
