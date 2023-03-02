//
//  MatchMaker.hpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#ifndef MatchMaker_hpp
#define MatchMaker_hpp

#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
using namespace std;

class MatchMaker{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;
    vector<AttValPair> getCompatibleAV(string email) const;
private:
    const MemberDatabase &m_data;
    const AttributeTranslator &m_translator;
};

#endif /* MatchMaker_hpp */
