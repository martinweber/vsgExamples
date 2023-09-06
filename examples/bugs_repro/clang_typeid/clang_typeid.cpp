#include <cstdlib>
#include <iostream>
#include "clang_typeid_dylib.h"

int main(int argc, char** argv)
{
    auto local = vsg::MatrixTransform::create();
    auto dylib = create_object_in_dylib();

    std::cout << "Local: type name: " << local->type_info().name() << ", type hash: " << local->type_info().hash_code() << std::endl;
    std::cout << "Dylib: type name: " << dylib->type_info().name() << ", type hash: " << dylib->type_info().hash_code() << std::endl;

    std::cout << (dylib->is_compatible(local->type_info()) ? "types are compatible" : "types are not compatible") << std::endl;

    // this dynamic_cast will result in the following clang_typeid runtime error when executed with debugger attached:
    // clang_typeid[30194:379372] dynamic_cast error 2: One or more of the following type_info's has hidden visibility or is defined
    // in more than one translation unit. They should all have public visibility. N3vsg6ObjectE, N3vsg15MatrixTransformE, N3vsg15MatrixTransformE.
    auto matrix_transform_ptr = dynamic_cast<vsg::MatrixTransform*>(dylib.get());
    assert(matrix_transform_ptr != nullptr);

    return EXIT_SUCCESS;
}
