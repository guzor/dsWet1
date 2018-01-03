//
// Created by or.guz on 03-Jan-18.
//

#ifndef DSWET2_GLADIATOR_H
#define DSWET2_GLADIATOR_H


/**---------------------------GLADIATOR----------------------------------
     * Gladiator class.
     * Each Gladiator will have a level and a unique id.
     * In addition, gladiator will save a pointer to its trainer */
class Gladiator {

    int id;
    int score;

public:
    /**EMPTY CONSTRUCTOR
     * initialize a Gladiator with invalid keys and a null trainet
     */
    //TODO Gladiator();

    /**CONSTRUCTOR
     * initialize a gladiator with the following details:
     * @param id
     * @param level
     * @param trainer - the trainer that owns the gladiator*/
    Gladiator(int id, int level);

    //Copy Constructor default
    //ddelte deefault

    /**GET ID
     * @return gladiator's id  */
    int getId() const;

    /**SET ID
     * set gladiator's id to new_id
     * @param new_id */
    void setId(int new_id);

    /**GET LEVEL
     **GET ID
     * @return gladiator's level  */
    int getScore() const;

    /**SET ID
     * set gladiator's level to new_level
     * @param new_level */
    void setScore(int new_score);


};/*END OF GLADIATOR*/


#endif //DSWET2_GLADIATOR_H
