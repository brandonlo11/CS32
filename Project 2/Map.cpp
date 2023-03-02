//
//  Map.cpp
//  Project 2
//
//  Created by Brandon Lo on 1/17/22.
//

#include "Map.h"

Map::Map(): counter(0){

};

bool Map::empty() const{
    return (counter == 0);
};

int Map::size() const{
    return counter;
};

bool Map::insert(const KeyType &key, const ValueType &value){
    for (int i=0; i< counter; i++){
        if (key == m_array[i].key){
            return false;
        }
    }
    if (counter < DEFAULT_MAX_ITEMS){
        m_array[counter].key = key;
        m_array[counter].value = value;
        counter++;
        return true;
    }
    return false;
};

bool Map::update(const KeyType &key, const ValueType &value){
    for (int i=0; i< counter; i++){
        if (key == m_array[i].key){
            m_array[i].value = value;
            return true;
        }
    }
    return false;
};

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value){
    for (int i=0; i< counter; i++){
        if (key == m_array[i].key){
            m_array[i].value = value;
            return true;
        }
    }
    if (counter < DEFAULT_MAX_ITEMS){
        m_array[counter].key = key;
        m_array[counter].value = value;
        counter++;
        return true;
    }
    return false;
};

bool Map::erase(const KeyType &key){
    for (int i=0; i< counter; i++){
        if (key == m_array[i].key){
            for (int j=i; j<counter-1; j++){
                m_array[j] = m_array[j+1];
            }
            counter--;
            return true;
        }
    }
    return false;
};

bool Map::contains(const KeyType& key) const{
    for (int i=0; i< counter; i++){
        if (key == m_array[i].key){
            return true;
            }
        }
    return false;
};

bool Map::get(const KeyType &key, ValueType &value) const{
    for (int i=0; i< counter; i++){
        if (key == m_array[i].key){
            value = m_array[i].value;
            return true;
        }
    }
    return false;
};

bool Map::get(int i, KeyType &key, ValueType &value) const{
    KeyType k = m_array[0].key;
    if (0 <= i && i < size()){
        for (int j =0; j<size(); j++){
            if (m_array[j].key < k){
                k = m_array[j].key;
            }
        }

        for (int x =0; x < i; x++){
            KeyType h = k;
            for (int j =0; j<size(); j++){
                if (m_array[j].key > k){
                    h = m_array[j].key;
                    break;
                }
            }
            for (int j =0; j<size(); j++){
                if (m_array[j].key < h && m_array[j].key>k){
                    h = m_array[j].key;
                }
            }
            k=h;
        }
        for (int i=0; i< counter; i++){
            if (k == m_array[i].key){
                key = m_array[i].key;
                value = m_array[i].value;
                return true;
            }
        }
    }
    return false;
};

void Map::swap(Map &other){
    int f = 0;
    if (size() < other.size()){
        f = size();
    }
    else{
        f = other.size();
    }
    for (int i = 0; i<f; i++){
        Pair temp = m_array[i];
        m_array[i] = other.m_array[i];
        other.m_array[i] = temp;
    }
    int k = 0;
    if (size() < other.size()){
        k = other.size() -size();
        for (int l = 0; l<k; l++){
            m_array[f+l] = other.m_array[f+l];
        }
    }
    else{
        k = size() - other.size();
        for (int l = 0; l<k; l++){
            other.m_array[f+l] = m_array[f+l];
        }
    }
    int temp = counter;
    counter = other.counter;
    other.counter = temp;
};

