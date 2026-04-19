#include <iostream>
#include "header.hpp"

int main() {
    int nums[3] = {5, 10, 15};
    for (int matrix_size_counter = 0; matrix_size_counter < 3; matrix_size_counter++) {
        int n = nums[matrix_size_counter];
        float** H = Hilbert_matrix_maker(n);
        float* b = Hilbert_answers(H, n);
        float* result_1 = Hauss_without_choice(n, H, b);
        float* result_2 = Hauss_with_choice(n, H, b);
        std::pair L_U_pair = LU(n, H);
        float* mid_result = direct_substitution(L_U_pair.first, b, n);
        float* result_3 = back_substitution(L_U_pair.second, mid_result, n);
        std::cout<<"Inaccuracies for "<<n<<"-sized matrix"<<"\n";
        std::cout<<relative_inac(result_1, n)<<" ";
        std::cout<<relative_inac(result_2, n)<<" ";
        std::cout<<relative_inac(result_3, n)<<"\n";
        std::cout<<nevyaska(H, result_1, b, n)<<" ";
        std::cout<<nevyaska(H, result_2, b, n)<<" ";
        std::cout<<nevyaska(H, result_3, b, n)<<"\n";
        matrix_deleter(H, n);
        delete[] b;
        delete[] result_1;
        delete[] result_2;
        delete[] result_3;
        matrix_deleter(L_U_pair.first, n);
        matrix_deleter(L_U_pair.second, n);
    }
}