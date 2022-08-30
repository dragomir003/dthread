#pragma once

#include <exception>
#include <thread>

class StdThread {
private:

    std::thread handle;

    bool started{ false };
    bool finished{ false };

public:
    
    StdThread() = default;

    template <typename Callable, typename ...Args>
    bool start(Callable&&  callable, Args&& ...args) {
        try {
            std::thread new_handle(
                [&callable, &args...]() { callable(args...); }
            );
            std::swap(handle, new_handle);
            started = true;
            return true;
        } catch (std::exception& e) {
            return false;
        }
    }

    bool join() {
        if (!started || finished)
            return false;
        try {
            handle.join();
            finished = true;
            return true;
        } catch (std::exception& e) {
            return false;
        }
    }

    bool detach() {
        if (!started)
            return false;
        try {
            handle.detach();
            return true;
        } catch (std::exception& e) {
            return false;
        }
    }
};
