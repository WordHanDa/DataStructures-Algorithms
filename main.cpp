#include <iostream>

using namespace std;
class inputs{
    public:
    int x, y;
    string yChar;
    void userinputs(){
        cout << "輸入X個字串，字串不可超過Y個字(X,Y):";
        cin >> x >> y;
        cout << "輸入字串：";
        cin >> yChar;
        while(yChar.length() > y){
            cin.clear();
            cout << "字串長度超過Y個字，重新輸入"<< endl;
            cin >> yChar;
        }
    }
    int **matrix = new int*[x];
    for (int i = 0; i < x; ++i) {
        matrix[i] = new int[y];
    }
};
class sort:inputs{
    void bubbleSort(int arr[], int n){
        if (n == 1){
            return;
        }
        for (int i=0; i<n-1; i++){
            if (arr[i] > arr[i+1]){
                swap(arr[i], arr[i+1]);
            }
        }
        bubbleSort(arr, n-1);
    }
    void swap(int &a, int &b){
        int temp = a;
        a = b;
        b = temp;
    }
};

int main()
{
    
    return 0;
}