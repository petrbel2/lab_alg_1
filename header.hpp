#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include <utility>

float** generate_matrix(int n) {
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<> dist(-1000, 1000);
    float ** the_matrix = new float*[n];
    for (int counter_1 = 0; counter_1 < n; counter_1++) {
        the_matrix[counter_1] = new float[n];
        for (int counter_2 = 0; counter_2 < n; counter_2++) {
            the_matrix[counter_1][counter_2] = dist(gen);
        }
    }
    return the_matrix;
}

float** copy_matrix(int n, float** matrix) {
    float ** new_matrix = new float*[n];
    for (int row = 0; row < n; row++) {
        new_matrix[row] = new float[n];
        for (int col = 0; col < n; col++) {
            new_matrix[row][col] = matrix[row][col];
        }
    }
    return new_matrix;
}

float* generate_b(int n) {
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<> dist(-1000, 1000);
    float * the_b = new float[n];
    for (int counter_1 = 0; counter_1 < n; counter_1++) {
        the_b[counter_1] = dist(gen);
        }
    return the_b;
}

float* copy_b(int n, float* b) {
    float * new_b = new float[n];
    for (int counter_1 = 0; counter_1 < n; counter_1++) {
        new_b[counter_1] = b[counter_1];
        }
    return new_b;
}

void matrix_deleter(float **matrix_to_delete, int n) {
    for (int delete_counter = 0; delete_counter < n; delete_counter++) {
        delete[] matrix_to_delete[delete_counter];
    }
    delete[] matrix_to_delete;
}

float* Hauss_without_choice(int n, float **start_matrix, float *start_part) {
    float ** Hauss_matrix = copy_matrix(n, start_matrix);
    float * right_part = copy_b(n, start_part);
    for (int big_counter = 0; big_counter < n - 1; big_counter++) {
        for (int norm_c_1 = big_counter + 1; norm_c_1 < n; norm_c_1++) {
            float factor = Hauss_matrix[norm_c_1][big_counter] / Hauss_matrix[big_counter][big_counter];
            for (int norm_c_2 = big_counter; norm_c_2 < n; norm_c_2++) {
                Hauss_matrix[norm_c_1][norm_c_2] -= factor * Hauss_matrix[big_counter][norm_c_2];
            }
            right_part[norm_c_1] -= factor * right_part[big_counter];
        }
    }
    for (int backtrack = (n - 1); backtrack > -1; backtrack--) {
        right_part[backtrack] = right_part[backtrack] / Hauss_matrix[backtrack][backtrack];
        for (int go_up = (backtrack - 1); go_up > -1; go_up--) {
            right_part[go_up] = (right_part[go_up] - Hauss_matrix[go_up][backtrack] * right_part[backtrack]);
            }
    }
    matrix_deleter(Hauss_matrix, n);
    return right_part;
}

float* Hauss_with_choice(int n, float **start_matrix, float *start_part) {
    float ** Hauss_matrix = copy_matrix(n, start_matrix);
    float * right_part = copy_b(n, start_part);
    float technikal = 0;
    for (int big_counter = 0; big_counter < (n - 1); big_counter++) {
    float max_elem = 0;
    int max_elem_num = 0;
    for (int counter = big_counter; counter < n; counter++) {
        if (std::abs(Hauss_matrix[counter][big_counter]) > max_elem) {
            max_elem = std::abs(Hauss_matrix[counter][big_counter]);
            max_elem_num = counter;
        }
    }
    technikal = right_part[big_counter];
    right_part[big_counter] = right_part[max_elem_num];
    right_part[max_elem_num] = technikal;
    for (int counter_2 = big_counter; counter_2 < n; counter_2++) {
        technikal = Hauss_matrix[big_counter][counter_2];
        Hauss_matrix[big_counter][counter_2] = Hauss_matrix[max_elem_num][counter_2];
        Hauss_matrix[max_elem_num][counter_2] = technikal;
    }
    for (int norm_c_1 = big_counter + 1; norm_c_1 < n; norm_c_1++) {
            float factor = Hauss_matrix[norm_c_1][big_counter] / Hauss_matrix[big_counter][big_counter];
            for (int norm_c_2 = big_counter; norm_c_2 < n; norm_c_2++) {
                Hauss_matrix[norm_c_1][norm_c_2] -= factor * Hauss_matrix[big_counter][norm_c_2];
            }
            right_part[norm_c_1] -= factor * right_part[big_counter];
        }
    }
    for (int backtrack = (n - 1); backtrack > -1; backtrack--) {
        right_part[backtrack] = right_part[backtrack] / Hauss_matrix[backtrack][backtrack];
        for (int go_up = (backtrack - 1); go_up > -1; go_up--) {
            right_part[go_up] = (right_part[go_up] - Hauss_matrix[go_up][backtrack] * right_part[backtrack]);
            }
    }
    matrix_deleter(Hauss_matrix, n);
    return right_part;
}

std::pair<float**, float**> LU(int n, float**start_A) {
    float ** A = copy_matrix(n, start_A);
    float ** L = new float*[n];
    float ** U = new float*[n];
    for (int counter = 0; counter < n; counter++) {
        L[counter] = new float[n];
        U[counter] = new float[n];
        for (int col_counter = 0; col_counter < n; col_counter++) {
            L[counter][col_counter] = 0;
            U[counter][col_counter] = 0;
        }
        L[counter][counter] = 1;
    }
    float sum = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            sum = 0;
            if (row <= col) {
                for (int counter = 0; counter < row; counter++) {
                    sum += L[row][counter] * U[counter][col];
                }
                U[row][col] = A[row][col] - sum;
            }
            else {
                for (int counter = 0; counter < col; counter++) {
                    sum += L[row][counter] * U[counter][col];
                }
                if (U[col][col] > 1e-10f) {
                    L[row][col] = (A[row][col] - sum) / U[col][col];
                }
                else {
                    L[row][col] = 0;
                }
            }
        }
    }
    matrix_deleter(A, n);
    return std::make_pair(L, U);
}

float* direct_substitution(float** matrix, float* right_part, int n) {
    float* b = copy_b(n, right_part);
    for (int counter = 0; counter < n; counter++) {
        b[counter] = b[counter] / matrix[counter][counter];
        for (int counter_2 = (counter + 1); counter_2 < n; counter_2++) {
            b[counter_2] = b[counter_2] - matrix[counter_2][counter] * b[counter];
        }
    }
    return b;
}

float* back_substitution(float** matrix, float* b, int n) {
    for (int backtrack = (n - 1); backtrack > -1; backtrack--) {
        b[backtrack] = b[backtrack] / matrix[backtrack][backtrack];
        for (int go_up = (backtrack - 1); go_up > -1; go_up--) {
            b[go_up] = (b[go_up] - matrix[go_up][backtrack] * b[backtrack]);
        }
    }
    return b;
}

float** Hilbert_matrix_maker(int n){
    float ** the_matrix = new float*[n];
    for (int counter_1 = 0; counter_1 < n; counter_1++) {
        the_matrix[counter_1] = new float[n];
        for (int counter_2 = 0; counter_2 < n; counter_2++) {
            the_matrix[counter_1][counter_2] = (1.0 / float((counter_1 + counter_2 + 1)));
        }
    }
    return the_matrix;
}

float* Hilbert_answers(float**matrix, int n) {
    float* right_part = new float[n];
    for (int big_counter = 0; big_counter < n; big_counter++) {
        right_part[big_counter] = 0;
        for (int small_counter = 0; small_counter < n; small_counter++) {
            right_part[big_counter] += matrix[big_counter][small_counter];
        }
    }
    return right_part;
}

float relative_inac(float* results, int n) {
    float inaccuracy = 0.0;
    float result = 0.0;
    for (int counter = 0; counter < n; counter++) {
        inaccuracy += (results[counter] - 1) * (results[counter] - 1);
    }
    result = sqrt(inaccuracy) / sqrt(n);
    return result;
}

double nevyaska(float**matrix, float*results, float*right_part, int n) {
    double answer = 0;
    double anti_b = 0;
    for (int counter_1 = 0; counter_1 < n; counter_1++) {
        anti_b = 0;
        for (int counter_2 = 0; counter_2 < n; counter_2++) {
            anti_b += matrix[counter_1][counter_2] * results[counter_2];
        }
        answer += ((anti_b - right_part[counter_1]) * (anti_b - right_part[counter_1]));
    }
    return sqrt(answer);
}
