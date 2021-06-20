#include "common.h"
#include "unknown.h"
#include "first.h"
#include "second.h"

using namespace mycom;

int main()
{
    ptr<i_unknown> pIUnknown;
    ptr<i_first> pIFirst;
    ptr<i_second> pISecond;

    if(!mycom::unknown::CreateInstance(uuid_of_type<i_unknown>::value(), (void**)pIUnknown)) {
        std::cout << "failed to instantiate mycom::unknown\n";
    }
    pIUnknown.reset();

    if(!mycom::first::CreateInstance(uuid_of_type<i_first>::value(), (void**)pIFirst))
    {
        std::cout << "failed to instantiate mycom::first\n";
    }
    pIFirst->queryinterface(uuid_of_type<i_unknown>::value(), (void**)pIUnknown);
    pIUnknown.reset();
    pIFirst.reset();

    if(!mycom::second::CreateInstance(uuid_of_type<i_second>::value(), (void**)pISecond))
    {
        std::cout << "failed to instantiate mycom::second\n";
    }

    pIUnknown = interface_cast<i_unknown>(pISecond);
    pIFirst = interface_cast<i_first>(pISecond);

    pISecond.reset();
    pIFirst.reset();
    pIUnknown.reset();
} 
