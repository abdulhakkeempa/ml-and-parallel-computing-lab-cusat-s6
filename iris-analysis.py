from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC


iris_data = load_iris()

X = iris_data.data
y = iris_data.target

print(X.shape)
print(y.shape)

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42)

lr = LogisticRegression()
lr.fit(X_train, y_train)

rf = RandomForestClassifier()
rf.fit(X_train, y_train)

tree = DecisionTreeClassifier()
tree.fit(X_train, y_train)

svc = SVC()
svc.fit(X_train, y_train)


print(f"""

    Training Scores & Testing Scores
    Logistic Regression: {lr.score(X_train, y_train)}, {lr.score(X_test, y_test)}
    Random Forest: {rf.score(X_train, y_train)}, {rf.score(X_test, y_test)}
    Decision Tree: {tree.score(X_train, y_train)}, {tree.score(X_test, y_test)}
    Support Vector Classifier: {svc.score(X_train, y_train)}, {svc.score(X_test, y_test)}

""")