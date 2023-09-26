//
// Created by elsa on 13.04.2020.
//

#ifndef HAILMARY_GAMEMANAGER_HPP
#define HAILMARY_GAMEMANAGER_HPP

#include "Character.hpp"
#include "DialogManager.hpp"
#include "GraphicsManager.hpp"
#include "Player.hpp"
#include "ScriptManager.hpp"
#include "TimeManager.hpp"
#include <string>
#include <vector>
/**
 * A singleton class, GameManager has only one active instance at any given time.
 */
class GameManager {
  private:
    std::vector<Character> characters;
    TimeManager timeManager;
    GraphicsManager graphicsManager;
    SDL_Event e;
    bool displayDialog = false;
    Dialog currentDialog{"", ""};
    static GameManager *game;
    ScriptManager harlequin;
    Player *player;
    /**
     * Move the player in given directions.
     * @param x movement in x direction.
     * @param y movement in y direction.
     */
    void movePlayer(float x, float y);
    /**
     * Track the objects.
     */
    void trackObjects();
    /**
     * Stub method to load the first scene for the first Milestone test.
     */
    void loadFirstScene();
    /**
     * Handle the key presses by the user.
     */
    void handleKeys();
    /**
     * Check if player is still inside the map after move.
     * @param x Move in x direction.
     * @param y Move in y direction.
     * @return If the player is still inside bounds.
     */
    bool inline playerIsInsideMapAfterMove(float x, float y);
    /**
     * Check if the player's desired location is blocked.
     * @param dx Movement in x.
     * @param dy Movement in y.
     * @return If p.x + dx, p.y + dy is blocked.
     */
    bool inline playerIsBlockedAfterMove(float dx, float dy);
    /**
     * Handles the display and process of dialog.
     */
    void handleDialog();
    /**
     * Initialise a gamemanager instance.
     */
    GameManager();

  public:
    /**
     * Show the splash screen.
     */
    void showSplashScreen();
    bool quit;
    /**
     * Main loop of the game.
     */
    void Update();
    /**
     * Get the instance of the gamemaneger.
     * @return Only instance of the game manager.
     */
    static GameManager getInstance();
    /**
     * Close the game manager. Release used resources.
     */
    void close();
};

#endif // HAILMARY_GAMEMANAGER_HPP