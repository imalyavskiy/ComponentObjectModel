#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__
namespace mycom
{
template<typename _T>
class ptr
{
public:
    using value_t = _T;
    using valueptr_t = _T*;

    ptr() { }
    
    ptr(valueptr_t p)
        : p_(p)
    {
        if(p_)
        {
            p_->addref();
        }
    }

    ptr(ptr<value_t>& p)
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

    operator bool() const
    {
        return p_ != nullptr;
    }

    bool operator !() const
    {
        return !operator bool();
    }


    operator void** ()
    {
        // contained pointer must be nullptr for this operation because is will be overwritten without call to release()
        assert(p_ == nullptr); 
        return (void**)&p_;
    }

    valueptr_t operator->()
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

    valueptr_t get()
    {
        return p_;
    }

private: 
    valueptr_t p_ = nullptr;
};
}
#endif // __SMART_POINTER_H__
