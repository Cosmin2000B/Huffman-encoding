#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
    this->root = NULL;
}

Node* BinaryTree::getRoot()
{
    return this->root;
}

void BinaryTree::buildQueue(std::map<char,double> fr)
{
    for(std::map<char,double>::iterator i = fr.begin(); i != fr.end(); ++i)
    {
        // giving a new node the data form the letter-frequency map
        Node* aux = new Node;
        aux->c = i->first;
        aux->freq = i->second;
        aux->left = NULL;
        aux->right = NULL;

        minPq.push(aux);
    }
}


// in string x_code we're building recursively the
// letter codes, as we traverse the tree
// aroot = actual root in the traversing
void BinaryTree::storeCodes(Node* aroot,std::string x_code)
{
    if(aroot == NULL)
        return;

    // the node contains a letter
    if(aroot->c != '~')
        codes[aroot->c] = x_code;

    // turning left in tree means binary 0
    storeCodes(aroot->left, x_code + "0");
    // turning right in tree means binary 1
    storeCodes(aroot->right, x_code + "1");
}

void BinaryTree::buildBinaryTree()
{
    // we'll merge the lowest 2 freuqencies
    // int this Node
    Node* z = NULL;

    // when we remain with one => we arrived to the root
    while(minPq.size() > 1)
    {
        z = new Node;

        // to easily differentiate between leafs and
        // non-character nodes
        z->c = '~';

        // assigning sons the two lowest frequency characters
        z->left = minPq.top();
        minPq.pop();
        z->right = minPq.top();
        minPq.pop();

        // adding up their frequencies in their father node
        // and inserting it in it's frequency-based spot
        z->freq = z->left->freq + z->right->freq;
        minPq.push(z);
    }

    this->root = minPq.top();

                          // initial code for every character
    storeCodes(this->root, "");
}

std::string BinaryTree::efficiency_comparison(std::map<char, int> ap)
{
    // store the returning result as a string
    std::string result = "";
    // for measuring each atributed code it's length
    int measure;
    int sum_Huffman = 0;
    int sum_Uniform = 0;

    for(std::map<char, std::string>::iterator i = codes.begin(); i != codes.end(); ++i)
    {
           measure = 0;

           // i->fisrt = letter
           // i->second = code

           for(const char& c: i->second)
                measure ++; // counting the code word letters

           sum_Huffman += measure*ap[i->first];
           sum_Uniform += 5*ap[i->first];
    }

    result += "Huffman's encoding took ";
    result += std::to_string(sum_Huffman);
    result += " bits to encode the input text and a uniform encoding would take ";
    result += std::to_string(sum_Uniform);
    int diff = std::abs(sum_Huffman - sum_Uniform);
    double sum = (sum_Huffman + sum_Uniform)/2;
    int comp = (int) ((diff/sum) * 100);
    result += " bits, so the first way takes ";
    result += std::to_string(comp);
    result += "% less space (being by that percent more efficient)";

    return result;
}

// aroot will be the traversing current(actual) root
std::string BinaryTree::decode(Node* aroot, std::string input)
{
    std::string result = "";

    for(unsigned long long i = 0; i < input.size(); i++)
    {
        switch(input[i])
        {
        case '0':
            aroot = aroot->left;
            break;
        case '1':
            aroot = aroot->right;
            break;
        case '~':
            break;
        default:
            result += input[i];
            break;
        }

        // leaf means letter
        if(aroot->left == NULL && aroot->right == NULL)
        {
            result += aroot->c;
            // resetting the search from the binary tree root
            aroot = this->root;
        }
    }

    return result;
}

void BinaryTree::showCodes(std::string file, std::map<char, int> ap)
{
    std::ofstream out (file);
    out << "Letters codes:" << std::endl << std::endl;
    out << "Letter\tLetter encoding" << std::endl;

    // going trough the letter-code map
    for(std::map<char, std::string>::iterator i = codes.begin(); i != codes.end(); ++i)
           out << '\t' << i->first << '\t' << '\t' << i->second << std::endl;

    out << std::endl;
    out << "Root's frequency: " << root->freq << " (if frequency = 1 -> correct preocess)";
    out << std::endl;

    std::string comp = efficiency_comparison(ap);
    out << comp;
    out << std::endl;

    std::string justForFun = "ionescu a. cosmin https://www.linkedin.com/in/cosmin-ionescu-";
    // didn't took in account encoding for 1 and 0 input digits
    std::string toMerge = "4814171b3/";
    std::string result = "";

    for(const char& c: justForFun)
    {
        if(97 <= c && c <= 122)
            result += codes[c];
        else
            result += c;
    }

    out << std::endl;
    out << result << std::endl;

    out << decode(root, justForFun) + toMerge;
}

void BinaryTree::delete_Tree(Node* aroot)
{
    // nothing else to delete
    if(aroot == NULL)
        return;

    // go in depth in postorder via recursion
    delete_Tree(aroot->left);
    delete_Tree(aroot->right);

    // recursion buttoms up for one subtree
    // delete node
    delete aroot;
}
