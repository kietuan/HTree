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
                }
    }
};

template <typename FILETYPE>
class HTree<FILETYPE>::Leaf
{
public:
    FILETYPE value[NODE_SIZE];
    int size{};
    int (*hash) (FILETYPE){};

    Leaf(): size{0}
    {}

    void sort()
    {
        std::sort(value, value + size, [] (FILETYPE& a, FILETYPE& b) -> bool
                                       {
                                            return (this->hash(a) < this->hash(b));
                                       } 
                 );
    }
};

template <typename FILETYPE>
class HTree<FILETYPE>::Node
{
public:
    int size{};
};

#endif