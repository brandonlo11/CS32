//
//  Utility.cpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#include "utility.h"
#include <fstream>

bool getLines(string fileName, vector<string> &lines) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
        return true;
    }
    return false;
}

bool getCommaSeparatedParts(string line, vector<string> &parts) {
    bool ret = false;
    size_t pos = 0;
    while ((pos = line.find(DELIMITER)) != string::npos) {
        ret = true; // if we find a comma, we separate
        parts.push_back(line.substr(0, pos));
        line.erase(0, pos + DELIMITER.length());
    }
    if (ret) {
        parts.push_back(line.substr(0)); // only add last value if we have comma's
    }
    return ret;
}

bool StringToAttributeValue(const string &str, AttValPair &av) {
    vector<string> parts;
    if (getCommaSeparatedParts(str, parts)) {
        av.attribute = parts[0];
        av.value = parts[1];
        return true;
    }
    return false;
}

bool comparator(const EmailCount& lhs, const EmailCount& rhs) {
    if (lhs.count == rhs.count) {
        return (lhs.email < rhs.email);
    }
    return lhs.count > rhs.count;
}

string AttributeValueToString(const AttValPair &av) {
    return av.attribute + DELIMITER + av.value;
}
