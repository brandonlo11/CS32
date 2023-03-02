//
//  PersonProfile.cpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#include "PersonProfile.h"

PersonProfile::PersonProfile(std::string name, std::string email): m_name(name), m_email(email){
}

std::string PersonProfile::GetName() const{
    return m_name;
}

std::string PersonProfile::GetEmail() const{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval){
    std::string temp;
    for (int i = 0;true;i++){
        temp = attval.attribute + "_" + std::to_string(i);
        string *value = m_radix.search(temp);
        if (value == nullptr){
            break;
        }
        if (*value == attval.value){
            return;
        }
    }
    m_attributes.push_back(temp);
    m_radix.insert(temp, attval.value);
}

int PersonProfile::GetNumAttValPairs() const{
    return (int) m_attributes.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if (m_radix.search(m_attributes[attribute_num]) == nullptr){
        return false;
    }
    AttValPair av;
    av.attribute = m_attributes[attribute_num].substr(0, m_attributes[attribute_num].find("_"));
    av.value = *(m_radix.search(m_attributes[attribute_num]));
    attval = av;
    return true;
}

