#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <iomanip>

using namespace std;

class Foo {
public:
    Foo():a(0),b(0){};
    ~Foo(){};
    int a;
    int b;
};

unsigned int n(10000000);

#define MTIME(func, str) {\
    auto start = std::chrono::system_clock::now();\
    {\
        for (unsigned int i = 0; i < n; i++) {\
            func\
        }\
    }\
    auto end = std::chrono::system_clock::now();\
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();\
    cout << std::right << std::setfill(' ') << std::setw(7) << str << " " << elapsed_seconds << " miliseconds" << endl; \
}

void c_pointer() {
    string wtype("c pointer");
    // 
    MTIME(
        Foo *foo = (Foo *)malloc(sizeof(Foo));
        free(foo);
    , wtype + " creation time"
    )
}

void simple_pointer() {
    string wtype("simple pointer");
    // 
    MTIME(
        Foo *foo = new Foo();
        delete foo;
    , wtype + " creation time"
    )
}

void shared_pointer() {
    string wtype("shared pointer");
    MTIME(
        shared_ptr<Foo> p(new Foo());
    , wtype + " creation time"
    )
}

void unique_pointer() {
    string wtype("unique pointer");
    MTIME(
        unique_ptr<Foo> p(new Foo());
    , wtype + " creation time"
    )
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        n = std::atoi(argv[1]);
    }

    for (unsigned int i = 0; i < n * 2; i++) {
        volatile Foo *foo = new Foo();
        delete foo;
    }

    cout << "Test passing with " << n << " iterations" << endl;
    c_pointer();
    simple_pointer();
    shared_pointer();
    unique_pointer();
    
    return 0;
}