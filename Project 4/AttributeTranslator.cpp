//
//  AttributeTranslator.cpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#include "AttributeTranslator.h"
#include "utility.h"

void AttributeTranslator::AddTranslation(string sourcePair, string compatiblePair) {
    set<string> *ptr = m_translator.search(sourcePair);
    if (ptr == nullptr) {
        m_translator.insert(sourcePair, set<string>());
        ptr = m_translator.search(sourcePair);
    }
    ptr->insert(compatiblePair);
}

bool AttributeTranslator::Load(string filename) {
    vector<string> lines;
    if (getLines(filename, lines)) {
        for (string line: lines) {
            vector<string> parts;
            if (getCommaSeparatedParts(line, parts)) {
                if (parts.size() == 4) {
                    AddTranslation(parts[0] + DELIMITER + parts[1], parts[2] + DELIMITER + parts[3]);
                }
            }
        }
        return true;
    }
    return false;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    vector<AttValPair> ret;
    string key = source.attribute + DELIMITER + source.value;
    set<string> *ptr = m_translator.search(key);
    if (ptr != nullptr) {
        for (auto i = ptr->begin(); i != ptr->end(); i++) {
            vector<string> parts;
            if (getCommaSeparatedParts(*i, parts)) {
                AttValPair av(parts[0], parts[1]);
                ret.push_back(av);
            }
        }
    }
    return ret;
}
