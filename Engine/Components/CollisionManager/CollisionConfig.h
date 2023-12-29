#pragma once
#include <cstdint>

//CollisionAttribute
const uint32_t kCollisionAttributePlayer = 0b00001;
const uint32_t kCollisionAttributeEnemy = 0b00010;
const uint32_t kCollisionAttributeGoal = 0b00100;

//CollisionMask
const uint32_t kCollisionMaskPlayer = 0b11110;
const uint32_t kCollisionMaskEnemy = 0b11101;
const uint32_t kCollisionMaskGoal = 0b11011;

//形状
const uint32_t kCollisionPrimitiveSphere = 0b1;
const uint32_t kCollisionPrimitiveAABB = 0b1 << 1;