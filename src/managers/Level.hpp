//
// Created by elsa on 14.04.2020.
//

#ifndef TREFUSISENGINE_LEVEL_H
#define TREFUSISENGINE_LEVEL_H

#include <iostream>
#include <string>
#include <vector>

/**
 * Represents the reading mode the parser is in.
 */
enum ReadingMode { LEVEL, ZONE, TILE, FOILAGE };

/**
 * Enviromental actor structure.
 */
struct envActor {
    int id;     // ID of the actor.
    int width;  // Width of the actor in spritesheet.
    int height; // Height of the actor in spritesheet.
};

/**
 * Holds the spawn probability rule objects for one zone.
 */
struct zoneProbability {
    int tileCount;                      // Tile count.
    int foilageCount;                   // Foilage count.
    std::vector<double> tileChances;    // Tile spawn chances.
    std::vector<double> foilageChances; // Foilage spawn chances.
    std::vector<envActor> tiles;        // Tiles.
    std::vector<envActor> foilages;     // Foilages.
};

/**
 * Holds the spawn probability rule objects for one level.
 */
struct levelProbability {
    std::string levelName;                          // Name of the level.
    std::vector<std::vector<int>> zoneMatrix;       // Zone IDs as a matrix
    int zoneCount;                                  // Count of zones.
    std::vector<zoneProbability> zoneProbabilities; // Zone probability objects for each zone.
};

/**
 * Holds the probability objects for all levels.
 */
struct levelProbabilities {
    int levelCount;                              // Count of levels.
    std::vector<std::string> levelNames;         // Name of levels.
    std::vector<levelProbability> probabilities; // Probability objects for each level.
};

/**
 * Copy an enviromental actor instance and return its copy. This may not be necessary, however I have no time to test
 * So I am being defensive.
 * @param ptr Pointer to the object.
 * @return Its clone.
 */
inline envActor copyEnvActor(envActor *ptr);

/**
 * Generate a tile given zone probability object.
 * @param zp Zone probability object containing rules to generate the tile.
 * @return The generated tile.
 */
inline envActor generateTile(zoneProbability *zp);

/**
 * Generate foilage given zone probability object.
 * @param zp Zone probability object to generate foilage for.
 * @return the generated foilage object.
 */
inline envActor generateFoilage(zoneProbability *zp);

/**
 * Generate an enviromental actor object given
 * @param referanceVector The vector holding possible enviromental objects.
 * @param probabilityVector Probability vector holding their spawn chance.
 * @return
 */
inline envActor generateEnvActor(std::vector<envActor> referanceVector, std::vector<double> probabilityVector);
class Level {
  private:
    /**
     * Normal constructor for level.
     */
    Level();
    /**
     * Copy constructor.
     * @param lp
     */
    Level(Level *lp);
    static std::vector<Level> levels; // Holds all the levels.
    /**
     * Import the spawn probabilities for levels.
     * @param lp Level probabilities object.
     * @param fileName Name of the file.
     */
    static void importLevelProbabilities(levelProbabilities *lp, const char *fileName);
    /**
     * Import the zone matrix for a level.
     * @param lpp Level probability pointer to import to.
     */
    static void importLevelZoneMatrix(levelProbability *lpp);
    /**
     * Generate the enviromental actors for all levels.
     * @param probabilities Probabilities container for all levels.
     */
    static void generateEnviromentalActors(levelProbabilities *probabilities);
    /**
     * Smoothen the tiles for all levels. RIP Conway.
     */
    static void smoothTiles();

  public:
    std::vector<std::vector<envActor>> foilageMatrix;
    std::vector<std::vector<envActor>> tileMatrix;
    static Level activeLevel;
    /**
     * Given a vector of level names, import the levels.
     * @return the level probabilities object.
     */
    static levelProbabilities importLevels();
    /**
     * Change the active level
     * @param levelIndex New active level's index.
     */
    static void changeLevel(int levelIndex);
};

#endif // TREFUSISENGINE_LEVEL_H
