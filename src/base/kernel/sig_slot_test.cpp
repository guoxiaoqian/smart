//#include "sig_slot_test.hpp"

//class A
//{
//public:
//    SLOTS void FuncOfA(int param,char param2)
//    {
//        printf("A::FuncOfA(%d) %c\n", param,param2);
//    }
//};


//class C
//{
//public:
//    void SetValue(int value)
//    {
//       emit ValueChanged(value,'q');
//    }

//public:
//    Signal<int,char> ValueChanged;

//};

//int main()
//{
//    A* pA = new A;
//    C* pC = new C;

//    connect(pC, ValueChanged, pA, &A::FuncOfA);

//    pC->SetValue(10);

//    delete pC;
//    delete pA;

//    system("pause");
//    return 0;
//}