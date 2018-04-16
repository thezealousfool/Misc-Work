from __future__ import print_function
from random import randint
import Queue
import time
import os

def bitstring(x):
    return bin(x)[2:]

def printlongdiv(lhs, rhs):
    rem = lhs
    div = rhs

    count = 1
    while (div | rem) > 2*div:
        div <<= 1
        count += 1

    quot = 0
    while count > 0:
        quot <<= 1
        count -= 1
        if (rem ^ div) < rem:
            quot |= 1
            rem ^= div
        div >>= 1

    return bitstring(rem)

def encode(data):
    bytes_val = (format(x, 'b') for x in bytearray(data))
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
    frames = []
    for data_temp in data_list:
        data_temp = data_temp + ('0' * 32)
        rem_temp = printlongdiv(int(data_temp, 2), 0xCBF43926)
        rem_temp = ('0' * (32 - len(rem_temp))) + rem_temp
        frame = '{0:b}'.format(int(data_temp, 2) + int(rem_temp, 2))
        frame = ('0' * (128 - len(frame))) + frame
        frames.append(frame)
    return frames

def decode(frame):
    my_byte_array = []
    rem_frame_rec = printlongdiv(int(frame, 2), 0xCBF43926)
    frame_msg = '0' + format(int(frame[:-32], 2), 'b')
    if int(rem_frame_rec, 2) != 0:
        return 'vvk-corrupted'
    else:
        byte_stream = [frame_msg[i: i+8]
                        for i in range(0, len(frame_msg), 8)]
    for b_s_val in byte_stream:
        my_byte_array.append(int(b_s_val, 2))
    decoded_string = ''
    for my_char in my_byte_array:
        decoded_string += chr(my_char)
    return decoded_string

def sender(data_queue, ack_queue, data):
    frames = encode(data)
    frames.append(encode('vvk-done')[0])
    for frame in frames:
        time.sleep(1)
        frame_success = False
        while not frame_success:
            data_queue.put(frame)
            try:
                ack = ack_queue.get(timeout=0.1)
                if decode(ack) == 'received':
                    frame_success = True
            except Queue.Empty:
                print('Timedout')
                frame_success = False
                

def receiver(data_queue, ack_queue):
    while True:
        frame = data_queue.get()
        rand_no_gen = randint(0, len(frame) - 1)
        print(rand_no_gen)
        if (rand_no_gen % 5 == 0):
            frame = frame[:rand_no_gen] + '0' + frame[rand_no_gen + 2:]
        decoded_str = decode(frame)
        if decoded_str != 'vvk-corrupted':
            time.sleep(1)
            if not rand_no_gen % 3 == 0:
                ack_queue.put(encode('received')[0])
            if decoded_str == 'vvk-done':
                break
            else:
                print(decoded_str)
        else:
            ack_queue.put(encode('failure')[0])
            print('Corrupted Frame')
