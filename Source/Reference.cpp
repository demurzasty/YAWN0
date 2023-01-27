#include <YAWN/Reference.hpp>

using namespace YAWN;

void Reference::Retain() {
    ++_counter;
}

void Reference::Release() {
    if (--_counter == 0) {
        delete this;
    }
}

isize Reference::UseCount() const {
    return _counter;
}
