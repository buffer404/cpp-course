#include <CustomClass.hpp>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <list>
#include <vector>

bool
between_inc(unsigned num, unsigned lower, unsigned upper) {
    return (num <= upper) & (num >= lower);
}

std::vector<CustomClass>
step1(int size) {
    return std::vector<CustomClass>(size);
}

std::vector<CustomClass>
step2(std::vector<CustomClass> origin, unsigned size, unsigned startPos, unsigned endPos) {
    return std::vector<CustomClass>(origin.begin() + startPos, origin.begin() + endPos);
}

std::list<CustomClass>
step3(unsigned n, std::vector<CustomClass>& v) {
    std::sort(v.begin(), v.end());
    std::list<CustomClass> wholeList(v.begin(), v.end());
    auto it = wholeList.begin();
    std::advance(it, n);
    return std::list<CustomClass>(wholeList.begin(), it);
}

std::list<CustomClass>
step4(unsigned n, std::vector<CustomClass>& v) {
    std::sort(v.begin(), v.end());
    std::list<CustomClass> wholeList(v.begin(), v.end());
    auto it = wholeList.end();
    std::advance(it, -n);
    return std::list<CustomClass>(wholeList.end(), it);
}

void
step5(std::vector<CustomClass>& v1, std::vector<CustomClass>& v2, unsigned n1, unsigned n2) {
    v1.erase(v1.begin(), v1.begin() + n1);
    v2.erase(v2.begin(), v2.begin() + n2);
}

void
add(int& sum, int addr) {
    sum += addr;
    return;
}

bool
is_even(CustomClass n) {
    return n.getSize() % 2 == 0;
}

void
step7(std::vector<CustomClass>& v) {
    std::vector<CustomClass> evened_vec;
    std::copy_if(v.begin(), v.end(), evened_vec.begin(), is_even);
    v = evened_vec;
}

std::vector<CustomClass>
step8(std::vector<CustomClass>& v1, std::vector<CustomClass>& v2) {
    std::vector<CustomClass> v3;

    v3.reserve(v1.size() + v2.size());
    v3.insert(v3.end(), v1.begin(), v1.end());
    v3.insert(v3.end(), v2.begin(), v2.end());
    return v3;
}

std::list<std::pair<CustomClass, CustomClass>>
step9(std::list<CustomClass> l1, std::list<CustomClass> l2) {
    std::list<std::pair<CustomClass, CustomClass>> l3;
    if (l1.size() >= l2.size()) {
        auto it = l1.end();
        std::advance(it, l1.size() - l2.size());
        l1.erase(it, l1.end()); // удаляем последние n элементов
    } else {
        auto it = l2.end();
        std::advance(it, l2.size() - l1.size());
        l2.erase(it, l2.end()); // удаляем последние n элементов
    }
    std::transform(l1.begin(), l1.end(), l2.begin(), std::back_inserter(l3),
                   [](const CustomClass& el1, const CustomClass& el2) { return std::make_pair(el1, el2); });
    return l3;
}

std::vector<std::pair<CustomClass, CustomClass>>
step10(std::vector<CustomClass> v1, std::vector<CustomClass> v2) {
    std::vector<std::pair<CustomClass, CustomClass>> v3;
    if (v1.size() >= v2.size()) {
        std::transform(v1.begin(), v1.end(), v2.begin(), std::back_inserter(v3),
                       [](const CustomClass& el1, const CustomClass& el2) { return std::make_pair(el1, el2); });
    } else {
        std::transform(v2.begin(), v2.end(), v1.begin(), std::back_inserter(v3),
                       [](const CustomClass& el1, const CustomClass& el2) { return std::make_pair(el1, el2); });
    }
    return v3;
}

int
main() {
    unsigned size;
    char sizeChar[4];
    std::vector<CustomClass> v1;
    std::vector<CustomClass> v2, v3;
    std::vector<std::pair<CustomClass, CustomClass>> v4;
    std::list<CustomClass> list1, list2;
    std::list<std::pair<CustomClass, CustomClass>> list3;
    unsigned n1, n2;

    n1 = 40;
    n2 = 30;
    size = 600;

    v1 = step1(size);
    v2 = step2(v2, size, size - 200, size);
    list1 = step3(n1, v1);
    list2 = step4(n2, v2);
    step5(v1, v2, n1,
          n2); // шаг 6 уже выполнен, вектора отсортированы, а значит слева от среднего значения только больше среднего
    step7(v2);
    v3 = step8(v1, v2);
    list3 = step9(list1, list2);
    v4 = step10(v1, v2);

    return 0;
}