/** \file interface_publishing.h
    \brief This is the set of classes that are responsible for assigning an uuid to certain interface type.
*/

#ifndef __INTERFACE_PUBLISHING_H__
#define __INTERFACE_PUBLISHING_H__
#pragma once

namespace mycom
{
    template<typename _Type, bool _templ = true>
    struct type_impl
    {
        typedef type_impl< _Type, _templ > this_type;

        static_assert(sizeof(this_type) != 0, "Interface has no UUID assigned.");
    };

    template <typename _Type>
    struct uuidof
    {
        static uuid const& value()
        {
            return type_impl<_Type>::value;
        }
    };

    template <class _Dst_, class _Src_>
    ptr<_Dst_> icast(ptr<_Src_>& src)
    {
        ptr<_Dst_> dst;

        if(!src || !src->queryinterface(uuidof<_Dst_>::value(), (void**)dst) || nullptr == dst.get())
            return {};

        return dst;
    }
}

#define declare_interface_uuid(InterfaceTypeName)                                 \
template<bool _templ>                                                             \
struct mycom::type_impl<InterfaceTypeName, _templ>                                \
{                                                                                 \
    static const typename mycom::uuid value;                                      \
};                                                                                \
                                                                                  \
template<bool _templ>                                                             \
const typename mycom::uuid mycom::type_impl<InterfaceTypeName, _templ>::value

#endif __INTERFACE_PUBLISHING_H__