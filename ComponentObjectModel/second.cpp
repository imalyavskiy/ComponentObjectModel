#include "second.h"
namespace mycom
{
second::second(std::string name)
    : first(name)
{

}

bool second::queryinterface(IID iid, void** ppv)
{
    *ppv = nullptr;
    if(iid == iid_i_second)
    {
        *ppv = static_cast<i_second*>(this);
        addref();
        return true;
    }

    return first::queryinterface(iid, ppv);
}

bool second::CreateInstance(IID iid, void** ppv)
{
    *ppv = nullptr;
    
    auto p = new second();
    if(p->queryinterface(iid, ppv))
        return true;

    delete p;

    return false;
}

void second::boo()
{
    std::cout << "second::boo()\n";
}
}