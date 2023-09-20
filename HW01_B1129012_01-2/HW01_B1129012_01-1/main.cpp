
#include <iostream>
using namespace std;


void swap(string &a, string &b){
    string temp = a;
    a = b;
    b = temp;
}
void bubbleSort(string** arr, int n) {
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (int(arr[j][0][0])<int(arr[j+1][0][0])) {
                swap(*(arr+j), *(arr+j+1));
            }
        }
    }
}
int main() {
    int x, y;
    cout << "輸入X個字串，字串不可超過Y個字(X,Y):";
    cin >> x >> y;
    cin.ignore();
    int row = x;
    int col = 1;
    string **A = (string **) malloc(sizeof(string *) * row);
    for (int i = 0; i < row; i++) {
        A[i] = (string *) malloc(sizeof(string) * col);
    }
    for(int i=0; i<row; i++){
        cout << "輸入字串：";
        cin >> A[i][0];
        while (A[i][0].length()>y){
            cin.clear();
            cout << "字串長度超過" << y << "個字，重新輸入" << endl;
            cin >> A[i][0];
        }
    }
    bubbleSort(A, row);
    for (int i=0; i<row; i++){
        cout << A[i][0] << " " << endl;
    }
    for (int i = 0; i < 3; i++) {
        free(A[i]);
    }
    free(A);
    return 0;
}
