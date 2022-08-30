#include <iostream>

#include <dthread/dthread.hpp>

#define DEFINE_FUNCTION
#include <dthread/threads/rtosthread.hpp>

struct Foo {
    int a, b;

    Foo(int a, int b)
        : a(a), b(b) {}

    void operator()() {
        std::cout << "Foo " << a << ' ' << b << '\n';
        a += 2;
    }

    ~Foo() {
        std::cout << "Deleted Foo\n";
    }
};

struct Bar {
    Bar() = default;
    Bar(const Bar&) = delete;

    void operator()(int x) {
        std::cout << "Bar " << x << '\n';
    }

    ~Bar() {
        std::cout << "Deleted Bar\n";
    }
};

auto main() -> int {
    Thread<Foo, RtosThread> foo(std::make_tuple(2, 5), std::make_tuple("foo_task"));
    Thread<Bar, RtosThread> bar(std::make_tuple(), std::make_tuple("bar_task", 100, 1));

    foo.start();
    std::cout << "Hello " << foo->a << "\n";
    bar.start(8);

    /* Irrelevant in current implementation
    bar.join();
    foo.join();
    */

    std::cout << foo->a << '\n';
}
