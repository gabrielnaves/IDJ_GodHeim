/*
 * HpBar.h
 *
 *  Created on: Jul 5, 2014
 *      Author: icaro
 */

#ifndef HPBAR_H_
#define HPBAR_H_

#include "../../../Engine.h"

class HpBar : public GameObject
{
  public:
	HpBar(std::string sprite, std::string character, int x, int y);
	virtual ~HpBar();
	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void Empty();
	void Fill();
	std::string GetSp();
	std::string GetCharacter();
  private:
	Sprite sp;
	std::string character, sprite;
	bool full, fill, empty;
};

#endif /* HPBAR_H_ */
