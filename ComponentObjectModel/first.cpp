#include "first.h"
namespace mycom
{
first::first(std::string name)
    : unknown(name)
{

}

bool first::queryinterface(IID iid, void** ppv)
{
    *ppv = nullptr;
    if(iid == iid_i_first)
    {
        *ppv = static_cast<i_first*>(this);
        addref();
        return true;
    }

    return unknown::queryinterface(iid, ppv);
}

bool first::CreateInstance(IID iid, void** ppv)
{
    *ppv = nullptr;
    first* p = new first();
    if(p->queryinterface(iid, ppv))
        return true;

    delete p;

    return false;
}

void first::foo()
{
    std::cout << "first::foo()\n";
}

}