//
// Created by DrMark on 10/2/2017.
//

#include "State.h"
#include "wordwrap.h"
#include "strings.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom), inventory() {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

std::list <GameObject*> State::getInventory() const{
    return this->inventory;

}

void State::addObject(GameObject *object) {
    this->inventory.push_back(object);
    wrapOut(&goodGet);
    wrapEndPara();
}

void State::removeObject(GameObject *object){
    this->inventory.remove(object);
    wrapOut(&goodRemove);
    wrapEndPara();
}

GameObject* State::getObject(string *_keyword) const {
    GameObject* dummy = nullptr;
    for(GameObject* i: this->inventory){
        if(i->getKeyword()->compare(*_keyword) == 0){
            dummy = i;
        }
    }
    return dummy;
}
void State::clearInventory() {
    this->inventory.clear();
}
