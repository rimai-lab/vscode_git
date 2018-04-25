from keras.applications.vgg16 import VGG16
model = VGG16(weights='imagenet')

from keras.applications.vgg16 import preprocess_input
from keras.preprocessing import image
import numpy as np

img = image.load_img("input.jpg", target_size=(224, 224))
img = image.img_to_array(img)
imgs = preprocess_input(np.asarray([img]))

from keras.applications.vgg16 import decode_predictions
preds = model.predict(imgs)
results = decode_predictions(preds, top=5)[0]
for result in results:
    print(result)