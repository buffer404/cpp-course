#include <algorithm>
#include <fstream>
#include <vector>

#include "iostream"
#include "string"
using namespace std;

int main() {
    string type1, type2;
    string operation;
    
    ifstream legit_ops("./data/legit_ops.txt");
    ifstream test_ops("./data/test_ops.txt");
    vector<string> legitOpsV;

    if (!legit_ops || !test_ops) {
        cout << "Some files have not been found!\n";
        return 0;
    }

    cout << "Legitimate operations (see legit_ops file):\n";
    while (getline(legit_ops, operation)) {
        cout << operation << endl;
        legitOpsV.push_back(operation); /* Write legit operations vector */
    }

    cout << "Enter the first data type > ";
    cin >> type1;

    cout << "Enter the second data type > ";
    cin >> type2;
    cout << type1 << ' ' << type2 << endl;
    ofstream fout("src/func.cpp");
    string fInput =
        "#include <iostream>\n"
        "#include <typeinfo>\n"
        "using namespace std;\n"
        "int f() {\n"
        "\t" +
        type1 +
        " var1 = 1;\n"
        "\t" +
        type2 + " var2 {3};\n";
    while (getline(test_ops, operation)) {
        for (int i = 0; i < legitOpsV.size(); ++i) {
            if (legitOpsV[i] == operation) {
                operation.erase(
                    remove(operation.begin(), operation.end(), '\r'),
                    operation.cend());
                fInput +=
                    "\tcout << typeid(var1).name() << \'(\' << var1 << \") \" "
                    "<< \"" +
                    operation +
                    "\" << \' \' << typeid(var2).name() << \'(\' << var2 << "
                    "\") = \" << typeid(var1 " +
                    operation + "var2).name() << \'(\' << (var1 " + operation +
                    " var2) << \')\' << endl;\n";
                break;
            }
            if (i == (legitOpsV.size() - 1)) {
                operation.erase(
                    remove(operation.begin(), operation.end(), '\r'),
                    operation.cend());
                cout << "Opertaion " << operation << " dismissed\n";
            }
        }
    }

    fInput +=
        "\treturn 0;\n"
        "}\n";

    fout << fInput;
    fout.close();
    return 0;
}
