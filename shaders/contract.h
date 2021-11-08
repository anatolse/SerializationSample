#pragma once

#ifndef HOST_BUILD

#include <cstddef>

#include <string>
#include <vector>
#include <algorithm>

/// YAS
#define _LITTLE_ENDIAN
#include "exception_base.hpp" // hack
#define __YAS_THROW_EXCEPTION(type, msg) Env::Halt();
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

/// YAS

#endif

namespace SerializationSample {

    template<class T>
    const T& mymin(const T& a, const T& b)
    {
        return (b < a) ? b : a;
    }
    struct CountStream
    {
        size_t write(const void* ptr, size_t size)
        {
            m_size += size;
            return size;
        }

        size_t m_size = 0;
    };

    struct MemStream
    {
        MemStream(char* p, size_t s)
            : m_cur(p)
            , m_begin(p)
            , m_end(p + s)
        {

        }

        size_t write(const void* ptr, size_t size)
        {
            auto s = mymin(size, static_cast<size_t>(m_end - m_cur));
            std::copy_n(static_cast<const char*>(ptr), s, m_cur);
            m_cur += s;
            return s;
        }

        size_t read(void* ptr, size_t size)
        {
            size_t s = mymin(size, static_cast<size_t>(m_end - m_cur));
            std::copy_n(m_cur, s, static_cast<char*>(ptr));
            m_cur += s;
            return s;
        }

        bool empty() const
        {
            return m_cur == m_end;
        }

        char peekch() const
        {
            return *m_cur;
        }

        char getch()
        {
            return *m_cur++;
        }

        void ungetch(char)
        {
            --m_cur;
        }

        char* m_cur, * m_begin, * m_end;

    };

    constexpr size_t YAS_FLAGS = yas::binary | yas::no_header | yas::elittle | yas::compacted;

#pragma pack(push, 1)

    struct Buffer
    {
        size_t size;
        char data[0];
    };

	struct InitialParams 
    {
		static const uint32_t METHOD = 0;
        
        struct Attribute
        {
            int type;
            std::string name;
            std::string description;
            bool operator==(const Attribute& other) const
            {
                return type == other.type
                    && name == other.name
                    && description == other.description
                    ;
            }
            template<typename Ar>
            void serialize(Ar& ar)
            {
                ar
                    & type
                    & name
                    & description
                    ;
            }
        };

		//std::string name;
		std::string anotherName;
		std::vector<Attribute> attributes;
        uint32_t health;

        bool operator==(const InitialParams& other) const
        {
            return anotherName == other.anotherName
                && attributes == other.attributes
                && 
                health == other.health
                ;
        }
		template<typename Ar>
		void serialize(Ar& ar) 
		{
			ar
				//& name
				& anotherName
                & attributes
				& health
                ;
		}
	};


#pragma pack(pop)
}
