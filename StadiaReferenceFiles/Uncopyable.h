#pragma once

// from meyers 55 ways, item 6
// privately inherit from this class to disallow copy
class Uncopyable {
protected:
    Uncopyable() {}                                     // allow construction
    virtual ~Uncopyable(){}                             // and destruction
private:
    Uncopyable(const Uncopyable&) = delete;             // but prevent copying
    Uncopyable& operator=(const Uncopyable&) = delete;  // and assignment
	Uncopyable(const Uncopyable&&) = delete;            // and move
	Uncopyable& operator=(const Uncopyable&&) = delete; // and move assignment
};