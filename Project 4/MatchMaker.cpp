//
//  MatchMaker.cpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//
//
#include "MatchMaker.h"
#include "utility.h"
#include <algorithm>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at):m_data(mdb), m_translator(at){
}

vector<AttValPair> MatchMaker::getCompatibleAV(string email) const {
    vector<AttValPair> attValVector;
    const PersonProfile *p = m_data.GetMemberByEmail(email);
    if(p != nullptr){
        set<string> total;
        for (auto i = 0; i < (*p).GetNumAttValPairs(); i++){
            AttValPair av;
            if ((*p).GetAttVal(i, av)){
                vector<AttValPair> l = m_translator.FindCompatibleAttValPairs(av);
                for (auto j = l.begin(); j != l.end(); j++){
                    string k = AttributeValueToString(*j);
                    total.insert(k);
                }
            }
        }
        for (auto i = total.begin(); i != total.end(); i++) {
            AttValPair av;
            if (StringToAttributeValue(*i, av)) {
                attValVector.push_back(av);
            }
        }
    }
    return attValVector;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const{
    RadixTree<EmailCount*> emailRadix;
    vector <EmailCount*> emailVector;
    vector<AttValPair> attValVector = getCompatibleAV(email);
    for (auto i = attValVector.begin(); i != attValVector.end(); i++) {
        vector<string> compatibleEmails = m_data.FindMatchingMembers(*i);
        for (auto j = compatibleEmails.begin(); j != compatibleEmails.end(); j++) {
            EmailCount *emailCount = (emailRadix.search(*j) == nullptr) ? nullptr : *emailRadix.search(*j);
            if (emailCount == nullptr) {
                emailCount = new EmailCount(*j, 1);
                emailRadix.insert(*j, emailCount);
                emailVector.push_back(emailCount);
            }
            else {
                emailCount->count += 1;
            }
        }
    }
    vector<EmailCount> ret;
    for (auto i = emailVector.begin(); i != emailVector.end(); i++){
        if ((*i)->count >= threshold){
            ret.push_back(**i);
        }
        delete *i;
    }
    sort(ret.begin(), ret.end(), &comparator);
    return ret;
}
