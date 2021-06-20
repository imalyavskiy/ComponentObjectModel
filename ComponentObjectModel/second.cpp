#include "common.h"
#include "unknown.h"
#include "first.h"
#include "second.h"

namespace mycom
{
second::second(iunknown* outer, std::string name)
    : first(outer, name)
{

}

bool second::queryinterface(uuid id, void** ppv)
{
    *ppv = nullptr;
    if(id == uuidof<isecond>::value())
    {
        *ppv = static_cast<isecond*>(this);
        addref();
        return true;
    }

    return first::queryinterface(id, ppv);
}

bool second::create(uuid id, void** ppv, iunknown* outer)
{
    *ppv = nullptr;
    
    auto p = new second(outer);
    if(p->queryinterface(id, ppv))
        return true;

    delete p;

    return false;
}

void second::boo()
{
    std::cout << "second::boo()\n";
}
}