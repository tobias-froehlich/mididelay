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
    return 0;
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
    zChannels = utils::vector_str_to_int(
        parameters.get_values("channels"));
    zDelays = utils::vector_str_to_int(
        parameters.get_values("delays"));
    if (zChannels.size() != zDelays.size()) {
        throw std::invalid_argument(
            "The number of delays must equal the number of channels!");
    }
    std::cout << "channels: "
              << utils::intvector_to_string(zChannels)
              << "\n";
    std::cout << "delays: "
              << utils::intvector_to_string(zDelays)
              << "\n";
}

