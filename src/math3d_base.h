
#ifndef math3d_base
#define math3d_base 1

#include <iostream>

#include "core/core.h"

namespace math3d {
    class basicMath3dObject {
    public:
        void * operator new(size_t size){
            return internal_malloc(size, 16);
        }
        
        void operator  delete(void * p){
            internal_free(p);
        }

        void * operator new[] (size_t size) {
            return aligned_malloc(size, 16);
        }

        void operator delete[] (void * p) {
            aligned_free(p);
        }
    };
}

#endif 

