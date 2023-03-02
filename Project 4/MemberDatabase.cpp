//
//  MemberDatabase.cpp
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#include "MemberDatabase.h"
#include "utility.h"

void MemberDatabase::AddAVEmail(string source, string email) {
    set<string> *ptr = m_av_to_emails.search(source);
    if (ptr == nullptr) {
        m_av_to_emails.insert(source, set<string>());
        ptr = m_av_to_emails.search(source);
    }
    ptr->insert(email);
}

void MemberDatabase::AddEmailProfile(string email, PersonProfile *profile) {
    m_profiles.push_back(profile);
    m_email_to_profile.insert(email, profile);
}

bool MemberDatabase::LoadDatabase(string filename) {
    vector<string> memberLines;
    if (getLines(filename, memberLines)) {
        for (int i = 0; i < memberLines.size(); ) {
            string name = memberLines[i];
            string email = memberLines[i + 1];
            int attNum = stoi(memberLines[i + 2]);
            PersonProfile * ptr = new PersonProfile(name, email);
            for (int j = 0; j < attNum; j++) {
                vector<string> pair;
                getCommaSeparatedParts(memberLines[i + 3 + j], pair);
                AttValPair av(pair[0], pair[1]);
                ptr->AddAttValPair(av);
                AddAVEmail(av.attribute + DELIMITER + av.value, email); // add av to email
            }
            AddEmailProfile(email, ptr); // add email to profile
            i += 4 + attNum; // advance i to next profile which is attNum + 4 (4 accounts for name, email, attNum specification and blank line.
        }
        return true;
    }
    return false;
}
vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    vector<string> ret;
    set<string> *ptr = m_av_to_emails.search(input.attribute + DELIMITER + input.value);
    if (ptr != nullptr) {
        for (auto i = ptr->begin(); i != ptr->end(); i++) {
            ret.push_back(*i);
        }
    }
    return ret;
}
const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const {
    PersonProfile** temp = m_email_to_profile.search(email);
    if (temp != nullptr){
        return *temp;
    }
    return nullptr;
}
