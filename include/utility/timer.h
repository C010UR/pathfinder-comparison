#pragma once

#include <chrono>
#include <string>
#include <vector>

template <class DT = std::chrono::microseconds,
          class ClockT = std::chrono::high_resolution_clock>
class Timer {
   private:
    using timep_t = typename ClockT::time_point;
    timep_t _start = ClockT::now(), _end = {};

   public:
    void tick() {
        _end = timep_t{};
        _start = ClockT::now();
    }

    void tock() { _end = ClockT::now(); }

    template <class T = DT>
    auto duration() const {
        ;
        return std::chrono::duration_cast<T>(_end - _start);
    }

    template <class T = DT>
    std::string format(T duration) {
        std::string result;

        auto m = std::chrono::duration_cast<std::chrono::minutes>(
            duration % std::chrono::hours(1));
        auto s = std::chrono::duration_cast<std::chrono::seconds>(
            duration % std::chrono::minutes(1));
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            duration % std::chrono::seconds(1));
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(
            duration % std::chrono::milliseconds(1));

        return std::to_string(m.count()) + "m " + std::to_string(s.count()) +
               "s " + std::to_string(ms.count()) + "ms " +
               std::to_string(us.count()) + "us ";
    }
};