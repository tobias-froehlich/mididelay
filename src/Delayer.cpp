#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "const.h"
#include "utils.h"
#include "Timer.h"
#include "TimedMessage.h"
#include "Parameters.h"
#include "Delayer.h"

Delayer::Delayer() {

}

Delayer::~Delayer() {

}

void Delayer::start() {
    zTimer.restart();
}


int Delayer::something_to_pull() {
    long time = zTimer.get_microseconds();
    for(TimedMessage timedMessage: zData) {
        if (timedMessage.get_time() <= time) {
            return 1;
        }
    }
    return 0;
}

std::vector < unsigned char> Delayer::pull() {
    long time = zTimer.get_microseconds();
    for(unsigned int i=0; i<zData.size(); i++) {
       if (zData[i].get_time() <= time) {
           std::vector < unsigned char> result =
                    zData[i].get_message();
           zData.erase(zData.begin() + i);
           std::cout << utils::message_to_string(
               result) << " ---->\n";
           return result;
       }
    }
    throw std::invalid_argument(
        "I thought, this cannot happen."
    );
}

void Delayer::push(std::vector < unsigned char >
        message) {
    int channel = utils::channel(message);
    int delay = zDelays[channel];
    TimedMessage timedMessage(
        zTimer.get_microseconds() + delay * 1000,
        message
    );
    std::cout << "---->" << utils::message_to_string(
            message) << "\n";
    zData.push_back(timedMessage);
}

void Delayer::read_parameter_file(
        std::string filename) {
    Parameters parameters;
    parameters.read_file(filename);

    if (!(parameters.name_occurs("channels"))) {
        throw std::invalid_argument(
            "Define channels!"
        );
    }
    if (!(parameters.name_occurs("delays"))) {
        throw std::invalid_argument(
            "Define delays!"
        );
    }
    std::vector < int > channels =
        utils::vector_str_to_int(
        parameters.get_values("channels"));
    std::vector < int > delays = utils::vector_str_to_int(
        parameters.get_values("delays"));
    if (channels.size() != delays.size()) {
        throw std::invalid_argument(
            "The number of delays must equal the number of channels!");
    }
    std::cout << "channels: "
              << utils::intvector_to_string(channels)
              << "\n";
    std::cout << "delays: "
              << utils::intvector_to_string(delays)
              << "\n";
    for(unsigned int i=0; i < channels.size(); i++) {
        for(unsigned int j=i+1; j < channels.size(); j++) {
            if (channels[i] == channels[j]) {
                throw std::invalid_argument(
                    "Each channels must appear only once!"
                );
            }
        }
    }
    for(unsigned int i = 0; i < 16; i++) {
        zDelays.push_back(0);
    }
    for(unsigned int i=0; i<16; i++) {
        for(unsigned int j = 0; j < channels.size(); j++) {
            if (channels[j] == (int)i + 1) {
                zDelays[i] = delays[j];
            }
        }
    }
    std::cout << "Array of delays: "
              << utils::intvector_to_string(zDelays)
              << "\n";

}

