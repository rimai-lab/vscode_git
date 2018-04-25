import numpy as np
from sklearn.datasets import fetch_mldata
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from sklearn.ensemble import RandomForestClassifier as Classifier
from sklearn.model_selection import GridSearchCV
#from sklearn.grid_search import GridSearchCV
#from sklearn.cross_validation import train_test_split

# 特徴量読み込み
mnist = fetch_mldata("MNIST original")
data = np.array(mnist.data, np.float32)

data_train, data_test, label_train, label_test = train_test_split(data, mnist.target, test_size=0.2)

# パラメータチューニング
classifier = Classifier()
parameters = [{'n_estimators': [1, 10, 100, 1000]}] # パラメータの探索範囲

# 複数のパラメータの組をリストで渡すことができる
cv = GridSearchCV(classifier, parameters, cv=5, scoring="accuracy") # n_jobsを設定するとImportError

cv.fit(data_train, label_train)
print(cv.best_estimator_) # 最高精度の時の設定

# 最高精度の時の識別器での分類
result = cv.predict(data_test)

# 集計、出力
cmat = confusion_matrix(label_test, result)
np.savetxt("./Python/ex2-2/result.csv", cmat, fmt="%.0f", delimiter=",")
