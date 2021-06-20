#ifndef __FIRST_H__
#define __FIRST_H__

namespace mycom
{
class first
    : public unknown
    , public ifirst
{
public:
    static bool create(uuid iid, void** ppv, iunknown* outer = nullptr);
    first(iunknown* outer = nullptr, std::string name = "first");

    DECLARE_ADDREF(unknown)
    DECLARE_RELEASE(unknown)

protected:
    bool queryinterface(uuid iid, void** ppv) override;
    
    void foo() override;
};
}

#endif // __FIRST_H__