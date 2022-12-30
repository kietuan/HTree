#ifndef HTREE
#define HTREE

#define NODE_SIZE 100
#define LEAF_SIZE 200

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
    unsigned int (*hash) (const FILETYPE& ){};

public:
    HTree(unsigned int (*hash_function)(const FILETYPE&) = nullptr) : height{1} , hash {hash_function}
    {   
        if (!hash)
            hash = [] (const FILETYPE& file) -> unsigned int
                {
                    return std::hash<FILETYPE>() (file); //some types.
                };
        
        root = new Node(1, 0);
    }

    void insert(FILETYPE);
    void search(FILETYPE);
    void remove(FILETYPE);

private:
    void split(Node*, unsigned int position);
};

template <typename FILETYPE>
class HTree<FILETYPE>::Node
{
public:
    Entry entries[NODE_SIZE];

    unsigned int numEntries{};
    bool isLeaf = false;
    std::uint8_t level{};

    Node(unsigned int numEntries = 1, std::uint8_t level = 0): numEntries{numEntries}, isLeaf{false}, level{level}
    {}
};

template <typename FILETYPE>
struct HTree<FILETYPE>::Entry
{
    void* child{}; //có thể là lá hoặc node nội
    unsigned int   key{};
    bool isCollision = false;

    Entry(void* child = nullptr, unsigned int key = 0): child{child}, key{key}, isCollision{false}
    {}
};

template <typename FILETYPE>
class HTree<FILETYPE>::Leaf
{
public:
    FILETYPE value[LEAF_SIZE];
    int size{};
    unsigned int (*hash) (const FILETYPE& ){}; //thừa hưởng của class
    bool isLeaf = true;

    Leaf(int (*hash) (const FILETYPE& )): size{0}, hash{hash}, isLeaf{true}
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