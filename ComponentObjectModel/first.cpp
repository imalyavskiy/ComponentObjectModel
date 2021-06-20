#include "common.h"
#include "unknown.h"
#include "first.h"

namespace mycom
{
first::first(iunknown* outer, std::string name)
    : unknown(outer, name)
{

}

bool first::queryinterface(uuid id, void** ppv)
{
    *ppv = nullptr;
    if(id == uuidof<ifirst>::value())
    {
        *ppv = static_cast<ifirst*>(this);
        addref();
        return true;
    }

    return unknown::queryinterface(id, ppv);
}

bool first::create(uuid id, void** ppv, iunknown* outer)
{
    *ppv = nullptr;
    first* p = new first(outer);
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