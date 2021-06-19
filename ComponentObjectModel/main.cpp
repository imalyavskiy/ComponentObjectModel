#include "second.h"

int main()
{
    mycom::ptr<mycom::i_unknown> pIUnknown;
    mycom::ptr<mycom::i_first> pIFirst;
    mycom::ptr<mycom::i_second> pISecond;

    if(!mycom::unknown::CreateInstance(mycom::iid_i_unknown, (void**)pIUnknown)) {
        std::cout << "failed to instantiate mycom::unknown\n";
    }
    pIUnknown.reset();

    if(!mycom::first::CreateInstance(mycom::iid_i_first, (void**)pIFirst))
    {
        std::cout << "failed to instantiate mycom::first\n";
    }
    pIFirst->queryinterface(mycom::iid_i_unknown, (void**)pIUnknown);
    pIUnknown.reset();
    pIFirst.reset();

    if(!mycom::second::CreateInstance(mycom::iid_i_second, (void**)pISecond))
    {
        std::cout << "failed to instantiate mycom::second\n";
    }
    pISecond->queryinterface(mycom::iid_i_unknown, (void**)pIUnknown);
    pISecond->queryinterface(mycom::iid_i_first, (void**)pIFirst);

    pISecond.reset();
    pIFirst.reset();
    pIUnknown.reset();
}
