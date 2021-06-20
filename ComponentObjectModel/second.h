#ifndef __SECOND_H__
#define __SECOND_H__

namespace mycom
{
class second
    : public first
    , public isecond
{
public:
    static bool create(uuid iid, void** ppv, iunknown* outer = nullptr);
    second(iunknown* outer = nullptr, std::string name = "second");

    DECLARE_ADDREF(unknown)
    DECLARE_RELEASE(unknown)

protected:
    bool queryinterface(uuid iid, void** ppv) override;

    void boo() override;
};
}
#endif // __SECOND_H__