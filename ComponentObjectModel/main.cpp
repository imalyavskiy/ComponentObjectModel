#include "common.h"
#include "unknown.h"
#include "first.h"
#include "second.h"
#include "collection.h"

using namespace mycom;

#define check_failure(_call_)       \
{                                   \
    auto result = _call_;           \
    if(0 > result)                  \
        return result;              \
}

int test_1()
{
    ptr<iunknown> pIUnknown;

    if(!mycom::unknown::create(uuidof<iunknown>::value(), pIUnknown))
    {
        std::cout << "failed to instantiate mycom::unknown\n";
        return -1;
    }

    // no need to call reset in this case because this pointer is smart.
    pIUnknown.reset();

    return 0;
}

int test_2()
{
    ptr<iunknown> pIUnknown;
    ptr<ifirst> pIFirst;

    if(!mycom::first::create(uuidof<ifirst>::value(), pIFirst))
    {
        std::cout << "failed to instantiate mycom::first\n";
        return -1;
    }
    pIFirst->queryinterface(uuidof<iunknown>::value(), pIUnknown);
    
    // no need to call reset in this case because this pointer is smart.
    pIUnknown.reset();
    pIFirst.reset();

    return 0;
}

int test_3()
{
    ptr<iunknown> pIUnknown;
    ptr<ifirst> pIFirst;
    ptr<isecond> pISecond;

    if(!mycom::second::create(uuidof<isecond>::value(), pISecond))
    {
        std::cout << "failed to instantiate mycom::second\n";
        return -1;
    }

    pIUnknown = icast<iunknown>(pISecond);
    pIFirst = icast<ifirst>(pISecond);

    return 0;
}

int test_4()
{
    ptr<icollection> pICollection;

    if(!mycom::collection::create(uuidof<icollection>::value(), pICollection))
    {
        std::cout << "failed to  instantiate mycom::collection\n";
        return -1;
    }
    
    std::list<ptr<iunknown>> items;
   
    size_t size = pICollection->size();
    
    for(size_t i = 0; i < size; ++i)
        items.push_back(ptr<iunknown>(pICollection->getitem(i)));

    pICollection.reset();

    while(!items.empty())
        items.pop_front();

    return 0;
}

int main()
{
    check_failure(test_1());
    check_failure(test_2());
    check_failure(test_3());
    check_failure(test_4());

    return 0;
} 
