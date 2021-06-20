#ifndef __SECOND_H__
#define __SECOND_H__

namespace mycom
{
class second
    : public first
    , public i_second
{
public:
    static bool CreateInstance(uuid iid, void** ppv);

    DECLARE_ADDREF(unknown)
    DECLARE_RELEASE(unknown)

protected:
    second(std::string name = "second");

    bool queryinterface(uuid iid, void** ppv) override;

    void boo() override;
};
}
#endif // __SECOND_H__