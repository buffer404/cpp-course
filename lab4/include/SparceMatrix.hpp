#include <cstddef>
#include <ostream>
#include <vector>

struct NonEmptyValue {
  private:
    bool assigned = false;
    friend class NonEmptyVector;

  public:
    std::size_t pos;
    long value;
};

class NonEmptyVector {
    friend class SMatrix;

    std::size_t pos, size;
    bool assigned = false;
    std::vector<NonEmptyValue> contains;
    long* currentZero;
    long atClear(size_t pos);

  public:
    NonEmptyVector(std::size_t size, std::size_t pos, long* currentZeroPtr);
    NonEmptyVector();
    long operator[](std::size_t index);
    std::size_t getPos();
    std::vector<NonEmptyValue> getValue();
    void setValue(long value, std::size_t indexH);
};

class SMatrix {
    std::size_t width, height;
    std::vector<NonEmptyVector> contains;
    long currentZero = 0;
    NonEmptyVector zeroVector;

  public:
    SMatrix(unsigned width, unsigned height);
    NonEmptyVector& operator[](std::size_t index);
    void setValue(long value, std::size_t indexW, std::size_t indexH);
    SMatrix transpose();
    SMatrix& operator=(const SMatrix& other);
    SMatrix& operator+=(const SMatrix& other);
    SMatrix& operator+=(const int scalar);
    SMatrix& operator-=(const int scalar);
    SMatrix& operator*=(const int scalar);
    SMatrix& operator/=(const int scalar);
    SMatrix operator+(const int scalar);
    SMatrix operator-(const int scalar);
    SMatrix operator*(const int scalar);
    SMatrix operator/(const int scalar);
    SMatrix& powElementwise(float power);
    SMatrix& operator*=(SMatrix& other);
    SMatrix(const SMatrix& other);
    long getDeterminant();
    SMatrix getBackwardsMatrix();
    friend SMatrix pow(SMatrix base, unsigned power);
    friend SMatrix pow(SMatrix base, float power);
    friend SMatrix operator+(SMatrix lhs, const SMatrix& rhs);
    friend std::ostream& operator<<(std::ostream& os, SMatrix& obj);
};