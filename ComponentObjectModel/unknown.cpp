#include "unknown.h"
namespace mycom
{

bool unknown::CreateInstance(IID iid, void** ppv)
{
    *ppv = nullptr;
    unknown* p = new unknown();
    if(p->queryinterface(iid, ppv))
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

bool unknown::queryinterface(IID iid, void** ppv)
{
    if(iid == iid_i_unknown)
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