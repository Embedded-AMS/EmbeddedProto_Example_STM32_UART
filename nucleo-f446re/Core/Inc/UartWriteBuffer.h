/*
 *  Copyright (C) 2020 Embedded AMS B.V. - All Rights Reserved
 *
 *  This file is part of Embedded Proto.
 *
 *  Embedded Proto is open source software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, version 3 of the license.
 *
 *  Embedded Proto  is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Embedded Proto. If not, see <https://www.gnu.org/licenses/>.
 *
 *  For commercial and closed source application please visit:
 *  <https://EmbeddedProto.com/license/>.
 *
 *  Embedded AMS B.V.
 *  Info:
 *    info at EmbeddedProto dot com
 *
 *  Postal adress:
 *    Johan Huizingalaan 763a
 *    1066 VH, Amsterdam
 *    the Netherlands
 */

#ifndef INC_UARTWRITEBUFFER_H_
#define INC_UARTWRITEBUFFER_H_

#include <cstdint>
#include <WriteBufferInterface.h>

class UartWriteBuffer : public ::EmbeddedProto::WriteBufferInterface
{
    //! Store a maximum of MAX_SIZE bytes in the buffer
    static constexpr uint32_t MAX_SIZE = 50;

  public:
    UartWriteBuffer() = default;
    ~UartWriteBuffer() override = default;

    //! \see ::EmbeddedProto::WriteBufferInterface::clear()
    virtual void clear() override;

    //! \see ::EmbeddedProto::WriteBufferInterface::get_size()
    virtual uint32_t get_size() const override;

    //! \see ::EmbeddedProto::WriteBufferInterface::get_max_size()
    virtual uint32_t get_max_size() const override;

    //! \see ::EmbeddedProto::WriteBufferInterface::get_available_size()
    virtual uint32_t get_available_size() const override;

    //! \see ::EmbeddedProto::WriteBufferInterface::push()
    virtual bool push(const uint8_t byte) override;

    //! \see ::EmbeddedProto::WriteBufferInterface::push()
    virtual bool push(const uint8_t* bytes, const uint32_t length) override;

    //! Return a pointer to the data array.
    uint8_t* get_data();

  private:

    //! The array in which the serialized data is stored.
    uint8_t data_[MAX_SIZE];

    //! The number of bytes currently serialized in the array.
    uint32_t write_index_;

};


#endif /* INC_UARTWRITEBUFFER_H_ */
