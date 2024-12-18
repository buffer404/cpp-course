#include <cstdio>
#include <vector>

/*
  Класс, хранящий номер и соответствующий этому номеру символ char
*/
class CustomClass {
  private:
    int size = 0;
    int* mas;

  public:
    CustomClass();                                    // implicit cinstructor
    CustomClass(int param);                           // expliit constructor 1
    CustomClass(int param, int* data);                // expliit constructor 1
    CustomClass(const CustomClass& obj);              // copy constructor
    CustomClass(CustomClass&& moved);                 // move constructor
    CustomClass& operator=(const CustomClass& other); // assign overload
    CustomClass& operator=(CustomClass&& moved);      // move assign operator
    ~CustomClass();

    int getSize();
    int* getArr();
};
