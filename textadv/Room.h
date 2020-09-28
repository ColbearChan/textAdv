//
// Created by DrMark on 10/2/2017.
// Modified by Hiu Ngai Chan 10/26/2018.
//

#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"

using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    /**
     * Pointers to room that is north, south, east and west.
     */
    Room* north;
    Room* south;
    Room* east;
    Room* west;
    std::list<GameObject*> objectList;
public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe();

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::map<std::string ,Room*> rooms;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static Room* addRoom(Room* room);


    Room* getNorth() const;
    void setNorth(Room* _north);
    Room* getSouth() const;
    void setSouth(Room* _south);
    Room* getEast() const;
    void setEast(Room* _east);
    Room* getWest() const;
    void setWest(Room* _west);

    GameObject* getObject(string* _keyword) const;
    void addObject(GameObject* _object);
    void removeObject(const string* _keyword);
    const string* getName();
    std::list<GameObject*> getObjects();
    void clearObjects();
};

#endif //TEXTADV_ROOM_H
