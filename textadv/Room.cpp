//
// Created by DrMark on 10/2/2017.
// Modified by Hiu Ngai Chan 10/26/2018.
//

#include "Room.h"
#include "wordwrap.h"
#include "string.h"
#include "strings.h"
#include <iostream>

/**
 * Stores a static list of all rooms.
 */
std::map<std::string, Room*> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), east(nullptr), west(nullptr), objectList() {};


/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.erase(*this->getName());
}

/**
 * Prints the description of a room (the name, long description and the items)
 */
void Room::describe(){
    const std::string itemStart = "Items inside this room: ";
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    wrapOut(&itemStart);
    for(GameObject* i: this->objectList){
        wrapOut(i->getName());
        wrapOut(&formatKeyword);
        wrapOut(i->getKeyword());
        wrapOut(&formatSpace);
    }
    wrapEndPara();
}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms[*newRoom->getName()] = newRoom;
    return newRoom;
}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
Room* Room::addRoom(Room* room) {
    Room::rooms[*room->getName()] = room;
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}

Room* Room::getSouth() const {
    return this->south;
}

Room* Room::getEast() const {
    return this->east;
}

Room* Room::getWest() const {
    return this->west;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}

void Room::setSouth(Room *_south) {
    this->south = _south;
}

void Room::setEast(Room *_east) {
    this->east = _east;
}

void Room::setWest(Room *_west) {
    this->west = _west;
}

void Room::addObject(GameObject* _theObject) {
    this->objectList.push_back(_theObject);
}

void Room::removeObject(const string* _keyword) {
    bool removed = false;
    for(GameObject* i: this->objectList){
        if(i->getKeyword()->compare(*_keyword) == 0){
            //wrapOut(i->getKeyword());
            this->objectList.remove(i);
            removed = true;
            break;
        }
    }
    if(removed){
        wrapOut(&goodRemove);
        wrapEndPara();
    } else {
        wrapOut(&badRemove);
        wrapEndPara();
    }
}

GameObject* Room::getObject(string *_keyword) const{
    GameObject* object = nullptr;
    for(GameObject* i: this->objectList){
        if(i->getKeyword()->compare(*_keyword) == 0){
            object = i;
        }
    }
    return object;
}

const string* Room::getName(){
    return this->name;
}

std::list<GameObject*> Room::getObjects() {
    return this->objectList;
}

void Room::clearObjects() {
    this->objectList.clear();
}