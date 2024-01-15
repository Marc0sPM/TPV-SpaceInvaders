#pragma once
#include "Alien.h"


class ShooterAlien: public Alien
{
private:
	int reloadTime;
public:
	ShooterAlien(PlayState* playState, std::istream& entrada, Texture* texture, Mothership* mothership);
	void update() override;
	void save(std::ostream& os) const override;
	int getReloadTime() const {
		return reloadTime;
	}
};

