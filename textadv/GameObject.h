//
// Created by Hiu Ngai Chan on 10/26/2018.
//

#include <string>
#include <list>
#include <map>

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#endif //TEXTADV_GAMEOBJECT_H

using std::string;

class GameObject{
    const string* name;
    const string* description;
    const string* keyword;
public:
    GameObject(const string *_name, const string *_desc, const string *_keyword);
    ~GameObject();
    static std::map<const std::string,GameObject*> staticObjectMap;
    static void addGameObject(GameObject* _object);
    const string* getName() const;
    const string* getDescription() const;
    const string* getKeyword() const;
};
