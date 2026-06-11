#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <cctype>
#include <iomanip>
#include <sstream>

// Класс узла дерева Хаффмана
class HuffmanNode {
public:
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f);
    HuffmanNode(int f, HuffmanNode* l, HuffmanNode* r);
    ~HuffmanNode();

    bool isLeaf() const;
    std::string toString() const;
};

// Класс дерева Хаффмана
class HuffmanTree {
public:
    HuffmanTree();
    HuffmanTree(const HuffmanTree& other);
    ~HuffmanTree();

    HuffmanTree& operator=(const HuffmanTree& other);

    void buildFromText(const std::string& text);
    void getCodes(std::map<char, std::string>& codes);
    void printTreeSideConsole();
    void printTreeSideFile(const std::string& filename, int width = 8);
    HuffmanNode* getRoot() const;
    std::string encode(const std::string& text);
    std::string decode(const std::string& encoded);
    void clear();

private:
    HuffmanNode* root;

    void deleteTree(HuffmanNode* node);
    HuffmanNode* copyTree(HuffmanNode* node);
    void buildCodesRecursive(HuffmanNode* node, std::string code, std::map<char, std::string>& codes);
    void printTreeSideRecursive(HuffmanNode* node, int level, std::ofstream& file, int width);
    void printTreeSideRecursiveConsole(HuffmanNode* node, int level);
    void getFrequencies(const std::string& text, std::map<char, int>& freq);
};
void Hamming15();
void Huffman1();
int inputMethod();
void Morse3();