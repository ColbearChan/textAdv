//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"

class State {
    Room *currentRoom;
    std::list <GameObject*> inventory;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;
    std::list <GameObject*> getInventory() const;
    void addObject(GameObject* object);
    void removeObject(GameObject* object);
    GameObject* getObject(string* _keyword) const;
    void clearInventory();

};


#endif //TEXTADV_STATE_H
