import pandas as pd
import pickle


def correctx(x, fwidth):
    if x < 0:
        return 0.0
    elif x > fwidth:
        return fwidth*1.0
    else:
        return x*1.0


def correcty(y, fheight):
    if y < 0:
        return 0.0
    if y > fheight:
        return fheight*1.0
    return y*1.0


def correctw(startx, endx, fwidth):
    if endx <= startx:
        return 0.0
    if endx > fwidth:
        endx = fwidth * 1.0
    return endx-startx


def correcth(starty, endy, fheight):
    if endy <= starty:
        return 0.0
    if endy > fheight:
        endy = fheight * 1.0
    return endy-starty


def correct(raw_info, fwidth, fheight):
    corrected_info = [0,0.0,0.0,0.0,0.0]
    corrected_info[0] = raw_info[0]
    corrected_info[1] = correctx(raw_info[1],
                                fwidth)
    corrected_info[2] = correcty(raw_info[2],
                                fheight)
    corrected_info[3] = correctw(corrected_info[1],
                                raw_info[1]+raw_info[3],
                                fwidth)
    corrected_info[4] = correcth(corrected_info[2],
                                raw_info[2]+raw_info[4],
                                fheight)
    return corrected_info


def interpolate(file, fwidth, fheight):

    df = pd.read_json(file+'.json')
    keyframes = df.keyframes

    result = []

    for bboxes in keyframes:
        box = []
        for box_setting in bboxes:
            box.append(correct([box_setting['frame'],
                                box_setting['x'],
                                box_setting['y'],
                                box_setting['w'],
                                box_setting['h']],
                        fwidth, fheight))
        result.append(box)

    # for res in result[0]:
    #     print(res)

    interpolated_result = []

    print('JSON extracted')

    for object_boxes in result:
        interpolated_object_boxes = [object_boxes[0]]
        i = 0
        for i in range(0, len(object_boxes)-1):
            iframe, ix, iy, iw, ih = object_boxes[i]
            fframe, fx, fy, fw, fh = object_boxes[i+1]
            no_frames = fframe - iframe
            stepx = (fx - ix) / no_frames
            stepy = (fy - iy) / no_frames
            stepw = (fw - iw) / no_frames
            steph = (fh - ih) / no_frames
            if no_frames < 2:
                interpolated_object_boxes.append([
                    fframe,
                    fx,
                    fy,
                    fw,
                    fh
                ])
            else:
                for j in range(1, no_frames+1):
                    interpolated_object_boxes.append([
                        iframe + j,
                        ix + stepx * j,
                        iy + stepy * j,
                        iw + stepw * j,
                        ih + steph * j,
                    ])
        interpolated_result.append(interpolated_object_boxes)


    # for res in interpolated_result[0]:
    #     print(res)

    proc = open(file+'.pkl', 'wb+')

    pickle.dump(interpolated_result, proc)

    proc.close()
