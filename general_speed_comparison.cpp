#include <iostream>
#include "header.hpp"

int main() {
    int nums[4] = {100, 200, 500, 1000};
    for (int matrix_size_counter = 0; matrix_size_counter < 4; matrix_size_counter++) {
        int n = nums[matrix_size_counter];
        float** matrix = generate_matrix(n);
        float* b = generate_b(n);
        clock_t before = clock();
        float* result_1 = Hauss_without_choice(n, matrix, b);
        clock_t duration = clock() - before;
        std::cout<<"SimpleHauss: "<<(float)duration / CLOCKS_PER_SEC<<" seconds"<<"    ";
        before = clock();
        float* result_2 = Hauss_with_choice(n, matrix, b);
        duration = clock() - before;
        std::cout<<"ComplexHauss: "<<(float)duration / CLOCKS_PER_SEC<<" seconds"<<"    ";
        clock_t before_2 = clock();
        std::pair L_U_pair = LU(n, matrix);
        duration = clock() - before_2;
        std::cout<<"LUcreation: "<<(float)duration / CLOCKS_PER_SEC<<" seconds"<<"    ";
        before = clock();
        float* cent_result = direct_substitution(L_U_pair.first, b, n);
        float* result_3 = back_substitution(L_U_pair.second, cent_result, n);
        duration = clock() - before;
        std::cout<<"LUsubstitutions: "<<(float)duration / CLOCKS_PER_SEC<<" seconds"<<"    ";
        duration = clock() - before_2;
        std::cout<<"Full LU: "<<(float)duration / CLOCKS_PER_SEC<<" seconds"<<"\n";
        matrix_deleter(matrix, n);
        matrix_deleter(L_U_pair.first, n);
        matrix_deleter(L_U_pair.second, n);
        delete[] b;
        delete[] result_3;
        delete[] result_2;
        delete[] result_1;
    }
}
