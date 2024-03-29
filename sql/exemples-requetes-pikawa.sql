--- Exemples et exercices d'accompagnement : déterminer les requêtes SQL

-- Liste des utilisateurs

SELECT * FROM Utilisateur;

-- Liste des capsules

SELECT * FROM Capsule;

--- Nombre de capsules

SELECT COUNT(*) AS NbCapsules FROM Capsule;

--- Liste des types de boisson

SELECT * FROM LongueurBoisson;

|idTypeBoisson|type|
|---|---|
|1|Ristretto|
|2|Espresso|
|3|Lungo|

--- Contenu du magasin

SELECT * FROM Magasin;

SELECT * FROM StockMagasin;

SELECT Magasin.nbRangees,Magasin.quantiteMaxRangee,StockMagasin.rangee,Capsule.designation,Capsule.intensite,StockMagasin.quantite FROM StockMagasin
INNER JOIN Magasin ON Magasin.idMagasin=StockMagasin.idMagasin
INNER JOIN Capsule ON Capsule.idCapsule=StockMagasin.idCapsule;

|nbRangees|quantiteMax|rangee|designation|intensite|quantite|
|---------|-----------|------|-----------|---------|--------|
|8	|4	|1	|colombia	|6	|0 |
|8	|4	|2	|colombia	|6	|0 |
|8	|4	|3	|indonesia	|8	|0 |
|8	|4	|4	|indonesia	|8	|0 |
|8	|4	|5	|ethiopia	|4	|0 |
|8	|4	|6	|volluto	|4	|0 |
|8	|4	|7	|capriccio	|5	|0 |
|8	|4	|8	|cosi	    |4	|0 |

--- Préférences d'un utilisateur

SELECT Preferences.idPreferences, Utilisateur.idUtilisateur, Utilisateur.nom, Utilisateur.prenom, Capsule.idCapsule, Capsule.designation, LongueurBoisson.idLongueurBoisson, LongueurBoisson.type FROM Preferences
INNER JOIN Utilisateur ON Utilisateur.idUtilisateur=Preferences.idUtilisateur
INNER JOIN Capsule ON Capsule.idCapsule=Preferences.capsuleActuelle
INNER JOIN LongueurBoisson ON LongueurBoisson.idLongueurBoisson=Preferences.longueurBoissonActuelle
WHERE Utilisateur.nom='VAIRA';

UPDATE Preferences SET capsuleActuelle='1' WHERE Preferences.idUtilisateur='1';
