#ifndef HTREE
#define HTREE

#define NODE_SIZE 20

#include <bits/stdc++.h>


template <typename FILETYPE>
class HTree
{
private:
    class Node;
    class Leaf;
    struct Entry;

    int height{}; //theo dõi chiều cao của cây;
    Node* root{};
    int (*hash) (FILETYPE){};

public:
    HTree(int (*hash_function)(FILETYPE) = nullptr) : hash {hash_function}
    {   
        if (!hash)
            hash = [] (FILETYPE& file) -> int
                {
                    return std::hash<FILETYPE>() (file) % NODE_SIZE; //some types.
                };
        
        root = new Node(0, 1);
        root->first_child      = new Leaf(this->hash);
        root->entries[0].child = new Leaf(this->hash);
    }

    void insert(FILETYPE);
    void search(FILETYPE);
    void remove(FILETYPE);
};

template <typename FILETYPE>
class HTree<FILETYPE>::Node
{
public:
    void* first_child{};
    Entry entries[NODE_SIZE - 1];
    unsigned int numEntries{};
    bool isLeaf = false;
    std::uint8_t level{};

    Node(std::uint8_t level, unsigned int numEntries = 1): first_child{nullptr}, numEntries{numEntries}, isLeaf{false}, level{level}
    {}
};

template <typename FILETYPE>
struct HTree<FILETYPE>::Entry
{
    void* child{};
    int   key{};
    bool isCollision = false;

    Entry(): child{nullptr}, key{0}, isCollision{0}
    {}
};

template <typename FILETYPE>
class HTree<FILETYPE>::Leaf
{
public:
    FILETYPE value[NODE_SIZE];
    int size{};
    int (*hash) (FILETYPE){}; //thừa hưởng của class
    bool isLeaf = true;

    Leaf(int (*hash) (FILETYPE)): size{0}, hash{hash}
    {}

    void sort()
    {
        std::sort(value, value + size, [this] (FILETYPE& a, FILETYPE& b) -> bool
                                       {
                                            return (this->hash(a) < this->hash(b));
                                       } 
                 );
    }

};




#endif