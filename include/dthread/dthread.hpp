#pragma once

#include <memory>

template <typename Object, typename ...ObjectArgs, size_t ...Indices>
std::unique_ptr<Object> create(std::tuple<ObjectArgs...>& args, std::index_sequence<Indices...>) {
    return std::make_unique<Object>(std::get<Indices>(args)...);
}

template <typename Object, typename ...ObjectArgs>
std::unique_ptr<Object> create(std::tuple<ObjectArgs...>&& args) {
    constexpr auto seq = std::make_index_sequence<sizeof...(ObjectArgs)>();
    return create<Object>(args, seq);
}

template <class Callable, class ThreadImpl>
class Thread {
private:

    std::unique_ptr<Callable> callable;
    std::unique_ptr<ThreadImpl> thread;

public:

    template <typename ...CallableArgs, typename ...ThreadArgs>
    Thread(std::tuple<CallableArgs...>&& cargs, std::tuple<ThreadArgs...>&& targs)
        : callable(create<Callable>(std::move(cargs))), thread(create<ThreadImpl>(std::move(targs))) {}

    template <typename ...Args>
    bool start(Args&&... args) {
        return thread->start(*callable.get(), args...);
    }

    bool join() {
        return thread->join();
    }

    bool detach() {
        return thread->detach();
    }

    Callable* operator->() {
        return callable.get();
    };
};
