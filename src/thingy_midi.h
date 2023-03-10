//
// Created by Orion Letizi on 2/13/23.
//
#ifndef THINGY_THINGY_MIDI_H
#define THINGY_THINGY_MIDI_H
#include "thingy_defs.h"
namespace thingy {
    struct ThingyMidiMessage {
        Channel channel;
    };

    class ThingyMidiListener {
    public:
        virtual void onMidiMessage(ThingyMidiMessage message) = 0;
    };

    class ThingyMidiPublisher {
        ThingyMidiListener *listeners[128] = {}; // TODO: figure out how to use a real data structure in Arduino
        int count = 0;
    public:
        void addMidiListener(ThingyMidiListener *listener) {
            this->listeners[count++] = listener; // XXX: this will fail if there are more than 128 listeners.
        }
        void onMidiMessage(ThingyMidiMessage message) {
            for (int i =0; i<this->count; i++) {
                auto listener = listeners[i];
                std::cout << "Listener: " << listener << std::endl;
                listeners[i]->onMidiMessage(message);
            }
        }
    };

}
#ifdef TARGET_NATIVE

#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>

namespace thingy {
    using namespace std;

    class MidiBroker : public juce::MidiInputCallback {
        string name = "MidiBroker: ";
        vector<unique_ptr<juce::MidiInput>> inputs;
        ThingyMidiPublisher midiPublisher;

    public:
        ThingyMidiPublisher* getMidiPublisher() {
            return &midiPublisher;
        }
        // Connect to all the available midi inputs
        void connectToInputs() {
            auto devices = juce::MidiInput::getAvailableDevices();
            cout << this->name << "MIDI input device count: " << devices.size() << endl;
            for (int i = 0; i < devices.size(); i++) {
                auto device = devices[i];
                cout << this->name << "Midi input device[" << i << "]: " << device.name << endl;

                auto midiInput = juce::MidiInput::openDevice(device.identifier, this);
                //inputs.add(midiInput);
                cout << this->name << "Connected to " << midiInput->getName() << endl;
                midiInput->start();
                inputs.push_back(move(midiInput));
            }
        }

        // Handle incoming midi messages and dispatch them to callbacks
        void handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message) override {
            cout << this->name << "source: " << source->getName() << " ch: " << message.getChannel();
            if (message.isNoteOn()) {
                cout << "; note on : " << message.getNoteNumber();
                cout << "; velocity : " << (int) message.getVelocity();
                cout << "; f velocity: " << message.getFloatVelocity();
            }
            if (message.isNoteOff()) {
                cout << "; note off: " << message.getNoteNumber();
            }
            cout << endl;
            ThingyMidiMessage thingyMessage {};
            this->midiPublisher.onMidiMessage(thingyMessage);
        }

        void handlePartialSysexMessage(juce::MidiInput *source,
                                       const juce::uint8 *messageData,
                                       int numBytesSoFar,
                                       double timestamp) override {
            cout << this->name << "Partial Sysex! source: " << source << "; data: " << messageData;
            cout << "; numBytesSoFar: " << numBytesSoFar << "; timestamp: " << timestamp;
            cout << endl;
        }

    };
}
#else // Arduino implementation
// Implement Me!
#endif //TARGET_NATIVE

#endif //THINGY_THINGY_MIDI_H
