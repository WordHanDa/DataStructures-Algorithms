//
//  main.cpp
//  HW04_B1129012
//
//  Created by macbook pro on 2023/11/25.
//

#include <iostream>

class Node {
    public:
    int coefficient;
    int exponent;
    Node* next;
    Node(int coef, int exp):coefficient(coef), exponent(exp), next(nullptr){}
};

class Polynomial {
    public:
    Node* headNode;
    Polynomial():headNode(nullptr){}
    
    void insert_term(int coef, int exp) {
        Node* newNode = new Node(coef, exp);
        if(headNode==nullptr){
            headNode=newNode;
        }else{
            Node* currentNode = headNode;
            Node* prevNode=nullptr;
            while (currentNode!=nullptr&&exp<currentNode->exponent){
                prevNode=currentNode;
                currentNode=currentNode->next;
            }
            if (currentNode!=nullptr&&exp==currentNode->exponent){
                currentNode->coefficient+=coef;
                delete newNode;
            }else{
                newNode->next=currentNode;
                (prevNode==nullptr)?headNode=newNode:prevNode->next=newNode;
            }
        }
    }
    Polynomial multiply(Polynomial other) const {
        Polynomial result;
        Node* current_a=headNode;
        while (current_a!=nullptr) {
            Node* current_b=other.headNode;
            while (current_b!=nullptr) {
                int coef=current_a->coefficient*current_b->coefficient;
                int exp=current_a->exponent+current_b->exponent;
                result.insert_term(coef, exp);
                current_b=current_b->next;
            }
            current_a=current_a->next;
        }
        return result;
    }
    void print(){
        Node* currentNode=headNode;
        while (currentNode!=nullptr) {
            if (currentNode->coefficient!=0) {
                std::cout<<currentNode->coefficient;
                if (currentNode->exponent!=0) {
                    std::cout<<"x^"<<currentNode->exponent;
                }
                if(currentNode->next!=nullptr&&currentNode->next->coefficient!=0){
                    std::cout<<" + ";
                }
            }
            currentNode=currentNode->next;
        }
        std::cout<<std::endl;
    }
};

void inputPolynomial(Polynomial& poly, const std::string polynomialName) {
    int terms;
    std::cout<<"Enter the number of terms for the "<<polynomialName<<" polynomial: ";
    std::cin>>terms;
    for (int i = 0; i < terms; ++i) {
        int coef, exp;
        std::cout<<"Enter coefficient and exponent for term "<<i+1<<" of the "<<polynomialName<<" polynomial: ";
        std::cin>>coef>>exp;
        poly.insert_term(coef, exp);
    }
}

int main(int argc, const char * argv[]) {
    Polynomial poly_a,poly_b;
    inputPolynomial(poly_a, "first");
    inputPolynomial(poly_b, "second");
    std::cout << "Result of multiplication: ";
    poly_a.multiply(poly_b).print();
    return 0;
}
//http://alrightchiu.github.io/SecondRound/linked-list-xin-zeng-zi-liao-shan-chu-zi-liao-fan-zhuan.html
