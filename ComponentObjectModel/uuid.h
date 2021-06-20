#ifndef __UUID_H__
#define __UUID_H__
namespace mycom
{
    /** \brief Shortens long type name for convenience.
    */
    template<unsigned int uuid_size = 16>
    struct uuid_t
    {
        static const unsigned int uuid_size = 16;
        std::array<unsigned char, uuid_size> data;
        uuid_t()
            : data{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
        {
        }

        uuid_t(uint8_t _01, uint8_t _02, uint8_t _03, uint8_t _04, uint8_t _05, uint8_t _06, uint8_t _07, uint8_t _08, uint8_t _09, uint8_t _10, uint8_t _11, uint8_t _12, uint8_t _13, uint8_t _14, uint8_t _15, uint8_t _16 )
            : data{ _01, _02, _03, _04, _05, _06, _07, _08, _09, _10, _11, _12, _13, _14, _15, _16 }
        {
        }

        uuid_t(const uuid_t& id)
            : data{ id.data }
        { }

        const uuid_t& operator=(const uuid_t& other)
        {
            data = other.data;
            return (*this);
        }

        bool operator==(const uuid_t& other) const
        {
            return data == other.data;
        }
    };
    typedef uuid_t<> uuid;
}
#endif // __UUID_H__
