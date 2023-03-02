//
//  NewMap.cpp
//  Project 2
//
//  Created by Brandon Lo on 1/18/22.
//

#include "newMap.h"

Map::Map(): Map(DEFAULT_MAX_ITEMS){

};

Map::Map(int size): counter(0), capacity(size){
    m_pair = new Pair[size];
    if (size < 0){
        exit(-1);
    }
};

bool Map::empty() const{
    return (counter == 0);
};

int Map::size() const{
    return counter;
};

bool Map::insert(const KeyType &key, const ValueType &value){
    for (int i=0; i< counter; i++){
        if (key == m_pair[i].key){
            return false;
        }
    }
    if (counter < DEFAULT_MAX_ITEMS){
        m_pair[counter].key = key;
        m_pair[counter].value = value;
        counter++;
        return true;
    }
    return false;
};

bool Map::update(const KeyType &key, const ValueType &value){
    for (int i=0; i< counter; i++){
        if (key == m_pair[i].key){
            m_pair[i].value = value;
            return true;
        }
    }
    return false;
};

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value){
    for (int i=0; i< counter; i++){
        if (key == m_pair[i].key){
            m_pair[i].value = value;
            return true;
        }
    }
    if (counter < DEFAULT_MAX_ITEMS){
        m_pair[counter].key = key;
        m_pair[counter].value = value;
        counter++;
        return true;
    }
    return false;
};

bool Map::erase(const KeyType &key){
    for (int i=0; i< counter; i++){
        if (key == m_pair[i].key){
            for (int j=i; j<counter-1; j++){
                m_pair[j] = m_pair[j+1];
            }
            counter--;
            return true;
        }
    }
    return false;
};

bool Map::contains(const KeyType& key) const{
    for (int i=0; i< counter; i++){
        if (key == m_pair[i].key){
            return true;
            }
        }
    return false;
};

bool Map::get(const KeyType &key, ValueType &value) const{
    for (int i=0; i< counter; i++){
        if (key == m_pair[i].key){
            value = m_pair[i].value;
            return true;
        }
    }
    return false;
};

bool Map::get(int i, KeyType &key, ValueType &value) const{
    KeyType k = m_pair[0].key;
    if (0 <= i && i < size()){
        for (int j =0; j<size(); j++){
            if (m_pair[j].key < k){
                k = m_pair[j].key;
            }
        }

        for (int x =0; x < i; x++){
            KeyType h = k;
            for (int j =0; j<size(); j++){
                if (m_pair[j].key > k){
                    h = m_pair[j].key;
                    break;
                }
            }
            for (int j =0; j<size(); j++){
                if (m_pair[j].key < h && m_pair[j].key>k){
                    h = m_pair[j].key;
                }
            }
            k=h;
        }
        for (int i=0; i< counter; i++){
            if (k == m_pair[i].key){
                key = m_pair[i].key;
                value = m_pair[i].value;
                return true;
            }
        }
    }
    return false;
};

void Map::swap(Map &other){
    Pair* temp;
    temp = other.m_pair;
    other.m_pair = m_pair;
    m_pair = temp;
    int temp2;
    temp2 = other.counter;
    other.counter = counter;
    counter = temp2;
    temp2 = other.capacity;
    other.capacity = capacity;
    capacity = temp2;
};

Map::Map(const Map& other){
    counter = other.size();
    capacity = other.capacity;
    m_pair = new Pair[other.capacity];
    for (int i = 0; i< counter; i++){
        m_pair[i] = other.m_pair[i];
    }
};

Map& Map::operator = (const Map& other){
    if (this != &other){
        delete[] m_pair;
        counter = other.size();
        m_pair = new Pair[other.capacity];
        for (int i = 0; i< counter; i++){
            m_pair[i] = other.m_pair[i];
        }
    }
    return *this;
};

Map::~Map(){
    delete[] m_pair;
};
