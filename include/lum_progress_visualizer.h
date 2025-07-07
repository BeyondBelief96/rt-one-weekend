#pragma once
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Lumina {
    class ProgressVisualizer {
    public:
        ProgressVisualizer(int total_scanlines, int width = 60);

        void update(int completed_scanlines);
        void finish();

    private:
        void clear_line();
        void print_ascii_art_bar(double percentage);
        std::string format_time(double seconds);
        std::string get_loading_spinner();
        bool detect_unicode_support();

        int total_scanlines;
        int bar_width;
        std::chrono::steady_clock::time_point start_time;
        int spinner_state;
        bool unicode_supported;

        // ASCII art elements - Unicode version
        static constexpr const char* FILLED_CHAR_UNICODE = "█";
        static constexpr const char* PARTIAL_CHARS_UNICODE[8] = { "", "▏", "▎", "▍", "▌", "▋", "▊", "▉" };
        static constexpr const char* EMPTY_CHAR_UNICODE = "░";
        static constexpr const char* SPINNER_CHARS_UNICODE[4] = { "◐", "◓", "◑", "◒" };

        // ASCII fallback elements
        static constexpr const char* FILLED_CHAR_ASCII = "#";
        static constexpr const char* EMPTY_CHAR_ASCII = "-";
        static constexpr const char* SPINNER_CHARS_ASCII[4] = { "|", "/", "-", "\\" };
    };
}