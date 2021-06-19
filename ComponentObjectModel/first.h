#include "unknown.h"

namespace mycom
{
class first
    : public unknown
    , public i_first
{
public:
    static bool CreateInstance(IID iid, void** ppv);

    DECLARE_ADDREF(unknown)
    DECLARE_RELEASE(unknown)

protected:
    first(std::string name = "first");

    bool queryinterface(IID iid, void** ppv) override;
    
    void foo() override;
};
}