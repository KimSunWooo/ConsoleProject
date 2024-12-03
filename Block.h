#pragma once
#include<iostream>
#include<vector>
#include"color.h"
#include "ColorSelector.h"
using namespace std;

class Block {
protected:
    Color color;
    
    int y; // Y 좌표 (통합 변수)
    int startX;
    vector<vector<int>> blockShape = { {1, 1, 1, 1}, {1, 1, 1, 1} }; // 블럭 모양

public:
    Block();
    ~Block();
    // 한줄 초기화
    static void GenerateBlockLine(std::vector<Block>& blocks, vector<Block> height, ColorSelector selector, int blockWidth, int gap, int startY, int i);
    
    // 블록 생성
    void GenerateBlock(int x, int y);

    // 색 설정
    void SetColor(Color newColor);

    static void RemoveMatchingBlocks(vector<vector<Block>>& columns, vector<Block>& blocks);

    void ClearBlock() const;


    // 블록 하단 이동
    void BlockDown(int startY, ColorSelector& selector);
    void MoveBlocks(std::vector<Block>& blocks, int startY, ColorSelector& selector);
    // Getters
    int GetX() const;
    int GetY() const;
    Color GetColor() const;

    // == 연산자 오버로딩
    bool operator==(const Block& other) const;

    // 블록 출력
    vector<string> DrawBlock(int level);
   
};

