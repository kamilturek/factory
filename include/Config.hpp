#pragma once
#include <array>

namespace Config
{
    constexpr int linesCount = 4;

    // Figure sizes
    constexpr int machineWidth = 21;
    constexpr int machineHeight = 3;
    constexpr int standWidth = 19;
    constexpr int standHeight = 5;
    constexpr int carWidth = 15;
    constexpr int carHeight = 4;

    // Machine positions
    constexpr std::pair<int, int> invisible { -99, -99 };
    constexpr std::array<std::pair<int, int>, linesCount> doubleMachinePositions{ {
      { 15, 20 },
      { 29, 20 },
      { 43, 20 },
      { 57, 20 },
    } };
}