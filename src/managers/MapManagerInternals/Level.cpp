//
// Created by elsa on 14.04.2020.
//

#include <langinfo.h>
#include "Level.h"
#include "../../trefusisInternals/TrefusisConfig.h"
#include "../../trefusisInternals/RandomNumberGenerator.h"

#ifdef DEBUG
#include <iostream>
#endif
Level Level::activeLevel {};

inline envActor copyEnvActor(envActor* ptr) {
    envActor newEnvActor {ptr->id, ptr->width, ptr->height};
    return newEnvActor;
}

inline envActor generateEnvActor(std::vector<envActor> refVector, std::vector<double> chanceVector) {
    double randomNumber = RandomNumberGenerator::random();
    for (int i = 0; i < refVector.size(); i++) {
        if (randomNumber < chanceVector[i]) {
            return refVector[i];
        }
    }
    return envActor{0,0,0};
}

inline envActor generateFoilage(zoneProbability* zp) {
    return generateEnvActor(zp->foilages, zp->foilageChances);
}

inline envActor generateTiles(zoneProbability* zp) {
    return generateEnvActor(zp->tiles, zp->tileChances);
}

Level::Level() {
#ifdef DEBUG
    std::cout << "Generating level in mode 1...\n";
#endif
    this->tileMatrix.resize(500);
    this->foilageMatrix.resize(500);
}

Level::Level(Level* lp) {
#ifdef DEBUG
    std::cout << "Generating level in mode 2...\n";
#endif
    this->tileMatrix.resize(500);
    this->foilageMatrix.resize(500);
    for (int i = 0; i < 500; i++) {
        this->tileMatrix[i].resize(500);
        this->foilageMatrix.resize(500);
        for (int j = 0; j < 500; j++) {
            this->tileMatrix[i][j] = copyEnvActor(&lp->tileMatrix[i][j]);
            this->foilageMatrix[i][j] = copyEnvActor(&lp->foilageMatrix[i][j]);
        }
    }
}

void Level::importLevelZoneMatrix(levelProbability *lpp) {
    FILE* fptr;
    fptr = fopen((TrefusisConfig::prefix + TrefusisConfig::mapsDirectory + lpp->levelName).c_str(), "r");
    lpp->zoneMatrix.resize(500);
    int i = 0;
    int j = 0;
    std::string token;
    int char_;
    do {
        char_ = fgetc(fptr);
        switch (char_) {
            case '\n':
                lpp->zoneMatrix[i][j] = std::atoi(token.c_str());  // Assign last zone of a row.
                i++;
            case ' ':
                break;
            case ',':
                lpp->zoneMatrix[i][j] = std::atoi(token.c_str()); // Assign zone.
                j++;
                break;
            case EOF:
                break;
            default:
                token += char_;
        }
    } while (char_ != EOF);
}

void Level::importLevelProbabilities(levelProbabilities* lp, const char* fileName) {
    FILE* fptr;
    fptr = fopen(fileName, "r");
    std::string token;
    ReadingMode mode;
    zoneProbability currentProbability;
    envActor* currentEnv;
    int commaDepth = 0;
    int char_;
    do {
        char_ = fgetc(fptr);
        switch(char_) {
            case '+':
                mode = LEVEL;
                break;
            case '-':
                mode = ZONE;
                break;
            case '*':
                mode = TILE;
                break;
            case '/':
                mode = FOILAGE;
                break;
            case '\n':
                switch (mode) {
                    case LEVEL:
                        lp->levelCount += 1;
                        lp->levelNames.push_back(token);
                        lp->probabilities.push_back(levelProbability{});
                        lp->probabilities.back().levelName = token.c_str();
                        importLevelZoneMatrix(&lp->probabilities.back());
                        break;
                    case ZONE:
                        lp->probabilities.back().zoneCount += 1;
                        lp->probabilities.back().zoneProbabilities.push_back(zoneProbability{});
                        break;
                    case TILE: // Token in this case is the tile spawn chance.
                        currentProbability = lp->probabilities.back().zoneProbabilities.back();
                        currentProbability.tileChances.push_back(std::atof(token.c_str())); // We push that chance to the back.
                        currentProbability.tileCount++;
                        currentEnv->width = 1;
                        currentEnv->height = 1;
                        currentProbability.tiles.push_back(copyEnvActor(currentEnv));
                        break;
                    case FOILAGE:
                        // Likewise, the last token must be foilage spawn chance.
                        currentProbability = lp->probabilities.back().zoneProbabilities.back();
                        currentProbability.foilageChances.push_back(std::atof(token.c_str()));
                        currentProbability.foilageCount++;
                        currentProbability.foilages.push_back(copyEnvActor(currentEnv));
                        break;
                    default:
                        std::cout << "ERROR: Blank line atop the levels file, or blank levels file.\n";
                        break;
                }
                token = ""; // Done!
                commaDepth = 0;
            case ',':
                switch (mode) {
                    case TILE:
                        if (commaDepth > 0) {
                            std::cout << "ERROR: Too many arguments (or commas) for tile definition.";
                            exit(1);
                        } else {
                            currentEnv->id = std::atoi(token.c_str());
                        }
                        break;
                    case FOILAGE:
                        switch (commaDepth) {
                            case 0:
                                currentEnv->id = std::atoi(token.c_str());
                                break;
                            case 1:
                                currentEnv->width = std::atoi(token.c_str());
                                break;
                            case 2:
                                currentEnv->height = std::atoi(token.c_str());
                                break;
                            default:
                                std::cout << "ERROR: Too many arguments (or commas) for foilage definition.";
                                exit(1);
                        }
                        break;
                    default:
                        std::cout << "ERROR: Comma cannot be used outside tile and foilage definitons.";
                        exit(1);
                }
                commaDepth++;
                token = "";
            default:
                token += char_;
                break;
        }
    } while(char_ != EOF);
    free(currentEnv);
}

void Level::generateEnviromentalActors(levelProbabilities *probabilities) {
    Level* newLevel {};
    levelProbability currentLevel;
    int currentZoneIndex; // Zone Index for this tile.
    zoneProbability currentZoneProbability; // Current zone probability for this tile.
    for (int x = 0; x < probabilities->levelCount; x++) {
        currentLevel = probabilities->probabilities[x];
        for (int i = 0; i < 500; i++) {
            for (int j = 0; j < 500; j++) {
                currentZoneIndex = currentLevel.zoneMatrix[i][j];
                currentZoneProbability = currentLevel.zoneProbabilities[currentZoneIndex];
                newLevel->foilageMatrix[i][j] = generateFoilage(&currentZoneProbability);
                newLevel->tileMatrix[i][j] = generateTile(&currentZoneProbability);
            }
        }
        levels.push_back(new Level(newLevel));
    }
    free(newLevel);
}

void Level::smoothTiles() {
    std::vector<envActor> surrounding;
    for (Level level : levels) {
        for (int i = 0; i < 500; i++) {
            for (int j = 0; j < 500; j++) {
                surrounding.push_back(level.tileMatrix[i - 1][j]);
                surrounding.push_back(level.tileMatrix[i][j - 1]);
                surrounding.push_back(level.tileMatrix[i + 1][j]);
                surrounding.push_back(level.tileMatrix[i][j + 1]);
                level.tileMatrix[i][j] = surrounding[RandomNumberGenerator::randint(0, 4)];
                surrounding.clear();
            }
        }
    }
}
levelProbabilities Level::importLevels() {
    levelProbabilities lp;
    importLevelProbabilities(&lp, TrefusisConfig::levelsLocation.c_str());
    generateEnviromentalActors(&lp);
    smoothTiles();
    activeLevel = levels[0];
}

void Level::changeLevel(int levelIndex) {
    activeLevel = levels[levelIndex];
}

