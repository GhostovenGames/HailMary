//
// Created by elsa on 14.04.2020.
//

#ifndef TREFUSISENGINE_ZONE_H
#define TREFUSISENGINE_ZONE_H


#include "../../objects/EnviromentalActor.h"
#include <iostream>
#include <string>
#include <vector>

/**
 * A zone's probabilities for tile generation.
 */
struct zoneProbability {
    std::vector<int> ids {};  // IDs of the tiles.
    std::vector<double> lowerBounds {};  // Lower bounds of the tiles spawn probability.
    std::vector<double> higherBounds {};  // Higher bounds of the tiles spawn probability.
};

void copyZoneProbabilities(zoneProbability* self, zoneProbability* other);

/**
 * Allocate memory for a zone probability structure.
 * @param zp ZP pointer.
 * @param mallocSize Memory allocation multiplier.

void mallocZoneProbability(zoneProbability* zp, int mallocSize);
*/
struct foilage {
    int id; //id of the foilage object
    int chance; //chance of the foilage object, this variable may be different for different zones
};

class Zone {
private:
    zoneProbability tileSpawnProbability;
    void copyProbabilities(Zone* otherZone);
    /**
     * Import a single zone given its file name.
     * @param fileName File name of the zone.
     * @return The newly created zone object.
     */
    static Zone importZone(std::string fileName);
public:
    int tileCount = 0; // Number of tiles in the file.
    EnviromentalActor generateTile();
    /**
     * Import zones and return a pointer to a zone array given the level name.
     * @param levelName Name of the level holding the zones.
     * @return The zone array holding the zones.
     */
    static std::vector<Zone> importZones(std::string levelName);
    /**
     * Initiate a new zone object.
     * @param tileCount Count of tile types in the given zone.
     */
    Zone();
    void operator=(const Zone& z);
};


#endif //TREFUSISENGINE_ZONE_H
