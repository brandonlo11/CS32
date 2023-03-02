//
//  MemberDatabase.hpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h
#include "PersonProfile.h"
#include <set>
#include "RadixTree.h"

class MemberDatabase {
    vector<PersonProfile *> m_profiles;
    RadixTree<set<string>> m_av_to_emails;
    RadixTree<PersonProfile *> m_email_to_profile;
    void AddAVEmail(string source, string email);
    void AddEmailProfile(string email, PersonProfile *profile);
public:
    MemberDatabase() {}
    ~MemberDatabase() {
        for (auto i = m_profiles.begin(); i != m_profiles.end(); i++) {
            delete *i;
        }
    }
    bool LoadDatabase(string filename);
    vector<string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(string email) const;
};

#endif /* MemberDatabase_h */

