#ifndef __COLLECTION_H__
#define __COLLECTION_H__
namespace mycom
{
class collection
    : public second
    , public icollection
{
public:

    static bool create(uuid iid, void** ppv, iunknown* outer = nullptr);
    collection(iunknown* outer = nullptr, std::string name = "collection");

    // iunknown
    DECLARE_ADDREF(second)
    DECLARE_RELEASE(second)
    bool queryinterface(uuid id, void** ppv) override;

    // icollection
    virtual size_t size() const override;

    virtual iunknown* getitem(size_t index) override;

protected:
    std::vector<std::unique_ptr<second>> items_;
};
}
#endif // __COLLECTION_H__
