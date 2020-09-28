//
// Created by Hiu Ngai Chan on 10/26/2018.
//

#include "GameObject.h"

std::map<const std::string, GameObject*> GameObject::staticObjectMap;

GameObject::GameObject(const string *_name, const string *_desc, const string *_keyword) :
        name(_name),description(_desc), keyword(_keyword){}

GameObject::~GameObject() {
    staticObjectMap.erase(*this->getName());
}


void GameObject::addGameObject(GameObject* _object){
    GameObject::staticObjectMap[*_object->getName()] = _object;
}

const std::string* GameObject::getName() const{
    return this->name;
}

const std::string* GameObject::getDescription() const{
    return this->description;
}

const std::string* GameObject::getKeyword() const{
    return this->keyword;
}