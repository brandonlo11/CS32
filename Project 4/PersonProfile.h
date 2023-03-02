//
//  PersonProfile.hpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#ifndef PersonProfile_hpp
#define PersonProfile_hpp

#include <iostream>
#include "provided.h"
#include "RadixTree.h"
#include <vector>

class PersonProfile{
public:
    PersonProfile(std::string name, std::string email);
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    RadixTree<std::string> m_radix;
    std::vector<std::string> m_attributes;
};

#endif /* PersonProfile_hpp */
