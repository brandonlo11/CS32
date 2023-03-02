//
//  AttributeTranslator.hpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h
#include <string>
#include <set>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
using namespace std;

class AttributeTranslator {
    RadixTree<set<string>> m_translator;
//    RadixTree<string> m_translator;
    void AddTranslation(string sourcePair, string compatiblePair);
public:
    AttributeTranslator() {}
    ~AttributeTranslator() {}
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(
                                                 const AttValPair& source) const;
};

#endif /* AttributeTranslator_h */
