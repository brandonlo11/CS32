//
//  CarMapTest.cpp
//  Project 2
//
//  Created by Brandon Lo on 1/18/22.
//

#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    CarMap m;
    m.addCar("xyz");
    m.drive("xyz", 200);
    assert(m.addCar("dos"));
    assert(m.drive("dos", 200));
    assert(!m.addCar("xyz"));
    assert(m.miles("xyz") == 200);
    assert (m.fleetSize() == 2);
    m.print();
}
