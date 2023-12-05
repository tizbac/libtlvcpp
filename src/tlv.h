#pragma once

#include <cstdint>
#include <ostream>

namespace ka
{
    using tag = uint32_t;
    using length = uint32_t;
    using value = uint8_t;

    class tlv
    {
    public:
        tlv(const tag &tag = 0, const length &length = 0, const value *value = nullptr);

        template <typename T>
        tlv(const tag &tag, const T &&type);

        explicit tlv(const tag &tag, const char *string);

        ~tlv();

        tlv(const tlv &other);
        tlv &operator=(const tlv &other);

        tlv(tlv &&other) noexcept;
        tlv &operator=(tlv &&other) noexcept;

        friend std::ostream &operator<<(std::ostream &stream, const tlv &tlv);

        tag get_tag() const { return m_tag; }
        length get_length() const { return m_length; }
        value *get_value() const { return m_value; }

    private:
        tag m_tag = 0;
        length m_length = 0;
        value *m_value = nullptr;
    };
}