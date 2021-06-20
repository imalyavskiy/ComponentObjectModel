/** \file interface_cast.h
    \brief Contains definition of classes and function that cast interfaces
           of one type to other.
*/
#ifndef __INTERFACE_CAST_H__
#define __INTERFACE_CAST_H__
#pragma once
namespace mycom
{
    /** \brief This is the most common helper class that converts pointer of one type to another.

            This class does nothing functional it just declares the type.
        Different conversions, e.g. std::shared_ptr to boost::intrusive_ptr,
        raw pointer to boost::intrusive_ptr, boost::intrusive_ptr to boost::intrusive_ptr,
        std::shared_ptr to std::shared_ptr require different approaches this
        conversions are by use specializations of the current class. If required
        specialization does not present a static_assert will be raised.<br>
        Supported conventions are:<br>
        <ul>
            <li>intrusive to intrusive</li>
            <li>shared to shared</li>
            <li>shared to intrusive</li>
            <li>raw to intrusive</li>
        </ul>
        others make no sense.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
        \tparam _DstP_ destination smart pointer type instantiated from raw destination type
        \tparam _SrcP_ source smart pointer type instantiated from raw source type
    */
    template<class _Dst_, class _Src_, class _DstP, class _SrcP>
    class reference_counter_guard
    {
        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst = _Dst_;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst_ptr = _DstP;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using src_ptr = _SrcP;
    public:
        /** \brief Constructor.
            \param[in] d pointer to destination interface.
            \param[in] s pointer to source interface.
        */
        reference_counter_guard(dst* d, src_ptr& s)
            : m_p(d)
        {
            static_assert(false, "conversion from intrusive to shared makes no sense");
        }

        /** \brief Destructor */
        ~reference_counter_guard()
        {
            static_assert(false, "conversion from intrusive to shared makes no sense");
        }

        /** \brief type cast operator
            \returns destination type pointer.
        */
        operator dst_ptr()
        {
            static_assert(false, "conversion from intrusive to shared makes no sense");
            return {};
        }
    };

    /** \brief This partially specialized helper class converts intrusive pointer intrusive pointer.

                This class specializes the reference_counter_guard class that use boost::intrusive_pointer
            smart pointer for both source and destination pointers. Thus it helps to convert a pointer given as
            boost_intrusive_ptr<_Src_> to boost_intrusive_ptr<_Dst_> and returns it via typecast operator.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
    */
    template<class _Dst_, class _Src_>
    class reference_counter_guard<_Dst_, _Src_, boost::intrusive_ptr<_Dst_>, boost::intrusive_ptr<_Src_>>
    {
        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst = _Dst_;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst_ptr = boost::intrusive_ptr<_Dst_>;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using src_ptr = boost::intrusive_ptr<_Src_>;
    public:
        /** \brief Constructor.
            \param[in] d pointer to destination interface.
            \param[in] s pointer to source interface.
        */
        reference_counter_guard(dst* d, src_ptr& s)
        {
            m_p.reset(d, false);
        }

        /** \brief Destructor */
        ~reference_counter_guard()
        {
        }

            /** \brief type cast operator
                \returns destination type pointer.
            */
        operator dst_ptr()
        {
            return m_p;
        }

    protected:
        /** \brief pointer to the smart pointer class instance of destination type. */
        dst_ptr m_p;
    };

    /** \brief This partially specialized helper class converts regular pointer to intrusive pointer.

                This class specializes the reference_counter_guard class that uses boost::intrusive_pointer
            for destination pointer and raw pointer for source pointer. Thus it helps to convert a pointer given as
            _Src_* to boost_intrusive_ptr<_Dst_> and returns it via typecast operator.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
    */
    template<class _Dst_, class _Src_>
    class reference_counter_guard<_Dst_, _Src_, boost::intrusive_ptr<_Dst_>, _Src_*>
    {
        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst = _Dst_;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst_ptr = boost::intrusive_ptr<_Dst_>;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using src_ptr = _Src_*;
    public:

        /** \brief Constructor.
            \param[in] d pointer to destination interface.
            \param[in] s pointer to source interface.
        */
        reference_counter_guard(dst* d, src_ptr& s)
        {
            m_p.reset(d, false);
        }

        /** \brief Destructor */
        ~reference_counter_guard()
        {
        }

            /** \brief type cast operator
                \returns destination type pointer.
            */
        operator dst_ptr()
        {
            return m_p;
        }

    protected:
        /** \brief pointer to the smart pointer class instance of destination type. */
        dst_ptr m_p;
    };

    /** \brief This partially specialized helper class converts shared pointer to intrusive pointer.

                    This class specializes the reference_counter_guard class that use boost::intrusive_pointer
            smart pointer for destination and std::shared_ptr for source pointer. Thus it helps to convert a pointer given as
            std::shared_ptr<_Src_> to boost_intrusive_ptr<_Dst_> and returns it via typecast operator.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
    */
    template<class _Dst_, class _Src_>
    class reference_counter_guard<_Dst_, _Src_, boost::intrusive_ptr<_Dst_>, std::shared_ptr<_Src_>>
    {
        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst = _Dst_;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst_ptr = boost::intrusive_ptr<_Dst_>;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using src_ptr = std::shared_ptr<_Src_>;
    public:

        /** \brief Constructor.
            \param[in] d pointer to destination interface.
            \param[in] s pointer to source interface.
        */
        reference_counter_guard(dst* d, src_ptr& s)
            : m_p(d)
        {
            ;
        }

        /** \brief Destructor */
        ~reference_counter_guard()
        {
            m_p->release();
        }

        /** \brief type cast operator
            \returns destination type pointer.
        */
        operator dst_ptr()
        {
            return m_p;
        }

    protected:
        /** \brief pointer to the smart pointer class instance of destination type. */
        dst_ptr m_p;
    };

    /** \brief This partially specialized helper class converts shared pointer to shared pointer.

                This class specializes the reference_counter_guard class that use std::shared_ptr
            smart pointer for both source and destination pointers.  Thus it helps convert a pointer given as
            std::shared_ptr<_Src_> to std::shared_ptr<_Dst_> and returns it via typecast operator.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
    */
    template<class _Dst_, class _Src_>
    class reference_counter_guard<_Dst_, _Src_, std::shared_ptr<_Dst_>, std::shared_ptr<_Src_>>
    {
        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst = _Dst_;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using dst_ptr = std::shared_ptr<_Dst_>;

        /** \brief Declaring the type alias in order to be able to access the
                   aliased type from outside of the class. */
        using src_ptr = std::shared_ptr<_Src_>;

    public:

        /** \brief Constructor.
            \param[in] d pointer to destination interface.
            \param[in] s pointer to source interface.
        */
        reference_counter_guard(dst* d, src_ptr& s)
        {
            m_p = std::dynamic_pointer_cast<_Dst_>(s);
        }

        /** \brief Destructor */
        ~reference_counter_guard()
        {
        }

            /** \brief type cast operator
                \returns destination type pointer.
            */
        operator dst_ptr()
        {
            return m_p;
        }

    protected:
        /** \brief pointer to the smart pointer class instance of destination type. */
        dst_ptr m_p;
    };

    /** \brief This function casts interfaces hold by std::shared_ptr to interfaces hold by std::shared_ptr or by boost::intrusive_ptr

            This function casts interfaces hold by std::shared_ptr to interfaces hold
        by std::shared_ptr or by boost::intrusive_ptr.
            The check of cast availability is made by call to source interface
        pointer's getInterface method.
            The check and choice regarding output smart pointer type is made by
        characteristic of requested interface does it inherits from IRefCounted
        or equal or not. If requested interface inherited from IRefCounted or
        equal to it then such interface pointer must be wrapped by
        boost::intrusive_ptr otherwize std::shared_ptr.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
        \tparam _DstP_ destination smart pointer type instantiated from raw destination type
        \tparam _SrcP_ source smart pointer type instantiated from raw source type
        \param[in] src reference to a source smart pointer type.
        \returns value of destination smart pointer type.
    */
    template <class _Dst_, class _Src_,
        class _DstP = std::conditional<std::is_same<IRefCounted, _Dst_>::value || std::is_base_of<IRefCounted, _Dst_>::value, boost::intrusive_ptr<_Dst_>, std::shared_ptr<_Dst_>>::type
        /* IM: I had try to move the type stored in _DstP from this function
               but failed. The reason seems to be that std::conditional
               instantiated at the place where the function is called and
               the IRefCounted has been declared before the function invocation.
               But if to move this std::conditional to some structure to get
               shorten name like as conditional does std::conditional<...>::type
               a few compile errors appear stating that IRefCounted type is
               unknown. Seems like that structure instantiated before the
               IRefCounred declared. Thus let it be like it is until I'll
               get a PhD grade in c++ templates. :-).
        */
    >
    _DstP interface_cast(std::shared_ptr<_Src_>& src)
    {
        _Dst_* p = nullptr;
        if(!src || failed(src->getInterface(uuid_of_type<_Dst_>::value(), (void**)&p)) || !p)
            return {};

        return reference_counter_guard<_Dst_, _Src_, _DstP, std::shared_ptr<_Src_> >(p, src);
    }

    /** \brief This function casts interfaces hold by boost::intrusive_ptr to interfaces hold by boost::intrusive_ptr

            This function casts interfaces hold by boost::intrusive_ptr to
        interfaces hold by boost::intrusive_ptr by std::shared_ptr or by
        boost::intrusive_ptr.
            The check of cast availability is made by call to source interface
        pointer's getInterface method.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
        \param[in] src reference to a source smart pointer type.
        \returns value of destination smart pointer type.
    */
    template <class _Dst_, class _Src_>
    boost::intrusive_ptr<_Dst_> interface_cast(boost::intrusive_ptr<_Src_>& src)
    {
        _Dst_* p = nullptr;
        if(!src || failed(src->getInterface(uuid_of_type<_Dst_>::value(), (void**)&p)) || !p)
            return {};

        return reference_counter_guard<_Dst_, _Src_, boost::intrusive_ptr<_Dst_>, boost::intrusive_ptr<_Src_>>(p, src);
    }

    /** \brief This function casts interfaces hold by regular class pointer to interfaces hold by boost::intrusive_ptr

            This function casts interfaces hold by regular class pointer to
        interfaces hold by boost::intrusive_ptr
            The check of cast availability is made by call to source interface
        pointer's getInterface method.

        \tparam _Dst_ raw destination type.
        \tparam _Src_ raw source type.
        \param[in] src raw pointer of source type.
        \returns value of destination smart pointer type.
    */
    template <class _Dst_, class _Src_>
    boost::intrusive_ptr<_Dst_> interface_cast(_Src_* src)
    {
        _Dst_* p = nullptr;
        if(!src || failed(src->getInterface(uuid_of_type<_Dst_>::value(), (void**)&p)) || !p)
            return {};

        return reference_counter_guard<_Dst_, _Src_, boost::intrusive_ptr<_Dst_>, _Src_*>(p, src);
    }
}

#endif // __INTERFACE_CAST_H__

