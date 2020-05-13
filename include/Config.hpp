#pragma once
#include <array>
#include <chrono>

namespace Config
{
    // Window sizes


    constexpr int linesCount = 4;

    constexpr std::chrono::milliseconds refreshInterval(300);

    // Figure sizes
    constexpr int machineWidth = 21;
    constexpr int machineHeight = 3;
    constexpr int standWidth = 19;
    constexpr int standHeight = 5;

    // Machine positions
    constexpr std::pair<int, int> invisible { -99, -99 };
    constexpr std::array<std::pair<int, int>, linesCount> doubleMachinePositions{ {
      { 15, 20 },
      { 29, 20 },
      { 43, 20 },
      { 57, 20 },
    } };
}