//
//  CarMap.cpp
//  Project 2
//
//  Created by Brandon Lo on 1/17/22.
//

#include "CarMap.h"
#include <iostream>
using namespace std;

CarMap::CarMap(){
    
};

bool CarMap::addCar(std::string license){
    return m_instance.insert(license, 0);
};

double CarMap::miles(std::string license) const{
    ValueType mile;
    if ( m_instance.get(license, mile)){
        return mile;
    }
    else{
        return -1;
    }
};

bool CarMap::drive(std::string license, double distance){
    ValueType add;
    if (!(m_instance.get(license, add)) || distance <0){
        return false;
    }
    else{
        distance += add;
        m_instance.update(license, distance);
        return true;
    }
};

int CarMap::fleetSize() const{
    return (m_instance.size());
};

void CarMap::print() const{
    KeyType key;
    ValueType value;
    for (int i = 0; i < m_instance.size(); i++){
        m_instance.get(i, key, value);
        cout << key << " " << value << endl;
    }
};
