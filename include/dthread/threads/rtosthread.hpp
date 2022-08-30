#pragma once

#include <functional>

/*
#include "FreeRTOS.h"
#include "task.h"
*/

using UBaseType_t = unsigned char;
using TaskHandle_t = unsigned;

extern int xTaskCreate(void(*)(void*), const char*, unsigned short, void*, UBaseType_t, TaskHandle_t*);

// This ensures there is only one definition of function in entire program
// THIS VERSION IS CORRECT ONLY IF ONE THREAD SPAWNS ALL THE OTHERS.
// OTHERWISE THERE ARE NO GUARANTEES.
#ifdef DEFINE_FUNCTION
std::function<void(void*)> function;
#else
extern std::function<void(void*)> function;
#endif

namespace {
    template <typename Callable>
    inline void set_function(Callable&& callable) {
        function = &callable;
    }

    inline decltype(function) get_function() {
        return function;
    }

    inline void run_function(void* arg) {
        get_function()(arg);
    }
}

class RtosThread {
    private:

        const char* task_name;
        unsigned short stack_size;
        UBaseType_t priority;
        TaskHandle_t handle;

    public:
        RtosThread(const char* task_name, unsigned short stack_size = 100, UBaseType_t priority = 0)
            : task_name(task_name), stack_size(stack_size), priority(priority) {}

        template <typename Callable>
        bool start(Callable&& callable, void* arg) {
            xTaskCreate(run_function, task_name, stack_size, arg, priority, &handle);
            return true;
        }

        bool join() { return true; }
        bool detach() { return true; }

};
