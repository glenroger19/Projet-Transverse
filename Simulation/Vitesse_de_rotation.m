close
clear
clc

r = 0.065/2;

PWM = 0:15:255;

U = 9; % Tension en V
I = 0.24; % Intensité en A
P_max = I*U; % Puissance en W
C = 0.0784532; % Couple en Nm
R = 1/48; % Gear ratio

w_max = P_max/C;    % vitesse de rotation à vide rad/s

disp(['Vitesse à vide : ' num2str(w_max) ' rad/s'])

% w_max = w_max/2*pi; % vitesse de rotation à vide /s
% w_max = w_max*R;    % vitesse de rotation après réducteur tr/s
% 
% disp(['Vitesse à vide : ' num2str(w_max*2*pi) ' tr/s'])
% 
% disp(['Puissance max : ' num2str(P_max) ' W'])


P = PWM*P_max/255;  % puisssance selon la valeur du PWM

w = P/C;    % vitesse de rotation

figure
plot(PWM,w)
title("La vitesse de rotation en fonction du PWM")
ylabel('Vitesse de rotation (en rad/s)')
xlabel('PWM')

v = 2*pi*w*r;   % vitesse en m/s

pwm = [45 75 105 135 150 165 195 225 255];
temps = 2.00;   % en secondes
distance = [0.401 1.038 1.344 1.584 1.740 1.910 2.153 2.275 2.54]; % en mètre
vitesse = distance/temps;

figure
plot(PWM,v)
hold on
plot(pwm,vitesse);
title('La vitesse du mobile en fonction du PWM')
ylabel('Vitesse (en m/s)')
xlabel('PWM')
legend('Simulation','Réel')

%% 
% Spécifiez le chemin vers le fichier de données
file_path = 'C:\Users\glenn\OneDrive\Bureau\Dossier Glen\2A\Semestre 2\Projet Transverse\Simulation\sans_regulation.txt';
file_path2 = 'C:\Users\glenn\OneDrive\Bureau\Dossier Glen\2A\Semestre 2\Projet Transverse\Simulation\avec_regulation.txt';

% Ouvrir le fichier de données en lecture
file_id = fopen(file_path, 'r');
file_id2 = fopen(file_path2, 'r');

% Lire les données à partir du fichier
data = textscan(file_id, '%f%f%f%f%f%f%f', 'Delimiter', ',');
data2 = textscan(file_id2, '%f%f%f%f%f%f%f', 'Delimiter', ',');

% Fermer le fichier
fclose(file_id);
fclose(file_id2);

% Accéder aux données lues
pwm_d_s = data{1};
vg_d_s = data{2};
vd_d_s = data{3};

pwm_d_a = data2{1};
vg_d_a = data2{2};
vd_d_a = data2{4};


figure
plot(pwm_d_s,vg_d_s)
hold on
plot(pwm_d_s,vd_d_s)
plot(PWM,w)
legend('Vitesse roue gauche sans régulation','Vitesse roue droite sans régulation','Vitesse roue théorique')
xlabel('PWM')
ylabel('Vitesse de rotation (en rad/s)')
title('Vitesse de rotation en fonction du PWM')

figure
plot(pwm_d_a,vg_d_a)
hold on
plot(pwm_d_a,vd_d_a)
plot(PWM,w)
legend('Vitesse roue gauche avec régulation','Vitesse roue droite avec régulation','Vitesse roue théorique')
xlabel('PWM')
ylabel('Vitesse de rotation (en rad/s)')
title('Vitesse de rotation en fonction du PWM')
