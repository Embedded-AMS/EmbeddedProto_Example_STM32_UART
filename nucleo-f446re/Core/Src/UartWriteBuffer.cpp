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

#include "UartWriteBuffer.h"

#include <string.h>

void UartWriteBuffer::clear()
{
  write_index_ = 0;
}

uint32_t UartWriteBuffer::get_size() const
{
  return write_index_;
}

uint32_t UartWriteBuffer::get_max_size() const
{
  return MAX_SIZE;
}

uint32_t UartWriteBuffer::get_available_size() const
{
  return MAX_SIZE - write_index_;
}

bool UartWriteBuffer::push(const uint8_t byte)
{
  bool return_value = MAX_SIZE > write_index_;
  if(return_value)
  {
    data_[write_index_] = byte;
    ++write_index_;
  }
  return return_value;
}

bool UartWriteBuffer::push(const uint8_t* bytes, const uint32_t length)
{
  bool return_value = MAX_SIZE > (write_index_ + length);
  if(return_value)
  {
    memcpy(data_ + write_index_, bytes, length);
    write_index_ += length;
  }
  return return_value;
}

uint8_t* UartWriteBuffer::get_data()
{
  return data_;
}
