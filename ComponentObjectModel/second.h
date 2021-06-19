#include "first.h"

namespace mycom
{
class second
    : public first
    , public i_second
{
public:
    static bool CreateInstance(IID iid, void** ppv);

    DECLARE_ADDREF(unknown)
    DECLARE_RELEASE(unknown)

protected:
    second(std::string name = "second");

    bool queryinterface(IID iid, void** ppv) override;

    void boo() override;
};
}