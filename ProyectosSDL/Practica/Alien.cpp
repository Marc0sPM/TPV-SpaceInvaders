#include "Alien.h"

Alien::Alien() : pos(), textura(), subtipo(), game() {}
Alien::Alien(Point2D<int> _pos, Texture _textura, int _subtipo, Game* _game): 
pos(_pos),
textura(_textura),
subtipo(_subtipo),
game(_game)
 {};
