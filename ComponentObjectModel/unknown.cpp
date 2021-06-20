#include "common.h"
#include "unknown.h"

namespace mycom
{

bool unknown::create(uuid id, void** ppv, iunknown* outer)
{
    *ppv = nullptr;
    unknown* p = new unknown();
    if(p->queryinterface(id, ppv))
        return true;

    delete p;

    return false;
}

unknown::unknown(iunknown* outer, std::string name)
    : outer_(outer)
    , name_(name)
{
    std::cout << "ctor(" << name_ << ")\n";
}

unknown::~unknown()
{
    std::cout << "dtor(" << name_ << ")\n";
}

bool unknown::queryinterface(uuid iid, void** ppv)
{
    if(iid == uuidof<iunknown>::value())
    {
        *ppv = static_cast<iunknown*>(this);
        addref();
        return true;
    }
    return false;
}

int32_t unknown::addref()
{
    counter_++;

    if(outer_)
    {
        return outer_->addref();
    }
    return counter_;
}

int32_t unknown::release()
{
    int32_t counter = --counter_;
    assert(counter >= 0);

    if(outer_)
        return outer_->release();
    else if(counter == 0)
        delete this;

    return counter;
}
}