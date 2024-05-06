import os
import serial

# Définition du chemin vers le dossier de destination
destination_folder = r'C:\Users\glenn\OneDrive\Bureau\pwm_avec_capteur'

# Changez le répertoire de travail vers le dossier de destination
os.chdir(destination_folder)

# Définition du port série et de la vitesse de communication
port = 'COM3'  # Assurez-vous de spécifier le bon port série
baud_rate = 9600

# Ouvrir le port série
ser = serial.Serial(port, baud_rate)

# Ouvrir le fichier pour écrire les données
file_name = 'data.txt'
with open(file_name, 'w') as file:
    try:
        # Lire les données depuis le port série et les écrire dans le fichier
        while True:
            # Lire une ligne de données depuis le port série
            data = ser.readline().decode().strip()
            # Écrire la ligne dans le fichier
            file.write(data + '\n')
            # Afficher les données reçues dans la console
            print(data)

    except KeyboardInterrupt:
        # Fermer le port série et le fichier lorsqu'on appuie sur Ctrl+C
        ser.close()
        print("Fermeture du port série.")
