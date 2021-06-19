#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__
namespace mycom
{
template<typename _T>
class ptr
{
public:
    ptr() { }
    
    ptr(_T* p)
        : p_(p)
    {
        if(p_)
        {
            p_->addref();
        }
    }

    ptr(ptr<_T>& p)
        : p_(p.p_)
    {
        if(p_)
        {
            p_->addref();
        }
    }

    ~ptr()
    {
        reset();
    }

    ptr& operator=(const ptr& p)
    {
        if(p_)
        {
            p_->release();
            p_ = nullptr;
        }

        p_ = p.p_;
        if(p_)
        {
            p_->addref();
        }

        return *this;
    }

    operator void** ()
    {
        // contained pointer must be nullptr for this operation because is will be overwritten without call to release()
        assert(p_ == nullptr); 
        return (void**)&p_;
    }

    _T* operator->()
    {
        // check if the contained pointer is not nullptr
        assert(p_);
        return p_;
    }

    void reset()
    {
        if(p_)
        {
            p_->release();
            p_ = nullptr;
        }
    }

private: 
    _T* p_ = nullptr;
};
}
#endif // __SMART_POINTER_H__
