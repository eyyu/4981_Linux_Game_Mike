#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include<SDL2/SDL.h>
#include "Marine.h"
#include "Turret.h"
#include "CollisionHandler.h"
#include "Object.h"
#include "Zombie.h"
#include "Barricade.h"
#include <map>
#include <unordered_map>
#include <vector>
#include "WeaponDrop.h"
#include <memory>
#include "SpriteTypes.h"
#include "Renderer.h"

//just for tesing weapon drop
#include "Weapon.h"
#include "HandGun.h"
#include "Rifle.h"
#include "ShotGun.h"

class GameManager {
public:
    static GameManager *instance();
    ~GameManager();

    void renderObjects(int camX, int camY, int camW, int camH); // Render all objects in level

    // Methods for creating, getting, and deleting marines from the level.
    unsigned int createMarine();
    bool createMarine(float x, float y);
    void deleteMarine(unsigned int id);

    bool addMarine(unsigned int id, Marine& newMarine);
    Marine& getMarine(unsigned int id);

    // Methods for creating, getting, and deleting towers from the level.
    unsigned int createTurret();
    void deleteTurret(unsigned int id);

    bool addTurret(unsigned int id, Turret& newTurret);
    bool createTurret(float x, float y) ;
    Turret& getTurret(unsigned int id);

    // Method for getting collisionHandler
    CollisionHandler& getCollisionHandler();

    void updateCollider(); // Updates CollisionHandler
    void updateMarines(const float& delta); // Update marine actions
    void updateZombies(const float& delta); // Update zombie actions

    unsigned int addObject(Object&);
    void deleteObject(unsigned int id);

    unsigned int addZombie(Zombie&);
    bool createZombie(float x, float y);
    void deleteZombie(unsigned int id);

    unsigned int addWeaponDrop(WeaponDrop& newWeaponDrop);
    bool createWeaponDrop(float x, float y);
    void deleteWeaponDrop(unsigned int id);

    unsigned int createBarricade(float x, float y);
    void deleteBarricade(unsigned int id);
    Barricade& getBarricade(unsigned int id);
private:
    static GameManager *sInstance;

    GameManager();
    CollisionHandler collisionHandler;
    std::unique_ptr<WeaponDrop> wdPointer;
    std::map<unsigned int, Marine> marineManager;
    std::map<unsigned int, Object> objectManager;
    std::map<unsigned int, Zombie> zombieManager;
    std::map<unsigned int, Turret> turretManager;
    std::map<unsigned int, WeaponDrop> weaponDropManager;
    std::map<unsigned int, Barricade> barricadeManager;

};


#endif
