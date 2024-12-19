#include <SparceMatrix.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

int
main() {
    // std::cout.precision(2);

    SMatrix m1(6, 5);
    m1.setValue(10, 2, 4);
    float tmp = m1[2][2]; // чтение записанного значение
    tmp = m1[3][2];       // чтение нуля
    SMatrix m2(5, 6);
    m2 = m1.transpose();

    std::cout << "Transposing:\n" << m1 << '\n' << m2;

    SMatrix m3(m2);
    m3 += m2;
    std::cout << "Arithmetics:\n" << m2 << '\n' << m3;

    SMatrix m4(3, 2);
    SMatrix m5(2, 3);
    m4.setValue(1, 0, 0);
    m5.setValue(1, 0, 0);
    m4 *= m5;
    std::cout << '\n' << m4;

    SMatrix m6(3, 3);
    m6.setValue(1, 0, 0);
    m6.setValue(2, 0, 1);
    m6.setValue(3, 1, 0);
    m6.setValue(4, 1, 1);
    m6.setValue(1, 2, 0);
    m6.setValue(1, 2, 1);
    m6.setValue(1, 2, 2);
    m6.setValue(1, 0, 2);
    m6.setValue(1, 1, 2);
    std::cout << '\n' << "matrix: \n" << m6 << "\nDeterminant = " << m6.getDeterminant() << '\n';
    SMatrix m7 = m6.getBackwardsMatrix();
    std::cout << "backwards matrix: \n" << m7;
    m7 = pow(m7, 2U);
    std::cout << "powered by 2: \n" << m7;
    m7 = pow(m7, 2.4F);
    std::cout << "powered by 2 again: \n" << m7;

    std::cout << "before adding 1: \n" << m6;
    m6 += 1;
    std::cout << "added 1: \n" << m6;
    m6 -= 2;
    std::cout << "substracted 2: \n" << m6;
    m6 *= 2;
    std::cout << "mul 2: \n" << m6;

    m6.powElementwise(2);
    std::cout << "pow 2: \n" << m6;

    std::cout << "\n\ntesting speeds of matrices... \n";

    size_t size_x, size_y;
    std::vector<std::vector<long>> testMatricVector;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    size_x = 1000;
    size_y = 2000;

    SMatrix testMatricCustom(size_x, size_y);

    std::cout << "test1: creating matrices: \n";
    begin = std::chrono::steady_clock::now();
    testMatricVector.reserve(size_x);
    for (int i = 0; i < size_y; ++i) {
        testMatricVector.push_back(std::vector<long>(size_y));
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Vector took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    testMatricVector.reserve(size_x);
    end = std::chrono::steady_clock::now();
    std::cout << "SMatrix took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    std::cout << "filling matrices.. \n";

    int rndVal;
    int rndVal2;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1k(1, 1000); // распределение от 0 до 1000

    for (int i = 0; i < size_x; ++i) {
        for (int j = 0; j < size_y; ++j) {
            rndVal = dist1k(rng);
            rndVal2 = dist1k(rng);
            if (rndVal == 1) { // только 1/1000 матрицы заполнится
                testMatricCustom.setValue(rndVal2, i, j);
                testMatricVector[i][j] = rndVal2;
            }
        }
    }

    std::cout << "test2: multiplying by value \n";

    int value = 10;

    begin = std::chrono::steady_clock::now();
    std::for_each(testMatricVector.begin(), testMatricVector.end(), [value](std::vector<long>& el) {
        std::for_each(el.begin(), el.end(), [value](long& num) { num *= value; });
    });
    end = std::chrono::steady_clock::now();
    std::cout << "Vector took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    testMatricCustom *= 10;
    end = std::chrono::steady_clock::now();
    std::cout << "SMatrix took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    std::cout << "test3: assign some value \n";

    begin = std::chrono::steady_clock::now();
    testMatricVector[100][200] = 0;
    end = std::chrono::steady_clock::now();
    std::cout << "Vector took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    testMatricCustom.setValue(0, 100, 200);
    end = std::chrono::steady_clock::now();
    std::cout << "SMatrix took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    std::cout << "test4: same but in the end of list \n";

    begin = std::chrono::steady_clock::now();
    testMatricVector[1000][2000] = 0;
    end = std::chrono::steady_clock::now();
    std::cout << "Vector took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    testMatricCustom.setValue(0, 1000, 2000);
    end = std::chrono::steady_clock::now();
    std::cout << "SMatrix took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    std::cout << "test5: access 1000 random cells \n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        testMatricVector[dist1k(rng)][dist1k(rng)];
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Vector took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        testMatricCustom[dist1k(rng)][dist1k(rng)];
    }
    end = std::chrono::steady_clock::now();
    std::cout << "SMatrix took \t= \t" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << "[µs]" << std::endl;
}