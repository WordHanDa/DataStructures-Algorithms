#include <iostream>
#include <string>
using namespace std;

int main() {
    int x;
    cout << "輸入X筆名字：";
    cin >> x;
    int row=x;
    int col=2;
    size_t maxNameLength=0;
    string** A=new string*[row];
    for (int i=0; i<row; i++){
        A[i]=new string[col];
    }
    for (int i=0; i<row; i++){
        cout << "輸入名字:";
        for (int j=0; j<col; j++){
            cin >> A[i][j];
        }
        long int nameLength=A[i][0].length();
        maxNameLength=(nameLength>maxNameLength)?nameLength:maxNameLength;
    }
    for (int i=0; i<row; i++){
        long int spacesToAdd=maxNameLength-A[i][0].length();
        for (int j=0; j<spacesToAdd; j++){
            cout << " ";
        }
        cout << A[i][0] << " " << A[i][1] << endl;
    }
    for (int i=0; i<row; i++){
        delete[] A[i];
    }
    delete[] A;
    return 0;
}
