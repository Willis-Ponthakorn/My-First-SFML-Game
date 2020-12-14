#ifndef MONSTER_H
#define MONSTER_H

enum MonsterTypes {MONSTERDEFAULT = 0, JUSTIDLE, WALKING, RANDOMJUMPIDLE, RANDOMJUMPWALKING};

#include "Entity.h"
class Monster :
    public Entity
{
private:
    short type;

    void initVariables();
    void initComponents();

public:
    Monster(float x, float y, sf::Texture& texture_sheet, short type = MonsterTypes::MONSTERDEFAULT);
    virtual ~Monster();

    const short& getType() const;

    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);
};

#endif

