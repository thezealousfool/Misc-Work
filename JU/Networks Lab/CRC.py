from __future__ import print_function
import argparse

def bitstring(x):
    return bin(x)[2:]

def printlongdiv(lhs, rhs):
    rem = lhs
    div = rhs
    origlen = len(bitstring(div))

    count = 1
    while (div | rem) > 2*div:
        div <<= 1
        count += 1

    quot = 0
    while count>0:
        quot <<= 1
        count -= 1
        divstr = bitstring(div)
        if (rem ^ div) < rem:
            quot |= 1
            rem ^= div
        div >>= 1

    return bitstring(rem)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--sender', dest='sender', action='store_true', default=False)
    parser.add_argument('--data', dest='data')
    args = parser.parse_args()

    if (args.sender):
        bytes_val = (format(x, 'b') for x in bytearray(args.data))
        data_list = []
        data = ''
        for ind, byte in enumerate(bytes_val):
            byte = '0' + byte
            if (ind % 12 == 0 and ind != 0):
                data_list.append(data)
                data = byte
            else:
                if len(byte) < 8:
                    byte = '0' + byte
                data = data + str(byte)
        if data != '':
            data = ('0' * (96 - len(data))) + data
            data_list.append(data)
        for data_temp in data_list:
            data_temp = data_temp + ('0' * 32)
            rem_temp = printlongdiv(int(data_temp, 2), 0xCBF43926)
            rem_temp = ('0' * (32 - len(rem_temp))) + rem_temp
            frame = '{0:b}'.format(int(data_temp, 2) + int(rem_temp, 2))
            frame = ('0' * (128 - len(frame))) + frame
            print(frame)
    else:
        data_array = args.data.split('\n')
        my_byte_array = []
        for frame in data_array:
            rem_frame_rec = printlongdiv(int(frame, 2), 0xCBF43926)
            frame_msg = '0' + format(int(frame[:-32],2), 'b')
            if int(rem_frame_rec, 2) != 0:
                byte_stream = (format(x, 'b') for x in bytearray('error: Corrupted frame'))
            else:
                byte_stream = [ frame_msg[i : i+8] for i in range(0, len(frame_msg), 8) ]
            for b_s_val in byte_stream:
                my_byte_array.append(int(b_s_val, 2))
        for my_char in my_byte_array:
            print(chr(my_char), end='')
        print()
