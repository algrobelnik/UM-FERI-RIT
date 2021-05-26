from __future__ import print_function
from google.cloud import vision

image_uri = 'gs://cloud-vision-codelab/eiffel_tower.jpg'

client = vision.ImageAnnotatorClient()
image = vision.Image()
image.source.image_uri = image_uri

response = client.landmark_detection(image=image)

for landmark in response.landmark_annotations:
    print('=' * 30)
    print(landmark)