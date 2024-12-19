#include <SparceMatrix.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>

long
NonEmptyVector::operator[](std::size_t index) {
    if (index > size) {
        throw std::invalid_argument("given value exceedes size of a vector");
        return 0;
    }
    for (auto it : contains) {
        if (it.pos == index) {
            return it.value + *currentZero;
        }
    }
    return 0;
}

NonEmptyVector::NonEmptyVector() : size(0), pos(0), currentZero(0) {}

NonEmptyVector::NonEmptyVector(std::size_t size, std::size_t pos, long* currentZeroPtr = 0)
    : size(size), pos(pos), currentZero(currentZeroPtr) {
    if (pos > size) {
        throw std::invalid_argument("given value exceedes size of a vector");
    }
}

std::size_t
NonEmptyVector::getPos() {
    return pos;
}

std::vector<NonEmptyValue>
NonEmptyVector::getValue() {
    return contains;
}

SMatrix::SMatrix(unsigned width, unsigned height = 1) : width(width), height(height) {}

NonEmptyVector&
SMatrix::operator[](std::size_t index) {
    if (index > width) {
        throw std::invalid_argument("given value exceedes size of a matrix");
    }
    for (int i = 0; i < contains.size(); ++i) {
        if (contains[i].getPos() == index) {
            return contains[i];
        }
    }
    zeroVector = NonEmptyVector(height, index, &currentZero);
    return zeroVector;
}

void
SMatrix::setValue(long value, std::size_t indexW, std::size_t indexH = 0) {
    if ((indexH > height) | (indexW > width)) {
        throw std::invalid_argument("given value exceedes size of a matrix");
        return;
    }
    if (value == currentZero) {
        return;
    }
    if ((*this)[indexW].assigned) {
    } else {
        NonEmptyVector push(height, indexW);
        push.assigned = true;
        push.currentZero = &currentZero;
        contains.push_back(push);
    }
    (*this)[indexW].setValue(value, indexH);
}

void
NonEmptyVector::setValue(long value, std::size_t indexH) {
    if ((assigned) & ((*this)[indexH] == *currentZero)) {
        NonEmptyValue push;
        push.value = value;
        push.pos = indexH;
        push.assigned = true;
        contains.push_back(push);
    } else if ((assigned)) {
        for (auto it = contains.begin(); it < contains.end(); ++it) {
            if (it->pos == indexH) {
                it->value = value;
            }
        }
    }
}

SMatrix&
SMatrix::operator=(const SMatrix& other) {
    if (this == &other) {
        return *this;
    }
    width = other.width;
    height = other.height;
    contains = other.contains;
    currentZero = other.currentZero;
    return *this;
}

SMatrix&
SMatrix::operator+=(const int scalar) {
    currentZero += scalar;
    return *this;
}

SMatrix&
SMatrix::operator-=(const int scalar) {
    currentZero -= scalar;
    return *this;
}

SMatrix&
SMatrix::operator*=(const int scalar) {
    currentZero *= scalar;
    for (int i = 0; i < contains.size(); ++i) {
        for (int j = 0; j < (*this).contains[i].contains.size(); ++j) {
            (*this).contains[i].contains[j].value *= scalar;
        }
    }
    return *this;
}

SMatrix&
SMatrix::powElementwise(float power) {
    unsigned currentZeroPowered = pow(currentZero, power);
    for (int i = 0; i < contains.size(); ++i) {
        for (int j = 0; j < (*this).contains[i].contains.size(); ++j) {
            (*this).contains[i].contains[j].value = pow((*this).contains[i].contains[j].value + currentZero, power)
                                                    - currentZeroPowered;
        }
    }
    currentZero = currentZeroPowered;
    return *this;
}

SMatrix&
SMatrix::operator/=(const int scalar) {
    currentZero /= scalar;
    for (int i = 0; i < contains.size(); ++i) {
        for (int j = 0; j < (*this).contains[i].contains.size(); ++j) {
            (*this).contains[i].contains[j].value /= scalar;
        }
    }
    return *this;
}

SMatrix
SMatrix::operator+(const int scalar) {
    SMatrix ret(*this);
    ret += scalar;
    return ret;
}

SMatrix
SMatrix::operator-(const int scalar) {
    SMatrix ret(*this);
    ret -= scalar;
    return ret;
}

SMatrix
SMatrix::operator*(const int scalar) {
    SMatrix ret(*this);
    ret *= scalar;
    return ret;
}

SMatrix
SMatrix::operator/(const int scalar) {
    SMatrix ret(*this);
    ret += scalar;
    return ret;
}

long
NonEmptyVector::atClear(size_t pos) {
    for (int i = 0; i < pos; ++i) {
        if (contains[i].pos == pos) {
            return contains[i].value;
        }
    }
    return 0.;
}

SMatrix&
SMatrix::operator+=(const SMatrix& other) {
    if ((height != other.height) & (width != other.width)) {
        throw std::invalid_argument("matrix sizes should be equal");
    }
    currentZero += other.currentZero;
    for (auto it : other.contains) {
        for (auto itElem : it.contains) {
            setValue(itElem.value + (*this)[it.pos].atClear(itElem.pos), it.pos, itElem.pos);
        }
    }
    return *this;
}

SMatrix
operator+(SMatrix lhs, const SMatrix& rhs) {
    lhs += rhs;
    return lhs;
}

SMatrix&
SMatrix::operator*=(SMatrix& other) {
    if ((width != other.height)) {
        throw std::invalid_argument("matrix sizes should be coherent");
    }
    SMatrix newMatrix(other.width, height);
    for (int i = 0; i < other.width; ++i) {
        for (int j = 0; j < height; ++j) {
            long res = 0;
            for (int k = 0; k < width; ++k) {
                res += (*this)[k][j] * other[i][k];
            }
            newMatrix.setValue(res, i, j);
        }
    }
    width = newMatrix.width;
    height = newMatrix.height;
    contains = newMatrix.contains;
    currentZero = newMatrix.currentZero;
    return *this;
}

SMatrix::SMatrix(const SMatrix& other) {
    currentZero = other.currentZero;
    width = other.width;
    height = other.height;
    contains = other.contains;
}

SMatrix
SMatrix::transpose() {
    SMatrix newMatrix(height, width);
    for (auto it : contains) {
        for (auto itElem : it.contains) {
            newMatrix.setValue(itElem.value, itElem.pos, it.getPos());
        }
    }
    return newMatrix;
}

std::ostream&
operator<<(std::ostream& os, SMatrix& obj) {
    for (int i = 0; i < obj.width; ++i) {
        for (int j = 0; j < obj.height; ++j) {
            os << obj[j][i] << "\t";
        }
        os << "\n";
    }
    return os;
}

long
SMatrix::getDeterminant() { // todo
    if (height != width) {
        throw std::invalid_argument("matrix should be squared");
    }
    if (height == 1) {
        return (*this)[0][0];
    }
    if (height == 2) {
        return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
    } else {
        std::vector<SMatrix> tmpV;
        int det = 0;
        for (int i = 0; i < width; ++i) {
            tmpV.push_back(SMatrix(width - 1, width - 1)); // create n-1 matrices
        }
        for (int i = 0; i < width; ++i) { // fill matrices
            for (int x = 0; x < width - 1; ++x) {
                int idx = (x < i) ? x : x + 1;
                for (int y = 1; y < width; ++y) {
                    tmpV[i].setValue((*this)[idx][y], x, y - 1);
                }
            }
        }
        for (int i = 0; i < width; ++i) {
            det += (*this)[i][0] * pow(-1, i % 2) * tmpV[i].getDeterminant();
        }
        return det;
    }
}

SMatrix
SMatrix::getBackwardsMatrix() {
    long det = getDeterminant();
    SMatrix newMat(width, height);
    SMatrix tmpMat(width - 1, height - 1);
    if (det = 0) {
        throw std::invalid_argument("this matrix has no backwards matrix");
    }
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < width; ++y) {
            for (int xin = 0; xin < width - 1; ++xin) {
                int xBaseIndex = xin < x ? xin : xin + 1;
                for (int yin = 0; yin < width - 1; ++yin) {
                    int yBaseIndex = yin < y ? yin : yin + 1;
                    tmpMat.setValue((*this)[xBaseIndex][yBaseIndex], xin, yin);
                }
            }
            det = tmpMat.getDeterminant() * pow(-1, x % 2) * pow(-1, y % 2);
            newMat.setValue(det, x, y);
        }
    }

    return newMat.transpose();
}

SMatrix
pow(SMatrix base, unsigned power) {
    if (base.height != base.width) {
        throw std::invalid_argument("matrix should be square to be powerable");
    }
    SMatrix newMat(base);
    for (int _ = 0; _ < power; _++) {
        newMat *= base;
    }
    return newMat;
}

SMatrix
pow(SMatrix base, float power) {
    return pow(base, unsigned(power));
}
