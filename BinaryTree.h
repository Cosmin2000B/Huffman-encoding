#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <cmath>

// bt node structure
struct Node
{
    // information of node
    char c;
    double freq;

    // left son
    Node* left;
    // right son
    Node* right;
};

class BinaryTree
{
    // root of the binary tree;
    Node* root;

    // to store codes of letters
    std::map<char, std::string> codes;

    // so i can tell the priority queue how
    // to compare two pairs of type Node*
    class Compare
    {
    public:
            bool operator()(Node* n1, Node* n2)
            {
                return n1->freq > n2->freq;
            }
    };

    // minimnum priority queue - at every step of
    // building the binary tree we will merge by
    // adding up the frequiencies of the first two
    // elements (with the lowest frequencies)
    std::priority_queue<Node*, std::vector<Node*>, Compare> minPq;

    // -> internal use under public showCodes method
    // between uniform encoding and Huffman's,
    // because the english aplhabet has 26 letters
    // we'll need codes words of 5 letters (2^5=32 > 26)
    // to encode it in an uniform manner
    std::string efficiency_comparison(std::map<char,int> ap);

    public: // --------------------------------------------------

        BinaryTree();
        Node* getRoot();
        void buildQueue(std::map<char,double> fr);

        // will do a DFS preorder traversal of the created
        // binary tree to find the code for every letter,
        // will be stored in the codes map
        // (letters can be found only on leaf positions)
        void storeCodes(Node* aroot, std::string x_code);

        void buildBinaryTree();

        void showCodes(std::string file, std::map<char, int> ap);

        // decoding message from Huffman encoding to plain english
        std::string decode(Node* aroot, std::string input);

        void delete_Tree(Node* aroot);
};
