#ifndef TIMED_MESSAGE_H_
#define TIMED_MESSAGE_H_
class TimedMessage {
  private:
    long zTime = 0;
    std::vector < unsigned char > zMessage{};

  public:
    TimedMessage(long time, std::vector < unsigned char > message);
    
    ~TimedMessage();
    long get_time();
    std::vector < unsigned char > get_message();
    std::string get_string();
};
#endif
