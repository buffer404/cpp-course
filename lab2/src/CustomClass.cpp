#include <CustomClass.hpp>

CustomClass::CustomClass() : size(0), mas(0) { printf("\tDefault constructor\n"); }

CustomClass::CustomClass(int param) : size(param) {
    mas = new int[size];
    printf("\tExplicit constructor\n");
}

CustomClass::CustomClass(int param, int* data) : size(param) {
    mas = new int[size];
    for (unsigned i{}; i < size; i++) {
        mas[i] = data[i];
    }
    printf("\tExplicit constructor\n");
}

CustomClass::~CustomClass() {
    printf("\tDestructor\n");
    delete[] mas;
}

CustomClass a;

CustomClass::CustomClass(const CustomClass& obj) : CustomClass(obj.size, obj.mas) { printf("\tCopy constructor\n"); }

CustomClass&
CustomClass::operator=(const CustomClass& other) {
    printf("\tCopy operator\n");
    if (this == &other) {
        return *this;
    }
    delete[] mas;
    size = other.size;
    mas = new int[size];
    for (unsigned i{}; i < size; i++) {
        mas[i] = other.mas[i];
    }
    return *this;
}

CustomClass::CustomClass(CustomClass&& moved) {
    printf("\tmove constructor\n");
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