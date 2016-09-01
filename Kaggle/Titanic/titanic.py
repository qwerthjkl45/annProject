import pandas
import re
import operator
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import LogisticRegression
from sklearn import cross_validation
from sklearn.ensemble import RandomForestClassifier
from sklearn.feature_selection import SelectKBest, f_classif
import matplotlib.pyplot as plt

# Sklearn also has a helper that makes it easy to do cross validation
from sklearn.cross_validation import KFold
import numpy as np
from sklearn import cross_validation

import sys
sys.path.append("../../..")
import ALData


def get_title(name):
    title_search = re.search(' ([A-Za-z]+)\.', name)
    if title_search:
        return title_search.group(1)
    return ""
family_id_mapping = {};
def get_family_id(row):
    # Find the last name by splitting on a comma
    last_name = row["Name"].split(",")[0]
    # Create the family id
    family_id = "{0}{1}".format(last_name, row["FamilySize"])
    # Look up the id in the mapping
    if family_id not in family_id_mapping:
        if len(family_id_mapping) == 0:
            current_id = 1
        else:
            # Get the maximum id from the mapping and add one to it if we don't have an id
            current_id = (max(family_id_mapping.items(), key=operator.itemgetter(1))[1] + 1)
        family_id_mapping[family_id] = current_id
    return family_id_mapping[family_id]


titanic = pandas.read_csv("titanic_train.csv");
titanic_test = pandas.read_csv("titanic_test.csv");

predictors = ["Pclass", "Sex", "Age", "SibSp", "Parch", "Fare", "Embarked", "AgeSquare","FamilySize", "Title", "sex_age"];
#for titanic_train
titanic["Age"] = titanic["Age"].fillna(titanic["Age"].median());
titanic.loc[titanic["Sex"] == "male", "Sex"] = 0
titanic.loc[titanic["Sex"] == "female", "Sex"] = 1;
titanic["Embarked"] = titanic["Embarked"].fillna("S");
titanic.loc[titanic["Embarked"] == "S", "Embarked"] = 0;
titanic.loc[titanic["Embarked"] == "C", "Embarked"] = 1;
titanic.loc[titanic["Embarked"] == "Q", "Embarked"] = 2;
titanic["FamilySize"] = titanic["SibSp"] + titanic["Parch"];
titanic["NameLength"] = titanic["Name"].apply(lambda x: len(x));
titanic["AgeSquare"] = titanic["Age"]**2;
titles = titanic["Name"].apply(get_title)
title_mapping = {"Mr": 1, "Miss": 2, "Mrs": 3, "Master": 4, "Dr": 5, "Rev": 6, "Major": 7, "Col": 7, "Mlle": 8, "Mme": 8, "Don": 9, "Lady": 10, "Countess": 10, "Jonkheer": 10, "Sir": 9, "Capt": 7, "Ms": 2, "Dona": 10}
for k,v in title_mapping.items():
    titles[titles == k] = v
titanic["Title"] = titles
family_ids = titanic.apply(get_family_id, axis=1)
family_ids[titanic["FamilySize"] < 3] = -1
titanic["FamilyId"] = family_ids;
titanic["sex_age"] = titanic["Sex"]* titanic["Age"];

multifeatureNo = [];
multifeatureName = [];
multifeatures= {};
newFIle = pandas.DataFrame();
for index, obj in enumerate(predictors):
	nowColumn = titanic[predictors[index]];
	if index < len(predictors) -1:
		for index1, obj1 in enumerate(predictors):
			if index <= index1:
				nextColumn = titanic[predictors[index1]];
				multifeatureName.append(predictors[index]+"_"+predictors[index1]);
				multifeatures[(index*len(predictors)) + index1] = nowColumn* nextColumn;
				multifeatureNo.append((index*len(predictors)) + index1);
				test = pandas.DataFrame({
				 predictors[index]+"_"+predictors[index1]:nowColumn* nextColumn	
				});
				if newFIle.empty:
					newFIle = newFIle.append(test);
				else:
					newFIle = newFIle.join(test);				
				#print(newFIle.head(2));		


selector = SelectKBest(f_classif, k=5)
selector.fit(newFIle[multifeatureName], titanic["Survived"]);	
scores = -np.log10(selector.pvalues_);
plt.bar(range(len(multifeatureName)), scores)
plt.xticks(range(len(multifeatureName)), multifeatureName, rotation='vertical')
plt.show()

#sex_age & sex_title & fare_title &sex_fare




#for titanic_test
titanic_test["Age"] = titanic_test["Age"].fillna(titanic["Age"].median());
titanic_test.loc[titanic_test["Sex"] == "male", "Sex"] = 0
titanic_test.loc[titanic_test["Sex"] == "female", "Sex"] = 1

titanic_test["Fare"] = titanic_test["Fare"].fillna(titanic_test["Fare"].mean())

titanic_test["Embarked"] = titanic_test["Embarked"].fillna("S");
titanic_test.loc[titanic_test["Embarked"] == "S", "Embarked"] = 0;
titanic_test.loc[titanic_test["Embarked"] == "C", "Embarked"] = 1;
titanic_test.loc[titanic_test["Embarked"] == "Q", "Embarked"] = 2;
titanic_test["FamilySize"] = titanic_test["SibSp"] + titanic_test["Parch"];
titanic_test["NameLength"] = titanic_test["Name"].apply(lambda x: len(x));
titanic_test["AgeSquare"] = titanic_test["Age"]**2;
titanic_test["sex_age"] = titanic_test["Sex"]* titanic_test["Age"];

family_id_mapping = {}
family_ids = titanic_test.apply(get_family_id, axis=1)
family_ids[titanic_test["FamilySize"] < 3] = -1
titanic_test["FamilyId"] = family_ids

titles = titanic_test["Name"].apply(get_title)
for k,v in title_mapping.items():
    titles[titles == k] = v
titanic_test["Title"] = titles

ALData.featurePowerTest(titanic["Age"], titanic["Survived"], 1, 5, 1, False);

alg = LogisticRegression();
kf = KFold(titanic.shape[0], n_folds = 3, random_state = 1);
predictions = [];

algs = {};

algs["LogisticRegression"] = LogisticRegression(random_state=1);
scores = cross_validation.cross_val_score(alg, titanic[predictors], titanic["Survived"], cv=3)
# Take the mean of the scores (because we have one for each fold)
print(scores.mean())

full_predictions = []
for key, alg in algs.items(): 
    alg.fit(titanic[predictors], titanic["Survived"])
    predictions = alg.predict_proba(titanic_test[predictors].astype(float))[:,1]
    full_predictions.append(predictions)


predictions[predictions <= 0.5] = 0;
predictions[predictions > 0.5] = 1;
predictions = predictions.astype(int);

submission = pandas.DataFrame({
        "PassengerId": titanic_test["PassengerId"],
        "Survived": predictions
    });

submission.to_csv("kaggle.csv", index=False)








