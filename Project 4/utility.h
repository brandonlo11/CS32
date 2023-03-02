//
//  Utility.hpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#ifndef utility_h
#define utility_h
#include <string>
#include <vector>
#include "provided.h"
using namespace std;

static const string SEPARATOR = "_";

const string DELIMITER = ",";

bool getLines(string fileName, vector<string> &lines);

bool getCommaSeparatedParts(string line, vector<string> &parts);

bool StringToAttributeValue(const string &str, AttValPair &av);

bool comparator(const EmailCount& lhs, const EmailCount& rhs);

string AttributeValueToString(const AttValPair &av);

#endif /* utility_h */

