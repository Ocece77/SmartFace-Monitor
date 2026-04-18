import serial, time
from mac_notifications import client
from pathlib import Path

# Connexion à l'Arduino 
arduinoData = serial.Serial('/dev/cu.usbmodem14801', 9600)

if __name__ == "__main__":

    # Boucle pour lire les données Arduino en continue
    while True:
        # Lecture de l'arduino 
        cc = arduinoData.readline().decode("utf-8").strip()
        
        # Affiche le contenu du serial monitor 
        print(cc)

        # Si Arduino envoie "1" → trop proche
        if cc == '1':

            # Création de la notification macOS
            client.create_notification(
                title="Hey 👋 trop près !", 
                subtitle="Ton écran ne va pas s’enfuir 😄 recule un peu",  # message
                sound="Frog",  # son de la notig
                action_button_str="C'est compris",  
                icon=str(Path(__file__).parent / "icon.png"),  
            )

            # Attendre 20 secondes pour éviter le spam
            time.sleep(20)

            # Stop l'écoute des interactions
            client.stop_listening_for_callbacks()