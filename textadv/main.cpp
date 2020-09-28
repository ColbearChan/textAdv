
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include <fstream>
#include "windows.h"
#include "dirent.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;
/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << ">  ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {

    auto * r1 = new Room(&r1name, &r1desc);
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r5 = new Room(&r5name, &r5desc);
    auto * r6 = new Room(&r6name, &r6desc);

    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);
    Room::addRoom(r6);

    r1->setNorth(r2);
    r1->setWest(r6);
    r1->setEast(r4);
    r2->setEast(r3);
    r2->setSouth(r1);
    r3->setSouth(r4);
    r3->setWest(r2);
    r4->setSouth(r5);
    r4->setWest(r1);
    r4->setNorth(r3);
    r5->setNorth(r4);
    r6->setEast(r1);
}

void initGameObjects(){
    auto * o1 = new GameObject(&o1name, &o1desc, &o1keyw);
    auto * o2 = new GameObject(&o2name, &o2desc, &o2keyw);
    auto * o3 = new GameObject(&o3name, &o3desc, &o3keyw);
    GameObject::addGameObject(o1);
    GameObject::addGameObject(o2);
    GameObject::addGameObject(o3);
    Room::rooms[r1name]->addObject(o1);
    Room::rooms[r1name]->addObject(o2);
    Room::rooms[r1name]->addObject(o3);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms[r1name]);
}

void savingIn(string fileName){
    std::ofstream savingFile (fileName.append(".txt"));
    //LockFileEx(savingFile,LOCKFILE_EXCLUSIVE_LOCK,0,NULL,NULL, NULL);
    savingFile << "player_current_room:" << *currentState->getCurrentRoom()->getName() << "\n";
    savingFile << "player inventory:";
    for(GameObject* o: currentState->getInventory()){
        savingFile << *o->getName() << ",";
    }
    savingFile << "\n";
    for(auto i: Room::rooms){
        savingFile << *i.second->getName() << ":";
        for(GameObject* o: i.second->getObjects()){
            savingFile << *o->getName() << ",";
        }
        savingFile << "\n";
    }
    savingFile.close();
    wrapOut(&goodSave);
    wrapEndPara();
}

string loadingList(){
    DWORD curDirSize = MAX_PATH;
    char curDir[MAX_PATH];
    GetCurrentDirectory(curDirSize, curDir);
    DIR *dir;
    struct dirent *entry;
    if((dir = opendir(curDir)) != NULL){
        while((entry = readdir(dir)) != NULL){
            if(static_cast<std::string>(entry->d_name).find("txt") != string::npos
               && static_cast<std::string>(entry->d_name).find("CMakeCache") == string::npos){
                std::cout << entry->d_name << std::endl;
            }
        }
        closedir(dir);
    } else {
        wrapOut(&badLoadDir);
        wrapEndPara();
    }

}

void loadingIn(string fileName){
    std::ifstream savedFile;
    savedFile.open(fileName.append(".txt"));
    if (savedFile.good()){
        std::string line;
        std::string roomName;
        std::string objectName;
        std::string currentRoomName;
        getline(savedFile, line);
        auto posOfColon = static_cast<uint8_t>(line.find(':'));
        //std::cout << "current room is " << line.substr(posOfColon) << std::endl;
        /*if(posOfColon == string::npos){
            wrapOut(&badLoadWrongContent);
            wrapEndPara();
        }*/
        currentRoomName = line.substr(posOfColon+1); //get the saved current room name
        getline(savedFile, line);
        posOfColon = static_cast<uint8_t>(line.find(':'));
        auto posOfObject = posOfColon+1;
        auto posOfComma = static_cast<uint8_t>(line.find(','));
        currentState->clearInventory();
        //loading in the items into the inventory
        while(posOfComma != static_cast<uint8_t>(string::npos)){
            objectName = line.substr(posOfObject, (posOfComma - posOfObject));
            currentState->addObject(GameObject::staticObjectMap[objectName]);
            posOfObject = posOfComma+1;
            posOfComma = static_cast<uint8_t>(line.find(',', posOfObject));
        }


        for(int i = 0; i < Room::rooms.size(); i++){
            getline(savedFile, line);
            posOfColon = static_cast<uint8_t>(line.find(':'));
            roomName = line.substr(0,posOfColon);
            //std::cout << roomName << std::endl;
            Room::rooms[roomName]->clearObjects(); //clear the object list
            posOfObject = posOfColon+1;
            posOfComma = static_cast<uint8_t>(line.find(','));

            while(posOfComma != static_cast<uint8_t>(string::npos)){
                objectName = line.substr(posOfObject, (posOfComma - posOfObject));
                Room::rooms[roomName]->addObject(GameObject::staticObjectMap[objectName]);
                //std::cout << objectName << std::endl;
                posOfObject = posOfComma+1;
                posOfComma = static_cast<uint8_t>(line.find(',', posOfObject));
            }
        }
        wrapOut(&goodLoad);
        wrapEndPara();
        currentState->goTo(Room::rooms[currentRoomName]);
    } else {
        wrapOut(&badLoadNoFile);
        wrapEndPara();
    }
    savedFile.close();
}

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));
        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a north exit */
            Room *northRoom = currentState->getCurrentRoom()->getNorth();
            if (northRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(northRoom); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a south exit */
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(southRoom); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a east exit */
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(eastRoom); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a west exit */
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(westRoom); /* Update state to that room - this will also describe it */
            }
        }


        if(commandBuffer.compare(0, endOfVerb, "get") == 0) {
            commandOk = true;
            if(endOfVerb == static_cast<uint8_t>(string::npos)){
                wrapOut(&badCommand);
                wrapEndPara();
            } else {
                if(commandBuffer.size() > 4){
                    string theSecVerb = commandBuffer.substr(endOfVerb+1);
                    if (currentState->getCurrentRoom()->getObject(&theSecVerb) != nullptr) {
                        currentState->addObject(currentState->getCurrentRoom()->getObject(&theSecVerb));
                        currentState->getCurrentRoom()->removeObject(&theSecVerb);
                    } else {
                        wrapOut(&objectNotFound);
                        wrapEndPara();
                    }
                } else {
                    wrapOut(&badCommand);
                    wrapEndPara();
                }
            }
        }

        if(commandBuffer.compare(0, endOfVerb, "drop") == 0) {
            commandOk = true;
            if(endOfVerb == static_cast<uint8_t>(string::npos)){
                wrapOut(&badCommand);
                wrapEndPara();
            } else {
                if(commandBuffer.size() > 5){
                    string theSecVerb = commandBuffer.substr(endOfVerb+1);
                    if (currentState->getObject(&theSecVerb) != nullptr) {
                        currentState->getCurrentRoom()->addObject(currentState->getObject(&theSecVerb));
                        wrapOut(&goodDrop);
                        wrapEndPara();
                        currentState->removeObject(currentState->getObject(&theSecVerb));
                    } else {
                        wrapOut(&objectNotFound);
                        wrapEndPara();
                    }
                } else {
                    wrapOut(&badCommand);
                    wrapEndPara();
                }
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"inventory") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a west exit */
            wrapOut(&showInventory);
            for(GameObject* i: currentState->getInventory()){
                wrapOut(i->getName());
                wrapOut(&formatKeyword);
                wrapOut(i->getKeyword());
                wrapOut(&formatSpace);
            }
            wrapEndPara();
        }

        if ((commandBuffer.compare(0, endOfVerb, "examine") == 0)) {
            commandOk = true;
            if(endOfVerb == static_cast<uint8_t>(string::npos)){
                wrapOut(&badCommand);
                wrapEndPara();
            } else {
                if(commandBuffer.size() > 8){
                    string theSecVerb = commandBuffer.substr(endOfVerb+1);
                    if (currentState->getCurrentRoom()->getObject(&theSecVerb) != nullptr) {
                        wrapOut(currentState->getCurrentRoom()->getObject(&theSecVerb)->getName());
                        wrapOut(&formatSpace);
                        wrapOut(currentState->getCurrentRoom()->getObject(&theSecVerb)->getDescription());
                        wrapEndPara();
                    } else if(currentState->getObject(&theSecVerb) != nullptr) {
                        wrapOut(currentState->getObject(&theSecVerb)->getName());
                        wrapOut(&formatSpace);
                        wrapOut(currentState->getObject(&theSecVerb)->getDescription());
                        wrapEndPara();
                    } else {
                        wrapOut(&objectNotFound);
                        wrapEndPara();
                    }
                } else {
                    wrapOut(&badCommand);
                    wrapEndPara();
                }
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"save") == 0)) {
            commandOk = true;
            if (endOfVerb == static_cast<uint8_t>(string::npos)) {
                wrapOut(&badSaveIntro);
                wrapEndPara();
            } else {
                if (commandBuffer.size() > 5) {
                    string theSecVerb = commandBuffer.substr(endOfVerb + 1);
                    std::ifstream check(theSecVerb + ".txt");
                    if (check.good()) {
                        wrapOut(&badSaveCluster);
                        wrapEndPara();
                    } else {
                        savingIn(theSecVerb);
                    }
                } else {
                    wrapOut(&badCommand);
                    wrapEndPara();
                }
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"load") == 0)) {
            commandOk = true;
            if (endOfVerb == static_cast<uint8_t>(string::npos)) {
                wrapOut(&badLoadIntro);
                wrapEndPara();
            } else {
                if (commandBuffer.size() > 5) {
                    string theSecVerb = commandBuffer.substr(endOfVerb + 1);
                    loadingIn(theSecVerb);
                } else {
                    wrapOut(&badCommand);
                    wrapEndPara();
                }
            }
        }

        if ((commandBuffer.compare(0,endOfVerb, "loadlist") == 0)){
            commandOk = true;
            loadingList();
        }

        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initGameObjects();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}