from __future__ import print_function
from random import randint
import subprocess
import argparse
import sys

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--data', dest='data')
    args = parser.parse_args()

    if (args.data == None):
        print('error :: data not supplied')
        print('usage :', sys.argv[0] , '--data <string to send>')
        sys.exit(-1)

    process = subprocess.Popen(['python', 'CRC.py', '--sender', '--data', args.data], stdout=subprocess.PIPE)
    out, err = process.communicate()

    out_frames = out.split('\n')
    for frame in out_frames:
        if frame != '':
            print(frame)
            rand_no_gen = randint(0, len(frame) - 1)
            print(rand_no_gen)
            if (rand_no_gen % 5 == 0):
                frame = frame[:rand_no_gen] + '0' + frame[rand_no_gen + 2:]
            read_process = subprocess.Popen(['python', 'CRC.py', '--data', frame], stdout=subprocess.PIPE)
            read_out, read_err = read_process.communicate()
            print(read_out)
