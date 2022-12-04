from skimage.color import rgb2hsv, hsv2rgb
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mplimg
import cv2

def segmentiraj_barvo(slika_rgb, barva, val_min=0.1, sat_min=0.1):
    hashmap = {
    'rdeca': (11, 1),
    'rumena': (1, 3),
    'zelena': (3, 5),
    'turkizna': (5, 7),
    'modra': (7, 9),
    'vijolicna': (9, 11),
    }
    color = hashmap.get(barva)
    hsv = rgb2hsv(slika_rgb)
    first = np.logical_and(np.logical_and(hsv[:, :, 0] >= (color[0] * 30) / (12 * 30), hsv[:, :, 1] >= sat_min), hsv[:, :, 2] >= val_min)
    second = np.logical_and(np.logical_and(hsv[:, :, 0] <= (color[1] * 30) / (12 * 30), hsv[:, :, 1] >= sat_min),hsv[:, :, 2] >= val_min)
    if barva == "rdeca":
        image = np.logical_or(first, second)
    else:
        image = np.logical_and(first, second)
    return image

if __name__=="__main__":
    img_source = mplimg.imread('img.jpg')
    img = img_source.copy()
    plt.title("Osnovna slika")
    plt.imshow(img)
    plt.colorbar()
    plt.show()
    mask = segmentiraj_barvo(img, "rumena")
    hsv = rgb2hsv(img)
    hsv[:, :, 1][mask==False] = 0
    hsv[:, :, 1][mask==True] /= hsv[:, :, 1].max()
    new_img = hsv2rgb(hsv).astype(np.float32)
    plt.title(f'Segmentacija nad rumeno barvo')
    plt.imshow(new_img)
    plt.colorbar()
    plt.show()
    hist = (cv2.calcHist([new_img], [0], None, [256], [0.0, 1.0]), cv2.calcHist([new_img], [1], None, [256], [0.0, 1.0]), cv2.calcHist([new_img], [2], None, [256], [0.0, 1.0]))
    plt.title('color graphs')
    plt.plot(hist[0], color='r')
    plt.plot(hist[1], color='g')
    plt.plot(hist[2], color='b')
    plt.xlim([0, 255])
    plt.show()
