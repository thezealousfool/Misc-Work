result = [[
    [0, 0., 0., 0., 0],
    [1, 5., 5., 5., 5],
    [5, 10., 10., 10., 10]
]]

interpolated_result = []

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

print(interpolated_result)
