--- LDD (langage de définition de données)

--- Supprime les tables

DROP TABLE IF EXISTS Entretien;
DROP TABLE IF EXISTS Preferences;
DROP TABLE IF EXISTS AnalyseSante;
DROP TABLE IF EXISTS StockMagasin;
DROP TABLE IF EXISTS Magasin;
DROP TABLE IF EXISTS LongueurBoisson;
DROP TABLE IF EXISTS Capsule;
DROP TABLE IF EXISTS Utilisateur;

--- Création des tables

-- Structure de la table Utilisateur

CREATE TABLE IF NOT EXISTS Utilisateur(
  idUtilisateur INTEGER PRIMARY KEY AUTOINCREMENT,
  nom varchar(64) NOT NULL,
  prenom varchar(64) NOT NULL,
  code varchar(6) DEFAULT NULL,
  badge VARCHAR,
  email varchar(64) NOT NULL,
  UNIQUE (nom,prenom)
);

-- Structure de la table Capsule

CREATE TABLE IF NOT EXISTS Capsule(
  idCapsule INTEGER PRIMARY KEY AUTOINCREMENT,
  marque VARCHAR NOT NULL,
  designation VARCHAR,
  description VARCHAR,
  intensite INTEGER DEFAULT 0
);

-- Structure de la table LongueurBoisson

CREATE TABLE IF NOT EXISTS LongueurBoisson(idLongueurBoisson INTEGER PRIMARY KEY, type VARCHAR);

-- Structure de la table Magasin

CREATE TABLE IF NOT EXISTS Magasin(
  idMagasin INTEGER PRIMARY KEY,
  nbRangees INTEGER NOT NULL DEFAULT 8,
  quantiteMaxRangee INTEGER NOT NULL DEFAULT 4
);

-- Structure de la table StockMagasin

CREATE TABLE IF NOT EXISTS StockMagasin(
  idStockMagasin INTEGER PRIMARY KEY AUTOINCREMENT,
  idMagasin INTEGER NOT NULL,
  idCapsule INTEGER NOT NULL,
  rangee INTEGER NOT NULL,
  quantite INTEGER DEFAULT 0,
  CONSTRAINT Unique_Rangee UNIQUE (idMagasin,rangee),
  CONSTRAINT Stock_fk_1 FOREIGN KEY (idMagasin) REFERENCES Magasin(idMagasin) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_2 FOREIGN KEY (idCapsule) REFERENCES Capsule(idCapsule) ON DELETE CASCADE
);

-- Structure de la table AnalyseSante

CREATE TABLE IF NOT EXISTS AnalyseSante(
  idUtilisateur INTEGER PRIMARY KEY NOT NULL,
  nombreCafeDuJour INTEGER DEFAULT 0,
  CONSTRAINT AnalyseSante_fk_1 FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur) ON DELETE CASCADE
);

-- Structure de la table Preferences

CREATE TABLE IF NOT EXISTS Preferences(
  idPreferences INTEGER PRIMARY KEY,
  idUtilisateur INTEGER NOT NULL,
  capsuleActuelle INTEGER NOT NULL,
  capsulePreferee INTEGER NOT NULL,
  longueurBoissonActuelle INTEGER NOT NULL,
  CONSTRAINT Preferences_fk_1 FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur) ON DELETE CASCADE,
  CONSTRAINT Preferences_fk_2 FOREIGN KEY (capsuleActuelle) REFERENCES Capsule(idCapsule) ON DELETE CASCADE,
  CONSTRAINT Preferences_fk_3 FOREIGN KEY (longueurBoissonActuelle) REFERENCES LongueurBoisson(idLongueurBoisson) ON DELETE CASCADE
);

-- Structure de la table Entretien

CREATE TABLE IF NOT EXISTS Entretien (
	nombreCafeTotal INTEGER DEFAULT 0,
	nombreCafeAvantDetartrage INTEGER DEFAULT 75
);
