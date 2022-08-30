#include <iostream>

#include <dthread/dthread.hpp>
#include <dthread/threads/stdthread.hpp>

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
    Thread<Foo, StdThread> foo(std::make_tuple(2, 5), std::make_tuple());
    Thread<Bar, StdThread> bar(std::make_tuple(), std::make_tuple());

    foo.start();
    std::cout << "Hello " << foo->a << "\n";
    bar.start(8);

    bar.join();
    foo.join();

    std::cout << foo->a << '\n';
}
