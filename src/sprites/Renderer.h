#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include <string>

#include "../sprites/SpriteTypes.h"
#include "../log/log.h"

/* DEVELOPER: Michael Goll
** DESIGNER:  Michael Goll
** DATE:      March 14, 2017
*/

//-------- Game Screens --------
#define MAIN_SCREEN "assets/TitleScreen_Marz.png"
//#define LOBBY_SCREEN "assets/texture/Map/" //<-- Will be used at a later date to show lobby

//-------- Map Textures --------
#define MAP_TEXTURE_PATH "assets/texture/Map/"

//terraformed terrain
#define TEXTURE_DIRT   MAP_TEXTURE_PATH "dirt_grass.png"
//barren dirt
#define TEXTURE_BARREN MAP_TEXTURE_PATH "mars_dirt.png"
//dead grass
#define TEXTURE_MIDDLE MAP_TEXTURE_PATH "middle_dirt.png"

//size of the texture
#define TEXTURE_SIZE 250

//size of the marine
#define MARINE_SIZE 100

//TODO: remove these textures, temporary for now
#define TEMP_MARINE_TEXTURE "assets/texture/arrow.png"
#define TEMP_ZOMBIE_TEXTURE "assets/texture/babyz1.png"

//Sprite Sheet folder path
#define SPRITE_PATH "assets/texture/SpriteSheets/"

//-------- Map Objects Sprite Sheet --------
#define MAP_OBJECTS SPRITE_PATH "mapObjects.png"

//-------- Zombie Sprite Sheets --------
#define ZOMBIE_BABYZ  SPRITE_PATH "babyz.png"
#define ZOMBIE_DIGGER SPRITE_PATH "digger.png"
#define ZOMBIE_BOSS   SPRITE_PATH "zombieboss.png"

//-------- Marine Sprite Sheet --------
#define PLAYER_MOHAWK  SPRITE_PATH "mohawk.png"

//-------- Weapons Sprite Sheet --------
#define WEAPONS SPRITE_PATH "weapons.png"
#define LASER   SPRITE_PATH "laser.png"
//#define TURRETS        SPRITE_PATH ""

#define TOTAL_SPRITES 20 //number of total sprites

//temporary sprite, will be removed later
#define REPLACE_ME "assets/texture/replace_me.png"


class Renderer {
public:
    //returns the instance if it exists, otherwise creates one
    static Renderer * instance();
    ~Renderer();

    //returns the sprite or sprite sheet that the object is looking to render
    static SDL_Texture * getTexture(int spriteType) {return _sprites.at(spriteType);};
    //gets the renderer
    static SDL_Renderer * getRenderer() {return _renderer;};
    //sets the window
    static void setWindow(SDL_Window * window);
    //loads all the sprites specified in Renderer.h
    static void loadSprites();

    static TTF_Font * loadFont(std::string fonts, int size);

    //creates a texture from a font file
    void createText(TTF_Font * font, std::string text, SDL_Color colour);

    //renders all of the sprites within the camera viewport

    static void render(const SDL_Rect& dest, TEXTURES spriteType, double angle = 0.0,
        SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    static void render(const SDL_Rect& dest, TEXTURES spriteType, const SDL_Rect& clip,
        double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);


private:
    Renderer(){}

    static Renderer * rInstance;
    static SDL_Renderer * _renderer;
    static SDL_Window * _window;
    static int _index;

    //array of all sprites in the game
    static std::array<SDL_Texture *, TOTAL_SPRITES> _sprites;
    //creates a texture from a file
    static void createTexture(std::string filePath);
    //sets the renderer
    static void setRenderer();
};

#endif