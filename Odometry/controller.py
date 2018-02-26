from generate_masks import generate_masks
from interpolate import interpolate

if __name__ == '__main__':
    file = '03'
    fwidth = 1242
    fheight = 375
    nframes = 801

    interpolate(file, fwidth, fheight)
    generate_masks(file, fwidth, fheight, nframes)
