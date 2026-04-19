#include <iostream>
#include "header.hpp"

int main() {
    int nums[3] = {1, 10, 100};
    int n = 500;
    clock_t before = 0;
    clock_t LU_time = 0;
    clock_t Hauss_time = 0;
    for (int matrix_amount_counter = 0; matrix_amount_counter < 3; matrix_amount_counter++) {
        int k = nums[matrix_amount_counter];
        float** matrix = generate_matrix(n);
        before = clock();
        std::pair L_U_pair = LU(n, matrix);
        LU_time += clock() - before;
        for (int counter = 0; counter < k; counter++) {
            float* b = generate_b(n);
            before = clock();
            float* result_1 = Hauss_with_choice(n, matrix, b);
            Hauss_time += clock() - before;
            before = clock();
            float* mid_result = direct_substitution(L_U_pair.first, b, n);
            float* result_2 = back_substitution(L_U_pair.second, mid_result, n);
            LU_time += clock() - before;
            delete[] b;
            delete[] result_1;
            delete[] result_2;
        }
        std::cout<<"Hauss_time: "<<(float)Hauss_time / CLOCKS_PER_SEC<<" seconds"<<"    ";
        std::cout<<"LU_time: "<<(float)LU_time / CLOCKS_PER_SEC<<" seconds"<<"\n";
        matrix_deleter(matrix, n);
        matrix_deleter(L_U_pair.first, n);
        matrix_deleter(L_U_pair.second, n);
    }
}