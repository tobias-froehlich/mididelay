#ifndef DELAYER_H_
#define DELAYER_H_

class Delayer {
    private:
        std::vector < TimedMessage > zData{};
        Timer zTimer;
        std::vector < int > zChannels;
        std::vector < int > zDelays;
    public:
        Delayer();
        ~Delayer();
        void start();
        int something_to_pull();
        std::vector < unsigned char > pull();
        void read_parameter_file(
                std::string filename);
};

#endif
