clear
close
clc

% Paramètres de simulation
nombre_de_dents = 20; % Nombre de dents sur la roue codeuse
temps_total = 40; % Temps total de simulation en secondes

% Génération du signal de la roue codeuse
t = linspace(0, temps_total, 1000);
theta = linspace(0, 2*pi*temps_total, 1000);
signal_codeur = (square(theta)+1)/2;

% Initialisation des variables
nb_etats_hauts = 0;
nb_etats_bas = 0;
vitesse_en_dents_par_seconde = zeros(size(t));
vitesse_en_rad_par_seconde = zeros(size(t));

% Création de la vidéo
writerObj = VideoWriter('compteur_de_vitesse.avi');
open(writerObj);

% Création de la figure
figure;

% Simulation du compteur de vitesse
for i = 2:length(signal_codeur)
    % Détection du front montant
    if signal_codeur(i) == 1 && signal_codeur(i-1) == 0
        nb_etats_hauts = nb_etats_hauts + 1;
    % Détection du front descendant
    elseif signal_codeur(i) == 0 && signal_codeur(i-1) == 1
        nb_etats_bas = nb_etats_bas + 1;
    end
    
    % Calcul de la vitesse en dents par seconde
    vitesse_en_dents_par_seconde(i) = (nb_etats_hauts + nb_etats_bas) / t(i);
     
    % Conversion de la vitesse en rad/s
    vitesse_en_rad_par_seconde(i) = vitesse_en_dents_par_seconde(i) * (2*pi / nombre_de_dents);
    
    
    % Tracé de la représentation binaire de la roue codeuse
    sgtitle('Simulation de la roue codeuse')
    subplot(3,1,1);
    plot(t(1:i), signal_codeur(1:i), 'b', t(i), signal_codeur(i), 'ro');
    xlim([0 temps_total]);
    ylim([-0.5 1.5]);
    xlabel('Temps (s)');
    ylabel('Signal codeur');
    title('Signal en sortie du capteur');
    
    % Mise à jour du compteur
    subplot(3,1,2);
    bar(1, nb_etats_hauts, 'r');
    hold on;
    bar(2, nb_etats_bas, 'b');
    hold off;
    xlim([0.5 2.5]);
    ylim([0 max(nb_etats_hauts, nb_etats_bas) + 1]);
    xlabel('États');
    ylabel('Compteur');
    title("Compteur d'état");
    set(gca, 'xtick', [1 2], 'xticklabel', {'États hauts', 'États bas'});
    
    % Tracé de la courbe de la vitesse de rotation
    subplot(3,1,3);
    plot(t(1:i), vitesse_en_rad_par_seconde(1:i), 'g');
    ylim([0,1])
    xlabel('Temps (en s)');
    ylabel('Vitesse (en rad/s)');
    title("Vitesse de rotation en fonction du temps");
    hold on;
    
    % Mise à jour de la vidéo
    frame = getframe(gcf);
    writeVideo(writerObj, frame);
end

% Fermeture de la vidéo
close(writerObj);