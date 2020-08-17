#include "ProgressBar.hpp"

void PrintProgressBar(const std::uint32_t done, const uint32_t total) noexcept {
  std::printf("\r Finished %d out of %d (%d %)", done, total,
              (int)(done / (float)total * 100));

  // constexpr std::uint32_t barLength = 50u;
  // const std::uint32_t done = doneTotalRatio * barLength;

  // for (std::uint32_t i = 0u; i < (int)done - 1; i++) std::putc('=', stdout);

  // std::putc('>', stdout);

  // for (std::uint32_t i = 0; i < barLength - done; i++) std::putc('-',
  // stdout);

  std::fflush(stdout);
}