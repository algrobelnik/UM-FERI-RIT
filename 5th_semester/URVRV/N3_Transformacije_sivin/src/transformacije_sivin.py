import numpy as np

def normaliziraj_sivine_uniformno(slika, vmin, vmax):
    return ((slika - np.amin(slika)) / (np.amax(slika) - np.amin(slika)) * (vmax - vmin) + vmin).astype(np.float32)

def normaliziraj_sivine_normalno(slika, povprecje, odklon):
    return (slika - np.mean(slika, dtype=np.float32)) / np.std(slika, dtype=np.float32) * odklon + povprecje

def transformiraj_z_lut(slika, lut):
    slika[slika >= len(lut)] = len(lut) - 1
    return lut[slika]

def izenaci_histogram(slika, vmin=0, vmax=1, bins=256, interpolacija=False):
    norm = normaliziraj_sivine_uniformno(slika, 0, bins)
    quant = norm.astype(np.int32)
    hist, bins_array = np.histogram(quant.flatten(), bins)
    cdf = hist.cumsum() 
    cdf = bins * cdf / cdf[-1]
    cdf = normaliziraj_sivine_uniformno(cdf, vmin, vmax)
    if interpolacija:
        return np.interp(norm.flatten(), bins_array[:-1], cdf).reshape(slika.shape)
    else: 
        return transformiraj_z_lut(quant, cdf)
