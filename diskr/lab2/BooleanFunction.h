#pragma once

#include <bitset>
#include <vector>
#include <string>
#include <unordered_map>

struct BDDNode{
    int var; // 1=x1, 2=x2, 3=x3, 4=x4, или 0 для терминала
    BDDNode* low; // Ветвь для 0
    BDDNode* high; // Ветвь для 1
    int value; // Значение для терминала (0 или 1)
    
    BDDNode(int v, int val = -1) : var(v), low(nullptr), high(nullptr), value(val){}
};

class BooleanFunction{
private:
    std::bitset<16> truthTable;
    BDDNode* root;
    BDDNode* term0;
    BDDNode* term1;

public:
    BooleanFunction(int funcValue);
    ~BooleanFunction();
    void deleteBDD(BDDNode* node);

    int  getValue(int x1, int x2, int x3, int x4) const;
    void printTruthTable() const;
    std::string buildSDNF() const;
    std::string buildSKNF() const;

    BDDNode* buildRecursive(int level, int x1, int x2, int x3, int x4);
    void buildBDD();
    int evaluateBDD(int x1, int x2, int x3, int x4) const;

    std::vector<int> buildZhegalkin() const;
    void printZhegalkin(const std::vector<int>& c) const;
    int  evaluateZhegalkin(const std::vector<int>& c, int x1, int x2, int x3, int x4) const;
};