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

#ifndef INC_UARTREADBUFFER_H_
#define INC_UARTREADBUFFER_H_

#include <cstdint>
#include <ReadBufferInterface.h>

class UartReadBuffer : public ::EmbeddedProto::ReadBufferInterface
{
    //! Store a maximum of MAX_SIZE bytes in the buffer
    static constexpr uint32_t MAX_SIZE = 50;

  public:
    UartReadBuffer();
    ~UartReadBuffer() override = default;

    /** \see ::EmbeddedProto::ReadBufferInterface::get_size() */
    uint32_t get_size() const override;

    /** \see ::EmbeddedProto::ReadBufferInterface::get_max_size() */
    uint32_t get_max_size() const override;

    /** \see ::EmbeddedProto::ReadBufferInterface::peak() */
    bool peek(uint8_t& byte) const override;

    /** \see ::EmbeddedProto::ReadBufferInterface::advance() */
    void advance() override;

    /** \see ::EmbeddedProto::ReadBufferInterface::advance(const uint32_t N) */
    void advance(const uint32_t N) override;

    /** \see ::EmbeddedProto::ReadBufferInterface::pop() */
    bool pop(uint8_t& byte) override;

    //! Return a pointer to the data array
    uint8_t* get_data_array();

    //! Return a non constant reference to the number of bytes written to the data array.
    uint32_t& get_bytes_written();

    //! Clear all indices, in effect allowing the data to be overwritten.
    void clear();

    //! Push new data into the buffer.
    bool push(uint8_t& byte);

  private:

    //! The array in which the data received over uart is stored.
    uint8_t data_[MAX_SIZE];

    //! The number of bytes currently received and stored in the data array.
    uint32_t write_index_;

    //! The number of bytes read from the data array.
    uint32_t read_index_;
};


#endif /* INC_UARTREADBUFFER_H_ */
