#include "common.h"
#include "unknown.h"

namespace mycom
{

bool unknown::CreateInstance(uuid id, void** ppv)
{
    *ppv = nullptr;
    unknown* p = new unknown();
    if(p->queryinterface(id, ppv))
        return true;

    delete p;

    return false;
}

unknown::unknown(std::string name)
    : name_(name)
{
    std::cout << "ctor(" << name_ << ")\n";
}

unknown::~unknown()
{
    std::cout << "dtor(" << name_ << ")\n";
}

bool unknown::queryinterface(uuid iid, void** ppv)
{
    if(iid == uuid_of_type<i_unknown>::value())
    {
        *ppv = static_cast<i_unknown*>(this);
        addref();
        return true;
    }
    return false;
}

int32_t unknown::addref()
{
    return ++counter_;
}

int32_t unknown::release()
{
    int32_t counter = --counter_;
    assert(counter >= 0);

    if(counter == 0)
    {
        delete this;
    }

    return counter;
}
}