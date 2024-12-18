#include <CustomClass.hpp>
#include <cmath>
#include <list>
#include <vector>

int
compareVectors(CustomClass& comp1, CustomClass& comp2) {
    if (comp1.getSize() != comp2.getSize()) {
        return 0;
    } else {
        int* mas1 = comp1.getArr();
        int* mas2 = comp2.getArr();
        for (int i = 0; i < comp1.getSize(); ++i) {
            if (mas1[i] != mas2[i]) {
                return 0;
            }
        }
        delete[] mas1, mas2;
    }
    return 1;
}

void
acceptObject(CustomClass a) {
    printf("\tfunc got class object\n");
}

void
acceptRefObject(CustomClass& a) {
    printf("\tfunc got class object by ref\n");
}

CustomClass
getObject() {
    printf("\tfunc returns class object\n");
    return CustomClass(10);
}

CustomClass&
getRefObject() {
    printf("\tfunc returns class object\n");
    static CustomClass a(10);
    return a;
}

int
main() {
    printf("\ntest 1:\n");
    {
        printf("\nstatic creation:\n");
        CustomClass a;
        CustomClass m[2];
        CustomClass b(10);
        int* mas = new int[10];
        CustomClass c(10, mas);
        a = CustomClass(b);
        a = c;
    }
    {
        printf("\ndynamic creation:\n");
        CustomClass* a = new CustomClass;
        CustomClass* b = new CustomClass[10];
        delete a;
        delete[] b;
    }
    {
        printf("\ncomparation:\n");
        int mas[10];
        for (int i = 0; i < 10; ++i) {
            mas[i] = log(i);
        }
        CustomClass a(10, mas);
        CustomClass b(a);
        if (compareVectors(a, b)) {
            printf("vectors are equal\n");
        } else {
            printf("vectors are inequal\n");
        }
    }
    printf("\ntest 2:\n");
    {
        printf("\nfunction exchange:\n");
        CustomClass a;
        acceptObject(a);
        acceptRefObject(a);
        getObject();
        getRefObject();
    }

    printf("\ntest 3:\n");
    {
        printf("\nvector and list creation:\n");
        std::vector<CustomClass>(10);
        std::list<CustomClass>(5);
    }
    return 0;
}