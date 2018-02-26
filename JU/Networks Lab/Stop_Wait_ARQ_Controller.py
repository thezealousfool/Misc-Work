import multiprocessing

import Stop_Wait_ARQ as arq

if __name__ == '__main__':
    data = 'Hello my name is Vivek Roy, I am a student of JU'
    data_queue = multiprocessing.Queue()
    ack_queue = multiprocessing.Queue()
    sender = multiprocessing.Process(
        target=arq.sender, args=(data_queue, ack_queue, data,))
    receiver = multiprocessing.Process(
        target=arq.receiver, args=(data_queue, ack_queue,))

    sender.start()
    receiver.start()

    sender.join()
    receiver.join()
