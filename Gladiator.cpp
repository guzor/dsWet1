//
// Created by or.guz on 03-Jan-18.
//

#include "Gladiator.h"

//TODO Gladiator::Gladiator() : id(INVALID_KEY), score(INVALID_KEY){}

Gladiator::Gladiator(int id, int score) :
        id(id), score(score) {}


int Gladiator::getId() const {
    return id;
}

void Gladiator::setId(int new_id) {
    id = new_id;
}

int Gladiator::getScore() const {
    return score;
}

void Gladiator::setScore(int new_score) {
    score = new_score;
}


