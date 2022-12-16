import numpy as np
import matplotlib.pyplot as plt
from skimage.transform import resize
import cv2
import math


def normaliziraj_konturo(kontura):
    avg = (np.average(kontura[:, 0]), np.average(kontura[:, 1]))
    zeroAvg = kontura.astype(np.float64)
    zeroAvg[:, 0] -= avg[0]
    zeroAvg[:, 1] -= avg[1]
    normalized = zeroAvg / np.max(np.absolute(zeroAvg))
    return normalized

def primerjaj_konturi(contour_ref, contour_example, locljivost=100, koraki=1):
    print("")
    # Rotate the contour of the example to align it with the reference contour
    step = 0
    iou_best = 0
    print("REF:")
    print(contour_ref)
    for i in range(koraki):
        # Calculate the current angle
        fi = i * 360 / koraki
        rotation_matrix = np.array([[np.cos(math.radians(fi)), -np.sin(math.radians(fi))], [np.sin(math.radians(fi)), np.cos(math.radians(fi))]])
        
        # Rotate the contour of the example by the current angle
        print(fi)

        center = np.mean(contour_example, axis=0)
        rotated = np.dot(contour_example - center, rotation_matrix) + center
        print(rotated)
        
        # Discretize the contours by multiplying them by half the resolution and
        # adding and subtracting their common minimum coordinates
        disc_ref = contour_ref * locljivost / 2
        disc_example = rotated * locljivost / 2
        min_val = np.min(np.append(disc_ref, disc_example))
        disc_ref -= min_val
        disc_example -= min_val
        center_ref = np.mean(contour_ref, axis=0)
        center_example = np.mean(contour_example, axis=0)
        disc_ref -= center_ref
        disc_example -= center_example

        #center = np.mean(contour_example, axis=0)
        #rotated = np.dot(contour_example, rotation_matrix)
        #print(contour_example.shape)
        #print(rotated)
        
        # Discretize the contours by multiplying them by half the resolution and
        # adding and subtracting their common minimum coordinates
        #centroid_ref = np.mean(contour_ref, axis=0)
        #centroid_example = np.mean(contour_example, axis=0)
        #disc_ref = contour_ref * locljivost / 2 - centroid_ref
        #disc_example = rotated * locljivost / 2 - centroid_example
        #min_val_x = np.min([np.min(disc_ref[:, 0]), np.min(disc_example[:, 0])])
        #min_val_y = np.min([np.min(disc_ref[:, 1]), np.min(disc_example[:, 1])])
        #print(min_val_x, min_val_y)
        #print(min_val)
        #disc_ref -= [min_val_x, min_val_y]
        #disc_example -= [min_val_x, min_val_y]


        print(disc_example)
        #print(disc_example)
        #resized_ref = disc_ref
        resized_ref = resize(disc_ref, disc_example.shape)
        #resized_example = disc_example
        resized_example = resize(disc_example, disc_ref.shape)
        #print(disc_example)
        print(resized_example)

        
        # Draw the contours into binary masks
        #print(resized_ref)
        #print(resized_example)
        
        zeroMask = np.zeros((locljivost, locljivost), np.uint8)
        im1 = cv2.drawContours(zeroMask.copy(), [resized_ref.astype(np.int64)], -1, 255, -1)
        im2 = cv2.drawContours(zeroMask.copy(), [resized_example.astype(np.int64)], -1, 255, -1)
        # Calculate the intersection over union (IOU) between the contours
        intersection = np.logical_and(im1, im2)
        union = np.logical_or(im1, im2)
        iou = np.sum(intersection) / np.sum(union)
        #plt.title(f'im1: {iou}')
        #plt.imshow(im1)
        #plt.show()
        #plt.title(f'im2 {iou}')
        #plt.imshow(im2)
        #plt.show()
        print(iou)
        
        # Update the best angle and IOU if the current IOU is higher than the previous best
        if iou >= iou_best:
            iou_best = iou
            step = i
    
    # Return the best IOU and angle
    print(iou_best)
    print(step)
    return iou_best, step * np.pi / 2

def poisci_ujemajoce_oblike(mask, mask_ref, min_ocena=0.5, min_povrsina=100, st_korakov=100, locljivost_primerjave=100):
    # Find the contour with the largest area in the reference image
    mask = cv2.UMat(mask, cv2.ACCESS_RW)
    mask_ref = cv2.UMat(mask_ref, cv2.ACCESS_RW)
    contours_ref, hierarchy_ref = cv2.findContours(mask_ref, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    contour_ref = max(contours_ref, key=cv2.contourArea)

    # Normalize the reference contour
    contour_ref = cv2.convexHull(contour_ref)

    # Find all contours in the search image and exclude those with area less than min_povrsina
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    contours = [c for c in contours if cv2.contourArea(c) > min_povrsina]

    # Initialize lists to store matching contours, their scores and angles
    matching_contours = []
    scores = []
    angles = []

    # Compare each contour in the search image to the reference contour
    for contour in contours:
        # Normalize the contour
        contour = cv2.convexHull(contour)

        # Compare the contour to the reference contour using the compare_contours function
        score = compare_contours(contour_ref, contour, locljivost_primerjave, st_korakov)

        # If the match score is greater than the minimum match score, store the contour, score and angle
        if score > min_ocena:
            matching_contours.append(contour)
            scores.append(score)
            angles.append(best_match_angle(contour_ref, contour))

    # Return lists of matching contours, scores and angles
    return matching_contours, scores, angles
