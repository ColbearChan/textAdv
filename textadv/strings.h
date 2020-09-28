//
// Created by DrMark on 10/4/2017.
// Modified by Hiu Ngai Chan 10/26/2018.
//

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

const std::string r1name = "Room 1";
const std::string r1desc = "You are in room 1. It's really quite boring, but then, it's just for testing really. There's a passage to the north.";
const std::string r2name = "Blue Room";
const std::string r2desc = "You are in the blue room. You know because it's blue. That's about all though. There's a passage to the south.";

const std::string r3name = "Mike's Room";
const std::string r3desc = "The room is small and dusty but surprisingly tidy with each item in a specific place hiding the secret passage way to... narrator dies";
const std::string r4name = "Will's Room";
const std::string r4desc = ".... still dead";
const std::string r5name = "Colbert's Room";
const std::string r5desc = "Second Narrator: This room is alright, it just alright, perfectly defines what alright means";
const std::string r6name = "Charlie's Room";
const std::string r6desc = "Charlies room is big, for a big big boy. ";
const std::string r7name = "Shikhar's Room";
const std::string r7desc = "Shikhars room is filled with all the robots as it should be for a robotics student";

const std::string o1name = "object one";
const std::string o1desc = "This is the first created object";
const std::string o1keyw = "obj1";
const std::string o2name = "object two";
const std::string o2desc = "This is the second created object";
const std::string o2keyw = "obj2";
const std::string o3name = "object three";
const std::string o3desc = "This is the third created object";
const std::string o3keyw = "obj3";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";
const std::string goodRemove = "The item is removed";
const std::string badRemove = "Cannot find the item";
const std::string objectNotFound = "This item is not found";
const std::string goodGet = "You have put it into your inventory";
const std::string goodDrop = "You have drop it in this room";
const std::string goodSave = "The game is saved successfully!";
const std::string badSaveIntro = "Please enter a name for the saving file after the key word save";
const std::string badSaveCluster = "This file name exist already, please try another name next time.";
const std::string goodLoad = "The game is loaded, now you are in:";
const std::string badLoadNoFile = "Cannot find the saving file";
const std::string badLoadWrongContent = "The saving file is not correct";
const std::string badLoadDir = "Cannot find the saving directory";
const std::string badLoadIntro = "Please enter the name for the saving file(without extension)after the "
        "key word load";
const std::string showInventory = "Inventory: ";
const std::string formatKeyword = " -> ";
const std::string formatSpace = ", ";


#endif //TEXTADV_STRINGS_H
