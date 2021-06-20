/** \file interface_publishing.h
    \brief This is the set of classes that are responsible for assigning an uuid to certain interface type.
*/

#ifndef __INTERFACE_PUBLISHING_H__
#define __INTERFACE_PUBLISHING_H__
#pragma once

namespace mycom
{
    /** \brief Shortens long type name for convenience. 
    */
    typedef boost::uuids::uuid uuid;

    /** \brief This is a default template class.

            This template class is a screamer class that raises a static assert
        when libClique::uuid_of_type<>::value() is called for the interface type
        that was not mentioned by means of declare_interface_uuid macro.
        \tparam _Type Type of an interface to report that such interface has
                      no corresponding uuid
        \tparam _templ This parameter requires to instantiate this template
                    class in an implicit way.
    */
    template<typename _Type, bool _templ = true>
    struct type_impl
    {
        /** \brief Type shortener used for convenience reason. 
        */
        typedef type_impl< _Type, _templ > this_type;

        /** \brief A static assert raised when the interface type assigned to _Type was not
                   mentioned by means of declare_interface_uuid macro
        */
        static_assert(sizeof(this_type) != 0, "Interface has no UUID assigned.");
    };

    /** \brief This class intended to get the uuid related to interface type provided by means of template parameter

        Usage example:<br>
        Assume we have previously declared ISomeThing interface:
        \code
        struct ISomeThing {
            // interface methods
        };
        \endcode
        And it has an uuid assigned:
        \code
        declare_interface_uuid(ISomeThing) =
            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        \endcode
        Then call to:
        \code
        libClique::uuid_of_type<ISomeThing>::value();
        \endcode
        will return the {00000000-0000-0000-0000-000000000000} uuid.

        \tparam _Type typename of the interface to get uuid of.
    */
    template <typename _Type>
    struct uuid_of_type
    {
        /** \brief This function returns uuid of the interface type declared by _Type template parameter.

                This function instantiates a type_impl template class. The class is
            instantiated for certain interface type and contains its uuid value
            in the value static variable(common to all class instances).
                If such template class was not instantiated. This means that the
            declare_interface_uuid macro was not mentioned for certain interface type.
            Then non specialized template class type instantiated and static_assert
            raises with "Interface has no UUID assigned." statement.

            \returns constant reference to an interface uuid.
        */
        static uuid const& value()
        {
            return type_impl<_Type>::value;
        }
    };
}

/** \brief This macro links together an interface and its uuid.

        A mention of this macro instantiates a libClique::type_impl template
    class for the type of the interface given through macro parameter and
    creates its static instance. This instance contains a static variable of
    libClique::uuid(boost::uuids:uuid) with value of interface uuid.
        If this macro was not mentioned for the certain interface then at call to
    libClique::uuid_of_type<>::value instantiates a non specialized libClique::type_impl
    that raise static assert with the message  - "Interface has no UUID assigned.".
        The only template argument of bool type required to instantiate the
    type implicitly.

    Usage example:<br>
    Assume we have previously declared ISomeThing interface:
    \code
    struct ISomeThing {
        // interface methods
    };
    \endcode
    The uuid assignment looks like the following:
    \code
    declare_interface_uuid(ISomeThing) =
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    \endcode

*/
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