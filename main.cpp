#include <fstream>
#include "Reader.h"
#include "CalcFreq.h"
#include "BinaryTree.h"
#include <map>

int main()
{
    Reader* r = new Reader();
    r->read("input.txt");
    // output_1 => letters apparitions
    //          => total number of letters
    r->showAp("output_1.txt");

    CalcFrq* f = new CalcFrq();
    f->calcFr(r->getLitNr(), r->getAp());
    // output_2 => letters frequency
    //          => sum of frequencies
    f->writeFr("output_2.txt");

    BinaryTree* bt = new BinaryTree();
    bt->buildQueue(f->getFre());
    bt->buildBinaryTree();
    bt->showCodes("output_3.txt", r->getAp());
    bt->delete_Tree(bt->getRoot());

    return 0;
}
