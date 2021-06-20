#include "common.h"
#include "unknown.h"
#include "first.h"
#include "second.h"

namespace mycom
{
second::second(std::string name)
    : first(name)
{

}

bool second::queryinterface(uuid id, void** ppv)
{
    *ppv = nullptr;
    if(id == uuid_of_type<i_second>::value())
    {
        *ppv = static_cast<i_second*>(this);
        addref();
        return true;
    }

    return first::queryinterface(id, ppv);
}

bool second::CreateInstance(uuid id, void** ppv)
{
    *ppv = nullptr;
    
    auto p = new second();
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