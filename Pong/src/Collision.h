#pragma once

#include "AABB.h"

bool BallPlayerCollision(const AABB& ball, const AABB& player) {
    if (ball.Max.x < player.Min.x || player.Max.x < ball.Min.x) {
        return false; // No collision
    }

    // If one box is above the other
    if (ball.Max.y < player.Min.y || player.Max.y < ball.Min.y) {
        return false; // No collision
    }

    return true; // Colliding
}