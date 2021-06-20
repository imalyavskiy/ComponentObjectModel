#define DECLARE_QUERYINTERFACE(_SUPER_) \
int32_t queryinterface(IID iid, void** ppv) override \
{ \
    return _SUPER_::queryinterface(iid, ppv); \
}

#define DECLARE_ADDREF(_SUPER_) \
int32_t addref() override \
{ \
    return _SUPER_::addref(); \
}

#define DECLARE_RELEASE(_SUPER_) \
int32_t release() override \
{ \
    return _SUPER_::release(); \
}


namespace mycom
{
class unknown 
    : public iunknown
{
public: 
    static bool create(uuid iid, void** ppv, iunknown* outer = nullptr);
    unknown(iunknown* outer = nullptr, std::string name = "unknown");

    ~unknown();

protected:
    bool queryinterface(uuid iid, void** ppv) override;
    int32_t addref() override;
    int32_t release() override;

protected:
    int32_t counter_ = 0;

    std::string name_;

    iunknown* outer_ = nullptr;
};
}