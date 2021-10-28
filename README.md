# TP1_Reseau
TP1 du cours de réseau pour le Jeux Vidéo à l'UQAC, portant sur l'utilisation des Sockets de Berkeley sous windows.    

## Utilisation
Pour utiliser le projet, téléchargez le en local, puis générez et configurez le projet avec Cmake.  
Une fois cela fait, allez dans le dossier Build, puis ouvrez le fichier TP1_Reseau.sln avec Visual Studio 2019.  
Générez le projet, des fichiers .exe auront été crées dans le dossier Build\Debug. Avez cmd, lancez le fichier server.exe de la manière suivante:  
```server.exe port```  
en remplaçant "port" par le numéro de port sur lequel vous souhaitez que le serveur soit visible (i.e: 8888).  

Dans un second temps, lancez le fichier client.exe de la manière suivante:  
```client.exe addresse port```  
en remplaçant "adresse" par l'adresse sur laquelle vous souhaitez vous connecter (i.e: localhost).  

## Question  
Sur le TP, la question suivante est posée:  
Quel protocole choisi-t-on pour le chat du jeu vidéo ? UDP ou TCP et pourquoi ?   

On choisira le protocole TCP, car on souhaite être certain que le message arrive bien à destination.  
