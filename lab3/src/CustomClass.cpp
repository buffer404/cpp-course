#include <CustomClass.hpp>
#include <random>

CustomClass::CustomClass() {
    //printf("\tDefault constructor\n");

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist50(1, 50); // distribution in range [1, 50]

    size = dist50(rng);
    mas = new int[size];
}

CustomClass::CustomClass(int param) : size(param) {
    mas = new int[size];
    //printf("\tExplicit constructor\n");
}

CustomClass::CustomClass(int param, int* data) : size(param) {
    mas = new int[size];
    for (unsigned i{}; i < size; i++) {
        mas[i] = data[i];
    }
    //printf("\tExplicit constructor\n");
}

CustomClass::~CustomClass() {
    //printf("\tDestructor\n");
    delete[] mas;
}

CustomClass a;

CustomClass::CustomClass(const CustomClass& obj) : CustomClass(obj.size, obj.mas) {} //printf("\tCopy constructor\n"); }

CustomClass&
CustomClass::operator=(const CustomClass& other) {
    //printf("\tCopy operator\n");
    if (this == &other) {
        return *this;
    }
    if (this != 0) {
        delete[] mas;
    }
    size = other.size;
    mas = new int[size];
    for (unsigned i{}; i < size; i++) {
        mas[i] = other.mas[i];
    }
    return *this;
}

CustomClass::CustomClass(CustomClass&& moved) {
    //printf("\tmove constructor\n");
    if (this != &moved) {
        size = moved.size;
        mas = moved.mas;
        moved.mas = 0;
        moved.size = 0;
    }
}

CustomClass&
CustomClass::operator=(CustomClass&& moved) {
    if (this != &moved) {
        size = moved.size;
        mas = moved.mas;
        moved.mas = 0;
        moved.size = 0;
    }
    return *this;
}

int
CustomClass::getSize() {
    return size;
}

int*
CustomClass::getArr() {
    int* ret = new int[size];
    for (int i = 0; i < size; ++i) {
        ret[i] = mas[i];
    }
    return ret;
}

bool
CustomClass::operator<(const CustomClass& r) {
    return size < r.size;
}