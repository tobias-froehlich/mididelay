#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <Stk.h>
#include <RtMidi.h>
#include "const.h"
#include "utils.h"
#include "Parameters.h"
#include "Timer.h"
#include "TimedMessage.h"
#include "Delayer.h"

void task_user_input(int* flag) {
    std::string text;
    while (*flag) {
        std::cin >> text;
        if (text.compare("quit") == 0) {
            *flag = 0;
        }
    }
}

void task_loop(int* flag,
        std::string parameterFilename) {
    Delayer delayer;
    delayer.read_parameter_file(parameterFilename);
    RtMidiIn* midiin = 0;
    try {
        midiin = new RtMidiIn(
            RtMidi::UNSPECIFIED,
            "mididelay in"
        );
    } catch(RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
    midiin->openVirtualPort();
    midiin->ignoreTypes(true, true, true);
    RtMidiOut* midiout = 0;
    try {
        midiout = new RtMidiOut(
            RtMidi::UNSPECIFIED,
            "mididelay out"
        );
    } catch(RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
    midiout->openVirtualPort();
    std::vector < unsigned char > message;
    message.clear();
    while (*flag) {
        std::cout << "hallo\n";
        midiin->getMessage(&message);
        if (message.size() >= 3) {
            delayer.push(message);
            message.clear();
        }
        if (delayer.something_to_pull()) {
            message = delayer.pull();
            midiout->sendMessage(&message);
            message.clear();
        }
        usleep(100000);
    }
    midiin->closePort();
    midiout->closePort();
}

int main(int argc, char** argv) {
    if (argc != 1 + 1) {
        std::cout << "You need to specify a parameter file.\n";
    }
    else {
        std::string parameterFilename(argv[1]);

        int flag = 1;
        std::thread thread_user_input(
            task_user_input,
            &flag
        );
    
        std::thread thread_loop(
            task_loop,
            &flag, parameterFilename
        );
        thread_user_input.join();
        thread_loop.join();
        std::cout << "Quit.\n";
    }
}
