set(BINARY ${CMAKE_PROJECT_NAME})

# TODO: Figure out why there are duplicate symbols
#        thingy_audio_white_noise.h
#        thingy_audio_white_noise.cpp
set(SOURCES
        thingy_audio.h
        thingy_defs.h
        thingy_display.h
        thingy_display.cc
        thingy_midi.h
        thingy_synth.h
        thingy_synth.cpp
        )

juce_add_console_app(${JUCE_TARGET}
        PRODUCT_NAME ${JUCE_TARGET})

target_sources(${JUCE_TARGET} PRIVATE main.cc ${SOURCES})
target_link_libraries(${JUCE_TARGET}
        PRIVATE
        # ConsoleAppData            # If you'd created a binary data target, you'd link to it here
        juce::juce_core
        juce::juce_audio_devices
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
        libarduino-dummy
        )
juce_generate_juce_header(${JUCE_TARGET})

add_library(${LIB_TARGET} STATIC ${SOURCES})
target_link_libraries(${LIB_TARGET}
        PUBLIC
        juce::juce_core
        juce::juce_audio_devices
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
        libarduino-dummy
        )
target_include_directories(${LIB_TARGET} PUBLIC .)