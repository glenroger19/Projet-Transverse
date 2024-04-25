close
clear
clc

r = 0.065/2;

PWM = 0:15:255;

U = 12; % Tension en V
I = 0.19; % Intensité en A
P_max = I*U; % Puissance en W
C = 0.0784532; % Couple en Nm
R = 1/48; % Gear ratio

w_max = P_max/C;    % vitesse de rotation à vide rad/s

disp(['Vitesse à vide : ' num2str(w_max) ' rad/s'])

w_max = w_max/2*pi; % vitesse de rotation à vide tr/s
w_max = w_max*R;    % vitesse de rotation après réducteur tr/s

disp(['Vitesse à vide : ' num2str(w_max*2*pi) ' tr/s'])

disp(['Puissance max : ' num2str(P_max) ' W'])


P = PWM*P_max/255;  % puisssance selon la valeur du PWM

w = P/C;    % vitesse de rotation

figure
plot(w,PWM)
title("Tension d'entrée en fonction de la vitesse de rotation")
xlabel('Vitesse de rotation (en rad/s)')
ylabel('Tension (en V)')

v = 2*pi*w*r;   % vitesse en m/s

pwm = [45 75 105 135 150 165 195 225 255];
temps = 2.00;   % en secondes
distance = [0.401 1.038 1.344 1.584 1.740 1.910 2.153 2.275 2.54]; % en mètre
vitesse = distance/temps;

figure
plot(v,PWM)
hold on
plot(vitesse,pwm);
title('PWM en fonction de la vitesse du mobile')
xlabel('Vitesse (en m/s)')
ylabel('PWM')
legend('Simulation','Réel')