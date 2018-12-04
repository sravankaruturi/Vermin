//
// Created by ant on 12/3/18.
//

#ifndef GAME_GAMEDEFINITIONS_H
#define GAME_GAMEDEFINITIONS_H

struct Resources{

    int rWood = 100;
    int rStone = 100;

    Resources() = default;

    Resources(int _wood, int _stone){
        rWood = _wood;
        rStone = _stone;
    }

};

#endif //GAME_GAMEDEFINITIONS_H
