import pandas as pd
import pickle

df = pd.read_json('00.json')

keyframes = df.keyframes

result = []

for bboxes in keyframes:
    box = []
    for box_setting in bboxes:
        box.append([
                box_setting['frame'],
                box_setting['x'] * 1.0,
                box_setting['y'] * 1.0,
                box_setting['w'] * 1.0,
                box_setting['h'] * 1.0
            ])
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

proc = open('00.pkl', 'wb+')

pickle.dump(interpolated_result, proc)

proc.close()
