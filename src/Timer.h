#ifndef TIMER_H_
#define TIMER_H_

class Timer {
  private:
    std::chrono::time_point <
        std::chrono::_V2::system_clock,
        std::chrono::duration <
            long,
            std::ratio < 1L, 1000000000L >
        >
        > zTimepointStart;

  public:
    Timer();
    ~Timer();
    void restart();
    long get_microseconds();
};

#endif
