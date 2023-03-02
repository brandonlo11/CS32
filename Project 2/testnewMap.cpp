//
//  testnewMap.cpp
//  Project 2
//
//  Created by Brandon Lo on 1/18/22.
//

#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;


void checkMap(Map &x, Map y) {
    string keyX, keyY;
    double valueX, valueY;
    assert(x.size() == y.size());
    for (int i = 0; i < x.size(); i++) {
        assert(x.get(i, keyX, valueX));
        assert(y.get(i, keyY, valueY));
        assert(keyX == keyY && valueX == valueY);
    }
    cout << "Checking now" << endl;
}

int main()
{
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    m.insert("dad", 100);
    checkMap(m, m);

    Map n;
    assert(n.insert("abc", 10));
    assert(n.contains("abc"));
//    n = m;
//    assert(!n.contains("abc"));
//    assert(n.contains("xyz"));

    n.swap(m);
    assert (n.contains("dad"));
    assert (m.contains("abc"));
    string x = "dad";
    double y;
    assert(n.get(x, y));


    cout << "Passed all tests" << endl;
}

