#include <iostream>
#include <string>
using namespace std;

void indent(){
    
}

int main() {
    int x;
    cout << "輸入X筆名字：";
    cin >> x;
    
    int row = x;
    int col = 2;

    string** A = new string* [row];
    for(int i=0; i<row; i++){
        A[i]=new string[col];
    }

    for(int i=0; i<row; i++) {
        cout << "輸入名字:";
        for (int j=0; j<col; j++) {
            cin >> A[i][j];
        }
    }
    
    
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    for (int i=0; i<row; i++) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}
