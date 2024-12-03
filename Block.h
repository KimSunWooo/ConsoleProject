#pragma once
#include<iostream>
#include<vector>
#include"color.h"
#include "ColorSelector.h"
using namespace std;

class Block {
protected:
    Color color;
    
    int y; // Y ��ǥ (���� ����)
    int startX;
    vector<vector<int>> blockShape = { {1, 1, 1, 1}, {1, 1, 1, 1} }; // �� ���

public:
    Block();
    ~Block();
    // ���� �ʱ�ȭ
    static void GenerateBlockLine(std::vector<Block>& blocks, vector<Block> height, ColorSelector selector, int blockWidth, int gap, int startY, int i);
    
    // ��� ����
    void GenerateBlock(int x, int y);

    // �� ����
    void SetColor(Color newColor);

    static void RemoveMatchingBlocks(vector<vector<Block>>& columns, vector<Block>& blocks);

    void ClearBlock() const;


    // ��� �ϴ� �̵�
    void BlockDown(int startY, ColorSelector& selector);
    void MoveBlocks(std::vector<Block>& blocks, int startY, ColorSelector& selector);
    // Getters
    int GetX() const;
    int GetY() const;
    Color GetColor() const;

    // == ������ �����ε�
    bool operator==(const Block& other) const;

    // ��� ���
    vector<string> DrawBlock(int level);
   
};

