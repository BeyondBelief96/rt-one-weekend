#include "lum_progress_visualizer.h"
#include <iostream>
#include <cmath>

namespace Lumina {

    ProgressVisualizer::ProgressVisualizer(int total_scanlines, int width)
        : total_scanlines(total_scanlines), bar_width(width), spinner_state(0) {
        start_time = std::chrono::steady_clock::now();
        unicode_supported = detect_unicode_support();

        // Print header - use simple ASCII for better compatibility
        std::cout << "\n";
        std::cout << "+==============================================================+\n";
        std::cout << "|                   * LUMINA RAY TRACER *                     |\n";
        std::cout << "+==============================================================+\n";
        std::cout << "\n";
    }

    void ProgressVisualizer::update(int completed_scanlines) {
        clear_line();

        double percentage = static_cast<double>(completed_scanlines) / total_scanlines;

        // Calculate timing
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count() / 1000.0;

        double estimated_total = (elapsed / percentage);
        double eta = estimated_total - elapsed;

        // Print the fancy progress bar
        std::cout << "Progress: ";
        print_ascii_art_bar(percentage);

        std::cout << " " << std::fixed << std::setprecision(1) << (percentage * 100) << "%";
        std::cout << " " << get_loading_spinner();
        std::cout << " [" << completed_scanlines << "/" << total_scanlines << "]";
        std::cout << " Time: " << format_time(elapsed);

        if (percentage > 0.01) { // Only show ETA after 1% to avoid wild estimates
            std::cout << " ETA: " << format_time(eta);
        }

        std::cout << std::flush;
        spinner_state = (spinner_state + 1) % 4;
    }

    void ProgressVisualizer::finish() {
        auto end_time = std::chrono::steady_clock::now();
        auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;

        clear_line();
        std::cout << "COMPLETE! ";
        print_ascii_art_bar(1.0);
        std::cout << " 100.0% ";
        std::cout << " Total time: " << format_time(total_time) << "\n\n";

        // Print completion art - ASCII compatible
        std::cout << "+==============================================================+\n";
        std::cout << "|  * Rendering completed successfully! *                      |\n";
        std::cout << "|                                                              |\n";
        std::cout << "|    #####   #####  ##   ## #######                           |\n";
        std::cout << "|    ##  ## ##   ## ###  ## ##                                |\n";
        std::cout << "|    ##  ## ##   ## ## # ## #####                             |\n";
        std::cout << "|    ##  ## ##   ## ##  ### ##                                |\n";
        std::cout << "|    #####   #####  ##   ## #######                           |\n";
        std::cout << "+==============================================================+\n";
        std::cout << "\n";
    }

    void ProgressVisualizer::clear_line() {
        std::cout << "\r\033[K";
    }

    void ProgressVisualizer::print_ascii_art_bar(double percentage) {
        double filled_exact = percentage * bar_width;
        int filled_full = static_cast<int>(filled_exact);

        std::cout << "[";
        // ASCII fallback version
        for (int i = 0; i < bar_width; ++i) 
        {
            if (i < filled_full) {
                std::cout << FILLED_CHAR_ASCII;
            }
            else {
                std::cout << EMPTY_CHAR_ASCII;
            }
        }

        std::cout << "]";
    }

    std::string ProgressVisualizer::format_time(double seconds) {
        int hours = static_cast<int>(seconds) / 3600;
        int minutes = (static_cast<int>(seconds) % 3600) / 60;
        int secs = static_cast<int>(seconds) % 60;

        std::stringstream ss;
        if (hours > 0) {
            ss << hours << "h " << minutes << "m " << secs << "s";
        }
        else if (minutes > 0) {
            ss << minutes << "m " << secs << "s";
        }
        else {
            ss << std::fixed << std::setprecision(1) << seconds << "s";
        }
        return ss.str();
    }

    std::string ProgressVisualizer::get_loading_spinner() 
    {
            return SPINNER_CHARS_ASCII[spinner_state];
    }

    bool ProgressVisualizer::detect_unicode_support() {
        // Simple heuristic: assume Windows terminals don't support Unicode well
        // unless it's Windows Terminal or a modern terminal
#ifdef _WIN32
    // Check if we're in Windows Terminal or a modern terminal
        const char* term = std::getenv("WT_SESSION");
        const char* term_program = std::getenv("TERM_PROGRAM");
        if (term != nullptr || (term_program != nullptr && std::string(term_program) == "vscode")) {
            return true;  // Windows Terminal or VS Code terminal
        }
        return false;  // Assume older Windows terminal
#else
        return true;   // Assume Unix terminals support Unicode
#endif
    }

    // Initialize static constexpr arrays
    constexpr const char* ProgressVisualizer::SPINNER_CHARS_ASCII[4];
}