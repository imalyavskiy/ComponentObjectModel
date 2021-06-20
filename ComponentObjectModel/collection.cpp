#include "common.h"
#include "unknown.h"
#include "first.h"
#include "second.h"
#include "collection.h"

namespace mycom
{

bool 
collection::create(uuid id, void** ppv, iunknown* outer /*= nullptr*/)
{
    *ppv = nullptr;
    collection* p = new collection(outer);
    if(p->queryinterface(id, ppv))
        return true;

    delete p;

    return false;
}

collection::collection(iunknown* outer, std::string name)
    : second(outer, name)
{
    items_.push_back(std::unique_ptr<second>(new second(static_cast<icollection*>(this))));
    items_.push_back(std::unique_ptr<second>(new second(static_cast<icollection*>(this))));
    items_.push_back(std::unique_ptr<second>(new second(static_cast<icollection*>(this))));
}

bool 
collection::queryinterface(uuid id, void** ppv)
{
    if(id == uuidof<icollection>::value())
    {
        *ppv = static_cast<icollection*>(this);
        addref();
        return true;
    }

    return second::queryinterface(id, ppv);
}

size_t 
collection::size() const
{
    return items_.size();
}

iunknown* 
collection::getitem(size_t index)
{
    if(0 > index  || index >= size() )
        return nullptr;

    isecond* p = items_[index].get();
    
    return static_cast<iunknown*>(p);
}
}