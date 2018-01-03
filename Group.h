
#ifndef DSWET2_GROUP_H
#define DSWET2_GROUP_H

#include "splayTree.h"
#include "Gladiator.h"

using namespace trees;

class Group {
    int id;
    Splay<Gladiator, int> gladiators;
public:
    Group();
    explicit Group(int id);
    int getID() const;



    class InvalidInput : public std::exception{
    };
};


#endif //DSWET2_GROUP_H
