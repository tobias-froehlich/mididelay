#include <chrono>
#include "Timer.h"

Timer::Timer() {
  zTimepointStart =
    std::chrono::system_clock::now();
}

Timer::~Timer() {

}

void Timer::restart() {
  zTimepointStart =
    std::chrono::system_clock::now(); 
}

long Timer::get_microseconds() {
  auto timepoint =
    std::chrono::system_clock::now();
  return std::chrono::duration_cast <
    std::chrono::microseconds
  > (
    timepoint - zTimepointStart
  ).count();
}
