--- LMD (langage de manipulation de données)

--- Contenu des tables (tests)

-- Table Utilisateur

INSERT INTO Utilisateur(nom,prenom,code,email) VALUES('VAIRA','Thierry','1234','tvaira@free.fr');
INSERT INTO Utilisateur(nom,prenom,code,email) VALUES('BEAUMONT','Jérôme','0000','beaumont@lasalle84.org');
INSERT INTO Utilisateur(nom,prenom,code,email) VALUES('MDOIOUHOMA','Nakib','6666','nakibmdoiouhoma.btssn@gmail.com');

-- Table Capsule

INSERT INTO Capsule VALUES (1,'Nespresso','colombia','Arabica cueilli en récolte tardive, unique comme la cordillère des Andes',6);
INSERT INTO Capsule VALUES (2,'Nespresso','indonesia','Arabica, né des pluies de Sumatra, labellisé Fairtrade et certifié biologique',8);
INSERT INTO Capsule VALUES (3,'Nespresso','ethiopia','Arabica dépulpé par voie sèche sous le soleil bienfaiteur',4);
INSERT INTO Capsule VALUES (4,'Nespresso','volluto','Doux et léger',4);
INSERT INTO Capsule VALUES (5,'Nespresso','capriccio','Riche et exclusif',5);
INSERT INTO Capsule VALUES (6,'Nespresso','cosi','Équilibré et délicatement torréfié',4);
INSERT INTO Capsule VALUES (7,'Nespresso','scuro','Idéal pour les amateurs de recettes intenses et équilibrées à base de lait',0);
INSERT INTO Capsule VALUES (8,'Nespresso','vanilla-eclair','Saveur éclair à la vanille',0);

-- Table LongueurBoisson

INSERT INTO LongueurBoisson(idLongueurBoisson,type) VALUES
(1,'Ristretto'),
(2,'Espresso'),
(3,'Lungo');

-- Table Magasin

INSERT INTO Magasin(idMagasin,nbRangees,quantiteMaxRangee) VALUES(1,8,4);

-- Table StockMagasin

INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,1,1,0);
INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,1,2,0);
INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,2,3,0);
INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,2,4,0);
INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,3,5,0);
INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,4,6,0);
INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,5,7,0);
INSERT INTO StockMagasin (idMagasin,idCapsule,rangee,quantite) VALUES(1,6,8,0);

-- Table AnalyseSante

INSERT INTO AnalyseSante(idUtilisateur,nombreCafeDuJour) VALUES(1,0);
INSERT INTO AnalyseSante(idUtilisateur,nombreCafeDuJour) VALUES(2,0);
INSERT INTO AnalyseSante(idUtilisateur,nombreCafeDuJour) VALUES(3,0);

-- Table Preferences

INSERT INTO Preferences(idPreferences,idUtilisateur,capsuleActuelle,capsulePreferee,longueurBoissonActuelle) VALUES(1,1,1,1,1);
INSERT INTO Preferences(idPreferences,idUtilisateur,capsuleActuelle,capsulePreferee,longueurBoissonActuelle) VALUES(2,2,4,3,3);
INSERT INTO Preferences(idPreferences,idUtilisateur,capsuleActuelle,capsulePreferee,longueurBoissonActuelle) VALUES(3,3,5,5,2);

-- Table Entretien

INSERT INTO Entretien(nombreCafeTotal,nombreCafeAvantDetartrage) VALUES(0,75);
