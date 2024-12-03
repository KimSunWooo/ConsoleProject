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
Block::Block() : color(Color::Red), y(6), startX(0),  blockShape()
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
    return startX == other.startX && y == other.y && color == other.color;
}

vector<string> Block::DrawBlock(int level) {
    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            if (blockShape[i][j] == 1) {
                cout << "\033[" << (y + i) << ";" << (startX + j * 2) << "H"; // 수정된 X 좌표 사용

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
    }
    cout << endl; // 마지막 줄에 개행
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
    y += 2; // 블록을 아래로 이동
}

std::atomic<bool> isBlockMoving(false);
void Block::MoveBlocks(std::vector<Block>& blocks, int startY, ColorSelector& selector) {
    if (!isBlockMoving.exchange(true, std::memory_order_relaxed)) {
        for (auto& block : blocks) {
            block.BlockDown(startY, selector);
        }
        isBlockMoving.store(false, std::memory_order_relaxed);
    }
}

int Block::GetX() const {
    return startX;
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

void Block::RemoveMatchingBlocks(vector<vector<Block>>& columns, vector<Block>& blocks) {
    vector<Block> blocksToRemove;

    // 각 세로줄 검사
    for (auto& column : columns) {
        while (column.size() >= 3) {
            const auto& last = column[column.size() - 1];
            const auto& secondLast = column[column.size() - 2];
            const auto& thirdLast = column[column.size() - 3];

            if (last.GetColor() == secondLast.GetColor() && secondLast.GetColor() == thirdLast.GetColor()) {
                // 제거할 블록을 추적
                blocksToRemove.push_back(last);
                blocksToRemove.push_back(secondLast);
                blocksToRemove.push_back(thirdLast);

                // 세로줄에서 제거
                column.pop_back();
                column.pop_back();
                column.pop_back();
            }
            else {
                break; // 더 이상 조건에 맞지 않으면 중단
            }
        }
    }

    // 제거된 블록 화면에서 지우기
    for (const auto& block : blocksToRemove) {
        block.ClearBlock();
    }

    // `blocks`에서 삭제
    blocks.erase(
        remove_if(blocks.begin(), blocks.end(), [&](const Block& block) {
            return find(blocksToRemove.begin(), blocksToRemove.end(), block) != blocksToRemove.end();
            }),
        blocks.end()
    );
}

void Block::ClearBlock() const{
    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            if (blockShape[i][j] == 1) {
                // 커서 이동: 블록 좌표
                int cursorX = startX + j * 2; // 블록의 기준 X + 내부 칸
                int cursorY = y + i;    // 블록의 기준 Y + 내부 줄

                cout << "\033[" << cursorY << ";" << cursorX << "H "; // 공백 출력
            }
        }
    }
    cout << endl;
}








