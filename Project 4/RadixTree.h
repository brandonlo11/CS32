//
//  RadixTree.h
//  CS32 Project 4
//
//  Created by Brandon Lo on 3/5/22.
//

#ifndef RadixTree_h
#define RadixTree_h
#include <string>
#include <vector>
using namespace std;

const static int NUM_CHARS = 256; // Radix is the number of possible chars

template <typename ValueType>
class RadixTree {
    // fwd decl
    struct Edge;
    
    // node in our radix tree
    struct Node {
        Node(bool isLeaf) : m_isLeaf(isLeaf), m_value(nullptr) {
        }
        ~Node() {
            if (m_value != nullptr) {
                delete m_value;
            }
            for (int i = 0; i < m_edgeChars.size(); i++) {
                delete m_edges[(int)m_edgeChars[i]];
            }
        }
        Edge *getTransition(char transitionChar) {
            return m_edges[(int)transitionChar];
        }
        void addEdge(char transitionChar, string label) {
            m_edges[(int)transitionChar] = new Edge(label);
            m_edgeChars.push_back(transitionChar);
        }
        void addEdge(string label, Node *next) {
            m_edges[(int)label.at(0)] = new Edge(label, next);
            m_edgeChars.push_back(label.at(0));
        }
        int totalEdges() {
            return m_edgeChars.size();
        }
        void addValue(const ValueType &value) {
            if (m_value == nullptr) {
                // allocate if we have not already
                m_value = new ValueType;
            }
            *m_value = value;
        }
        
        bool m_isLeaf;
        // ValueType values should be stored in leaf nodes
        ValueType *m_value;
        Edge *m_edges[NUM_CHARS] = {nullptr}; // init all ptrs in array to nullptr
        // this vector is only to keep track of indices used in m_edges (m_edges should be sparse in general)
        vector<char> m_edgeChars;
    };
    
    // edge in our radix tree
    struct Edge {
        Edge(string label) : m_label(label) {
            m_next = new Node(true);
        }
        Edge(string label, Node *next) : m_label(label), m_next(next) {
        }
        ~Edge() {
            if (m_next != nullptr) {
                delete m_next;
            }
        }
        string m_label;
        Node *m_next;
    };
    
    Node *root;
    
    // Returns index of where the two strings diverge or do not match.  -1 is returned if they do not diverge
    int getFirstMismatchLetter(string word, string edgeWord) {
        int minLength = (word.length() < edgeWord.length()) ? (int) word.length() : (int) edgeWord.length();
        for (int i = 1; i < minLength; i++) {
            if (word.at(i) != edgeWord.at(i)) {
                return i;
            }
        }
        return -1;
    }
    
public:
    RadixTree() {
        root = new Node(false);
    }

    ~RadixTree() {
        delete root;
    }

    void insert(string key, const ValueType& value) {
        Node *current = root;
        int currIndex = 0;
 
        while (currIndex < key.length()) {
            char transitionChar = key.at(currIndex);
            Edge *currentEdge = current->getTransition(transitionChar);
            //Updated version of the input word
            string currStr = key.substr(currIndex);

            //There is no associated edge with the first character of the current string
            //so simply add the rest of the string and finish
            if (currentEdge == nullptr) {
                current->addEdge(transitionChar, currStr);
                current->m_edges[(int)transitionChar]->m_next->addValue(value);
                break;
            }

            int splitIndex = getFirstMismatchLetter(currStr, currentEdge->m_label);
            if (splitIndex == -1) {
                //The edge and leftover string are the same length
                //so finish and update the next node as a word node
                if (currStr.length() == currentEdge->m_label.length()) {
                    currentEdge->m_next->m_isLeaf = true;
                    currentEdge->m_next->addValue(value);
                    break;
                } else if (currStr.length() < currentEdge->m_label.length()) {
                    //The leftover word is a prefix to the edge string, so split
                    string suffix = currentEdge->m_label.substr(currStr.length());
                    currentEdge->m_label = currStr;
                    Node *newNext = new Node(true);
                    newNext->addValue(value);
                    Node *afterNewNext = currentEdge->m_next;
                    currentEdge->m_next = newNext;
                    newNext->addEdge(suffix, afterNewNext);
                    break;
                } else { //currStr.length() > currentEdge.label.length()
                    //There is leftover string after a perfect match
                    splitIndex = (int) currentEdge->m_label.length();
                }
            } else {
                //The leftover string and edge string differed, so split at point
                string suffix = currentEdge->m_label.substr(splitIndex);
                currentEdge->m_label = currentEdge->m_label.substr(0, splitIndex);
                Node *prevNext = currentEdge->m_next;
                currentEdge->m_next = new Node(false);
                currentEdge->m_next->addEdge(suffix, prevNext);
            }
            
            //Traverse the tree
            current = currentEdge->m_next;
            currIndex += splitIndex;
        }
    }

    ValueType* search(string key) const {
        Node *current = root;
        int currIndex = 0;
        while (currIndex < key.length()) {
            char transitionChar = key.at(currIndex);
            Edge *edge = current->getTransition(transitionChar);
            if (edge == nullptr) {
                return nullptr;
            }

            string currSubstring = key.substr(currIndex);
            // Testing if edge label is a prefix of currSubstring.  If it is not, return nullptr
            if (!(currSubstring.rfind(edge->m_label, 0) == 0)) {
                return nullptr;
            }
            currIndex += edge->m_label.length();
            current = edge->m_next;
        }
        // we are at the end, we don't even need to check for isLeaf. we can return m_value.  If it is a leaf, it should have a value, else nullptr
        return current->m_value;
    }
};

#endif /* RadixTree_h */
