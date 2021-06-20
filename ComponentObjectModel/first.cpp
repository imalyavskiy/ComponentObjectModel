#include "common.h"
#include "unknown.h"
#include "first.h"

namespace mycom
{
first::first(std::string name)
    : unknown(name)
{

}

bool first::queryinterface(uuid id, void** ppv)
{
    *ppv = nullptr;
    if(id == uuid_of_type<i_first>::value())
    {
        *ppv = static_cast<i_first*>(this);
        addref();
        return true;
    }

    return unknown::queryinterface(id, ppv);
}

bool first::CreateInstance(uuid id, void** ppv)
{
    *ppv = nullptr;
    first* p = new first();
    if(p->queryinterface(id, ppv))
        return true;

    delete p;

    return false;
}

void first::foo()
{
    std::cout << "first::foo()\n";
}

}