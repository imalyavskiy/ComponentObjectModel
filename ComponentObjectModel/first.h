#ifndef __FIRST_H__
#define __FIRST_H__

namespace mycom
{
class first
    : public unknown
    , public i_first
{
public:
    static bool CreateInstance(uuid iid, void** ppv);

    DECLARE_ADDREF(unknown)
    DECLARE_RELEASE(unknown)

protected:
    first(std::string name = "first");

    bool queryinterface(uuid iid, void** ppv) override;
    
    void foo() override;
};
}

#endif // __FIRST_H__