#include "GameManager.h"
#include "HitBox.h"
#include <memory>
#include <utility>

GameManager *GameManager::sInstance;
Weapon w;
//Returns the already existing GameManager or if there isn't one, makes
//a new one and returns it.
GameManager *GameManager::instance() {
    if (!sInstance)
        sInstance = new GameManager;
    return sInstance;
}

GameManager::GameManager():collisionHandler() {
    printf("Create GM\n");
}

GameManager::~GameManager() {

    printf("Destroy GM\n");
    marineManager.clear();
    zombieManager.clear();
    objectManager.clear();
    turretManager.clear();
    weaponDropManager.clear();
}

// Render all objects in level

void GameManager::renderObjects(int camX, int camY, int camH, int camW) {

    for (const auto& m : weaponDropManager) {
        if (m.second.getX() - camX < camW) {
            if (m.second.getY() - camY < camH) {
                    Renderer::instance()->render(m.second.getX() - camX, m.second.getY() - camY,
                                                 MARINE_SIZE, MARINE_SIZE, TEXTURES::CONCRETE);
            }
        }
    }

    for (const auto& m : marineManager) {
         if (m.second.getX() - camX < camW) {
             if (m.second.getY() - camY < camH) {
                     Renderer::instance()->render(m.second.getX() - camX, m.second.getY() - camY,
                                                  MARINE_SIZE, MARINE_SIZE, TEXTURES::MARINE, NULL,
                                                  m.second.getAngle());
             }
         }
    }


    for (const auto& o : objectManager) {
        if (o.second.getX() < camW) {
            if (o.second.getY() - camY < camH) {
                    Renderer::instance()->render(o.second.getX() - camX, o.second.getY() - camY,
                                                 MARINE_SIZE, MARINE_SIZE, TEXTURES::MARINE);
            }
        }
    }

    for (const auto& z : zombieManager) {
        if (z.second.getX() - camX < camW) {
            if (z.second.getY() - camY < camH) {
                    Renderer::instance()->render(z.second.getX() - camX, z.second.getY() - camY,
                                                 75, 125, TEXTURES::BABY_ZOMBIE);
            }
        }
    }

    for (const auto& m : turretManager) {
        if (m.second.getX() - camX < camW) {
            if (m.second.getY() - camY < camH) {
                    Renderer::instance()->render(m.second.getX() - camX, m.second.getY() - camY,
                                                 MARINE_SIZE, MARINE_SIZE, TEXTURES::CONCRETE,
                                                 NULL, m.second.getAngle());
            }
        }
    }

    for (const auto& b : barricadeManager) {
        if (b.second.getX() - camX < camW) {
            if (b.second.getY() - camY < camH) {
                    Renderer::instance()->render(b.second.getX() - camX, b.second.getY() - camY,
                                                 MARINE_SIZE, MARINE_SIZE, TEXTURES::CONCRETE);
            }
        }
    }
}

// Update marine movements. health, and actions
void GameManager::updateMarines(const float& delta) {
    for (auto& m : marineManager) {
        m.second.move((m.second.getDX()*delta), (m.second.getDY()*delta), collisionHandler);
    }
}

// Update zombie movements.
void GameManager::updateZombies(const float& delta) {
    for (auto& z : zombieManager) {
        z.second.generateRandomMove();
        z.second.move((z.second.getDX()*delta), (z.second.getDY()*delta), collisionHandler);
    }
}
// Create marine add it to manager, returns marine id
unsigned int GameManager::createMarine() {
    unsigned int id = 0;
    if (!marineManager.empty()) {
        id = marineManager.rbegin()->first + 1;
    }
    marineManager[id] = Marine();
    return id;
}

bool GameManager::createMarine(float x, float y){
    unsigned int id = 0;
    if (!marineManager.empty()) {
        id = marineManager.rbegin()->first + 1;
    }
    marineManager[id] = Marine();
    marineManager[id].setPosition(x,y);
    return true;
}

void GameManager::deleteMarine(unsigned int id) {
    marineManager.erase(id);
}


// Adds marine to level
bool GameManager::addMarine(unsigned int id, Marine& newMarine) {
    if (marineManager.count(id)) {
        return false;
    } else {
        marineManager[id] = newMarine;
        return true;
    }
}

// Get a marine by its id
Marine& GameManager::getMarine(unsigned int id) {
    return marineManager.find(id)->second;
}

// Create Turret add it to manager, returns tower id
unsigned int GameManager::createTurret() {
    unsigned int id = 0;
    if (!turretManager.empty()) {
        id = turretManager.rbegin()->first + 1;
    }
    turretManager[id] = Turret();
    return id;
}

// Deletes tower from level
void GameManager::deleteTurret(unsigned int id) {
    turretManager.erase(id);
}

// Adds tower to level
bool GameManager::addTurret (unsigned int id, Turret& newTurret) {
    if (turretManager.count(id)) {
        return false;
    } else {
        turretManager[id] = newTurret;
        return true;
    }
}

// Create turret add it to truret, returns if success
bool GameManager::createTurret(float x, float y) {
    unsigned int id = 0;
    if (!turretManager.empty()) {
        id = turretManager.rbegin()->first + 1;
    }
    turretManager[id] = Turret();
    turretManager.at(id).setPosition(x,y);
    return true;
}

// Get a tower by its id
Turret& GameManager::getTurret(unsigned int id) {
    return turretManager.find(id)->second;
}

unsigned int GameManager::addZombie(Zombie& newZombie) {
    unsigned int id = 0;
    if (!zombieManager.empty()) {
        id = zombieManager.rbegin()->first + 1;
    }
    zombieManager[id] = newZombie;
    return id;
}

// Create zombie add it to manager, returns success
bool GameManager::createZombie(float x, float y) {
    unsigned int id = 0;
    if (!zombieManager.empty()) {
        id = zombieManager.rbegin()->first + 1;
    }
    zombieManager[id] = Zombie();
    zombieManager.at(id).setPosition(x,y);
    return true;
}

// Deletes zombie from level
void GameManager::deleteZombie(unsigned int id) {
    zombieManager.erase(id);
}

unsigned int GameManager::addObject(Object& newObject) {
    unsigned int id = 0;
    if (!objectManager.empty()) {
        id = objectManager.rbegin()->first + 1;
    }
    objectManager[id] = newObject;
    return id;
}

// Deletes Object from level
void GameManager::deleteObject(unsigned int id) {
    objectManager.erase(id);
}

unsigned int GameManager::addWeaponDrop(WeaponDrop& newWeaponDrop) {
    unsigned int id = 0;
    if (!weaponDropManager.empty()) {
        id = weaponDropManager.rbegin()->first + 1;
    }
    weaponDropManager.insert(std::make_pair(id, newWeaponDrop));
    return id;
}

// Create weapon drop add it to manager, returns success
bool GameManager::createWeaponDrop(float x, float y) {
    int id;
    int randGun = rand() % 2 + 1;

    if(randGun == 1){
        w = Rifle();
    } else if(randGun == 2){
        w = ShotGun();
    }

    if (!zombieManager.empty()) {
        id = zombieManager.rbegin()->first + 1;
    }

    weaponDropManager.insert(std::make_pair(id, WeaponDrop(w)));

    weaponDropManager.at(id).setPosition(x,y);
    return true;
}

// Deletes weapon from level
void GameManager::deleteWeaponDrop(unsigned int id) {
    weaponDropManager.erase(id);
}

// Returns Collision Handler
CollisionHandler& GameManager::getCollisionHandler() {
    return collisionHandler;
}

// Update colliders to current state
void GameManager::updateCollider() {

    delete collisionHandler.quadtreeMov;
    delete collisionHandler.quadtreePro;
    delete collisionHandler.quadtreeDam;
    delete collisionHandler.quadtreePickUp;

    collisionHandler.quadtreeMov = new Quadtree(0, {0,0,2000,2000});
    collisionHandler.quadtreePro = new Quadtree(0, {0,0,2000,2000});
    collisionHandler.quadtreeDam = new Quadtree(0, {0,0,2000,2000});
    collisionHandler.quadtreePickUp = new Quadtree(0, {0,0,2000,2000});

    for (auto& m : marineManager) {
        collisionHandler.quadtreeMov->insert(m.second.movementHitBox.get());
        collisionHandler.quadtreePro->insert(m.second.projectileHitBox.get());
        collisionHandler.quadtreeDam->insert(m.second.damageHitBox.get());
    }

    for (auto& z : zombieManager) {
        collisionHandler.quadtreeMov->insert(z.second.movementHitBox.get());
        collisionHandler.quadtreePro->insert(z.second.projectileHitBox.get());
        collisionHandler.quadtreeDam->insert(z.second.damageHitBox.get());
    }

    for (auto& o : objectManager) {
        collisionHandler.quadtreeMov->insert(o.second.movementHitBox.get());
        collisionHandler.quadtreePro->insert(o.second.projectileHitBox.get());
        collisionHandler.quadtreeDam->insert(o.second.damageHitBox.get());
    }

    for (auto& m : turretManager) {
        collisionHandler.quadtreeMov->insert(m.second.movementHitBox.get());
        collisionHandler.quadtreePro->insert(m.second.projectileHitBox.get());
        collisionHandler.quadtreeDam->insert(m.second.damageHitBox.get());
    }

    for (auto& b : barricadeManager) {
        if(b.second.isPlaced()) {
            collisionHandler.quadtreeMov->insert(b.second.movementHitBox.get());
            collisionHandler.quadtreeDam->insert(b.second.damageHitBox.get());
        }
 }

    for (auto& m : weaponDropManager) {
        collisionHandler.quadtreePickUp->insert(m.second.pickupHitBox.get());
    }

}

// Create barricade add it to manager, returns success
unsigned int GameManager::createBarricade(float x, float y) {
    unsigned int id = 0;
    if (!barricadeManager.empty()) {
        id = barricadeManager.rbegin()->first + 1;
    }
    barricadeManager[id] = Barricade();
    barricadeManager.at(id).setPosition(x,y);
    return id;
}


void GameManager::deleteBarricade(unsigned int id) {
    barricadeManager.erase(id);
}
// Get a barricade by its id
Barricade& GameManager::getBarricade(unsigned int id) {
    return barricadeManager.find(id)->second;
}
