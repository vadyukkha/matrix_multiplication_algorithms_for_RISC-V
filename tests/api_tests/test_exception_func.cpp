#include "../api/matrix_lib.h"
#include <cassert>

int main() {
    MatrixLib::Matrix mat1(2, 3);
    MatrixLib::Matrix mat2(12, 23);

    try {
        mat1.setElement(10, 12, 1);
        assert(false && "Exception was not thrown as expected!");
    } catch (const std::out_of_range& e) {
        assert(true);
    }

    try {
        mat1.getElement(11, 22);
        assert(false && "Exception was not thrown as expected!");
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index out of range");
    }

    try {
        mat1.multiply(mat2);
        assert(false && "Exception was not thrown as expected!");
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Matrix sizes are not compatible");
    }

    return 0;
}
