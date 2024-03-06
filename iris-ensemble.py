from sklearn.ensemble import VotingClassifier

from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split

from sklearn.metrics import accuracy_score

iris_data = load_iris()

X = iris_data.data
y = iris_data.target

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42)

# Create a list of classifiers.
classifiers = [
    ('lr', LogisticRegression()),
    ('rf', RandomForestClassifier(n_estimators=100)),
    ('svc', SVC())
]

# Create a voting classifier.
voting_clf = VotingClassifier(estimators=classifiers, voting='hard')

# Train the voting classifier.
voting_clf.fit(X_train, y_train)

# Make predictions.
y_pred = voting_clf.predict(X_test)

# Evaluate the accuracy.
print(accuracy_score(y_test, y_pred))
