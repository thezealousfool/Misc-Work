import os, shutil
import cv2
import pickle
import numpy as np

def check_folder(name):
    abs_path = os.path.join(os.getcwd(), name)
    if os.path.exists(abs_path):
        print(abs_path, 'already exists. Emptying folder for repopulation')
        shutil.rmtree(abs_path)
    os.makedirs(abs_path)

def generate_masks(file, fwidth, fheight, nframes):

    check_folder(file)
    pkl_file = open(file+'.pkl', 'rb')

    objects = pickle.load(pkl_file)

    for i in range(nframes):
        frame = np.ones((fheight, fwidth), dtype=np.uint8) * 255

        for obj in objects:
            startf = obj[0][0]
            endf = obj[-1][0]
            if not (i < startf or i > endf):
                bbox = obj[i-startf]
                cv2.rectangle(frame, 
                            (int(bbox[1]), int(bbox[2])),
                            (int(bbox[1])+int(bbox[3]), int(bbox[2])+int(bbox[4])),
                            0, thickness=-1)
        
        cv2.imwrite('%s/%06d.png'%(file,i), frame)
  
    pkl_file.close()
