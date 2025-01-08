#include "reloadable_library.hpp"

extern "C" {
    EXPORT_API int calculate(int x, int y) {
        return x + y;
    }
}