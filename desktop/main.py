#
# Copyright (C) 2020-2022 Embedded AMS B.V. - All Rights Reserved
#
# This file is part of Embedded Proto.
#
# Embedded Proto is open source software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, version 3 of the license.
#
# Embedded Proto  is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Embedded Proto. If not, see <https://www.gnu.org/licenses/>.
#
# For commercial and closed source application please visit:
# <https://EmbeddedProto.com/license/>.
#
# Embedded AMS B.V.
# Info:
#   info at EmbeddedProto dot com
#
# Postal address:
#   Johan Huizingalaan 763a
#   1066 VH, Amsterdam
#   the Netherlands
#

import serial
import argparse
from generated import uart_messages_pb2


def print_control_keys():
    print("Command keys are:")
    print("To move around press:")
    print("  w")
    print("a s d")
    print("")
    print("To try to grab your price press \"g\"")
    print("If your done press \"Q\"")


def process_cmd_input():
    send_command = True
    quit = False
    msg = uart_messages_pb2.Command()
    msg.value = 1

    char = input("Next command: ")
    if "w" == char:
        msg.button = uart_messages_pb2.Command.Up
    elif "s" == char:
        msg.button = uart_messages_pb2.Command.Down
    elif "a" == char:
        msg.button = uart_messages_pb2.Command.Left
    elif "d" == char:
        msg.button = uart_messages_pb2.Command.Right
    elif "g" == char:
        msg.button = uart_messages_pb2.Command.Grab
    elif "Q" == char:
        msg.button = uart_messages_pb2.Command.Stop
        # Stop the loop
        quit = True
    else:
        send_command = False
        print_control_keys()

    if send_command:
        return msg, quit
    else:
        return None, quit


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--com', default="/dev/ttyACM0", help='The desired comport to open')
    args = parser.parse_args()

    # Try to open the serial port with the default baud rate.
    with serial.Serial(args.com, 115200, timeout=1) as ser:
        print_control_keys()

        running = True

        while running:
            command, quit = process_cmd_input()
            running = not quit

            if command:
                b = bytearray()

                # Serialize the command message and send it over uart.
                command_str = command.SerializeToString()
                # First send the length of the message.
                l = len(command_str)
                b.extend(l.to_bytes(1, byteorder='little'))
                # Next send the actual data
                b.extend(command_str)
                ser.write(b)

                # Await a reply.
                # First the length of the message.
                length_bytes = ser.read(1)
                length = int.from_bytes(length_bytes, byteorder="little")
                if 0 < length:
                    # Next the actual data
                    bytes = ser.read(length)

                    # Check if we have received all bytes.
                    if length == len(bytes):
                        reply = uart_messages_pb2.Reply()
                        reply.ParseFromString(bytes)

                        # Do something with the reply.
                        if reply.price:
                            print("We have a winner!")
                        else:
                            print("x pos: " + str(reply.x_pos))
                            print("y pos: " + str(reply.y_pos))

