#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include "pch.h"

namespace mycom
{
static IID iid_i_unknown{ 0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
struct i_unknown
{
    virtual bool queryinterface(IID, void** ppv) = 0;
    virtual int32_t addref() = 0;
    virtual int32_t release() = 0;
};

static IID iid_i_first{ 0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 } };
struct i_first : i_unknown
{
    virtual void foo() = 0;
};

static IID iid_i_second{ 0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 } };
struct i_second: i_unknown
{
    virtual void boo() = 0;
};

}
#endif // __INTERFACES_H__
