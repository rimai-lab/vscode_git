import numpy as np
from sklearn.datasets import fetch_mldata
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier as Classifier
from sklearn.metrics import confusion_matrix


# 特徴量読み込み
mnist = fetch_mldata("MNIST original", data_home = ".")
data = np.array(mnist.data, np.float32)

data_train, data_test, label_train, label_test = train_test_split(data, mnist.target, test_size=0.2)

# 識別器の初期化、学習
classifier = Classifier()
classifier.fit(data_train, label_train)

# 評価
result = classifier.predict(data_test)

# 集計、出力
cmat = confusion_matrix(label_test, result)
np.savetxt("./Python/ex2-1/result.csv", cmat, fmt="%.0f", delimiter=",")