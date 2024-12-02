#include "KeyManager.h"
#include "Block.h"
#include "Color.h"
#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include "ColorSelector.h"
using namespace std;
KeyManager m;
Block::Block() : color(Color::Red),x(16), y(6), startX(0),  blockShape()
{
}

Block::~Block()
{
}

void Block::GenerateBlockLine(std::vector<Block>& blocks, vector<Block> height, ColorSelector selector, int blockWidth, int gap, int startY, int i)
{
    Block b;
    int startX = 35 + i * (blockWidth + gap); // X 위치 계산
    b.GenerateBlock(startX, startY);
    Color color = selector.GetColor(1);      // 난수 기반 색상 선택
    b.SetColor(color);
    height.push_back(b);
    blocks.push_back(b); // 블록 추가
}

bool Block::operator==(const Block& other) const {
    return x == other.x && y == other.y && color == other.color;
}

vector<string> Block::DrawBlock(int level) {
    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            if (blockShape[i][j] == 1) {
                cout << "\033[" << (y + i) << ";" << (startX + j * 2) << "H";

                // 설정된 color에 따라 출력
                switch (color) {
                case Color::Red:
                    cout << "\033[31m■\033[0m"; // 빨강
                    break;
                case Color::Blue:
                    cout << "\033[34m■\033[0m"; // 파랑
                    break;
                case Color::Green:
                    cout << "\033[32m■\033[0m"; // 초록
                    break;
                case Color::Yellow:
                    cout << "\033[33m■\033[0m"; // 노랑
                    break;
                case Color::Purple:
                    cout << "\033[35m■\033[0m"; // 보라
                    break;
                default:
                    cout << "■"; // 기본값
                }
            }
        }
        cout << endl;
    }
    return vector<string>();
}

void Block::GenerateBlock(int startX, int y) {
    int blockWidth = 6; // 블럭 너비 계산
    int height = 2;     // 블럭 높이 고정

    this->startX = startX;
    this->y = y; // 통합된 Y 좌표 설정

    // 블럭 모양 초기화
    blockShape = vector<vector<int>>(height, vector<int>(blockWidth, 1)); // 2D 벡터로 블럭 생성
}

void Block::BlockDown(int startY, ColorSelector& selector) {
    y+=2;
    // 매번 호출 시 색상 변경
    Color newColor = selector.GetColor(1); // 새로운 색상 선택
     
}

std::atomic<bool> isBlockMoving(false);
void Block::MoveBlocks(std::vector<Block>& blocks, int startY, ColorSelector& selector)
{
    if (isBlockMoving.load(std::memory_order_relaxed)) {
        return; // 이동 중이면 중복 처리 방지
    }

    isBlockMoving.store(true, std::memory_order_relaxed); // 이동 시작

    for (auto& block : blocks) {
        block.BlockDown(startY, selector); // 블록 이동
    }

    isBlockMoving.store(false, std::memory_order_relaxed); // 이동 완료
}

int Block::GetX() const {
    return x;
}

// Y 좌표 반환
int Block::GetY() const {
    return y;
}

// 색상 반환
Color Block::GetColor() const {
    return color;
}

void Block::SetColor(Color newColor)
{
    this->color = newColor;
}

int Block::DestroyBlock(int level, std::string color)
{
    // 사라진 것으로 간주
    color = "none";
    int score = 1;

    return score;
}








