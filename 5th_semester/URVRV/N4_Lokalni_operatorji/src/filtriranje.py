import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mplimg

def konvolucija(img, kernel):
    padded = np.pad(img, int(kernel.shape[0] / 2), 'constant', constant_values=0)
    output_height = (padded.shape[0] - kernel.shape[0]) + 1
    output_width = (padded.shape[1] - kernel.shape[1]) + 1
    new_img = np.zeros((output_height, output_width), dtype=img.dtype)

    for j in range(0, output_height):
        for i in range(0, output_width):
            new_img[j, i] = np.sum(padded[j:j + kernel.shape[0], i:i + kernel.shape[1]] * kernel).astype(img.dtype)
    return new_img

def filtriraj_gaussovo_jedro(slika, sigma):
    kernel_size = (2 * sigma) * 2 + 1
    k = kernel_size/2 - 1/2
    kernel_size = int(kernel_size)
    H = np.zeros((kernel_size, kernel_size))
    for i in range(0, kernel_size):
        for j in range(0, kernel_size):
            a = - ((np.power(i - k, 2) + np.power(j - k, 2)) / (2 * np.power(sigma, 2)))
            H[i,j] = (1 / (2 * np.pi * np.power(sigma, 2))) * np.power(np.e, a)
    #plt.imshow(H)
    #plt.show()
    return konvolucija(slika, H)

# add colorbar
def filtriraj_sobel_horizontalno(slika):
    kernel = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])
    return konvolucija(slika, kernel)

if __name__=="__main__":
    img_source = mplimg.imread('img.jpg')
    R, G, B = img_source[:,:,0], img_source[:,:,1], img_source[:,:,2]
    img = 0.2989 * R + 0.5870 * G + 0.1140 * B

    fig, axis = plt.subplots(ncols=3, nrows=2)

    for (i, j), val in np.ndenumerate(axis):
        if i == j == 0:
            res = img
            title = "Osnovna slika"
        else:
            calc = (i * (axis.shape[0] + 100)) + j + 0.5 - 1
            res = filtriraj_gaussovo_jedro(img, calc)
            title = "Sigma: " + str(calc)
            res = filtriraj_sobel_horizontalno(res)
        val.set_title(title)
        val.set_xlabel("x piksli")
        val.set_ylabel("y piksli")
        im = val.imshow(res)
        fig.colorbar(im, ax=val)
    plt.show()
