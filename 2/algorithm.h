#ifndef algorithm_h
#define algorithm_h
#include"vector.h"
typedef int pos_t;
template<typename T>
pos_t move_backward(pos_t start, pos_t stop, pos_t to) {
    to += stop - start;
    while (start != stop) { a[--to] = std::move(a[--stop]); }
    return to;
}
template<typename T>
pos_t move(pos_t start, pos_t stop, pos_t to) {
    while (start != stop) { a[to++] = std::move(a[start++]); }
    return to;
}
template<typename T>
pos_t copy_backward(pos_t start, pos_t stop, pos_t to) {
    to += stop - start;
    while (start != stop) { a[--to] = a[--stop]; }
    return to;
}
template<typename T>
pos_t copy(pos_t start, pos_t stop, pos_t to) {
    while (start != stop) { a[to++] = a[start++]; }
    return to;
}
template<typename T>
pos_t fill(pos_t start, pos_t stop, const T& x) {
    while (start != stop) { a[start++] = x; }
}
#endif // !algorithm_h