clear
close
clc

% Paramètres
omega_ext = 25.62; % Vitesse de rotation de la roue extérieure (en rad/s)
omega_int = 11.02;  % Vitesse de rotation de la roue intérieure (en rad/s)
L = 0.5;        % Largeur du véhicule (en m)
r = 0.065/2;        % Rayon de la roue (en m)
dt = 0.001;      % Pas de temps (en s)

% Calcul de la courbure de virage
C = abs(omega_ext - omega_int) / (L/r);

% Temps
t = 0:dt:2; % De 0 à 10 secondes avec un pas de dt seconde

% Initialisation des positions x et y
x = zeros(size(t));
y = zeros(size(t));

% Initialisation de l'angle de virage
theta = 0;
temps = 0;

% Calcul de la trajectoire
for i = 2:length(t)
    % Mise à jour de l'angle de virage
    theta = theta + C * dt;
    temps = temps + dt;
        if theta >= 45/180*pi
            disp(['Temps (s): ',num2str(temps)]);
            disp(['Theta (deg) : ',num2str(theta/pi*180)])
        end 
    % Mise à jour des positions x et y
    x(i) = x(i-1) + r * (omega_ext-omega_int)/L * cos(theta) * dt;
    y(i) = y(i-1) + r * (omega_ext-omega_int)/L * sin(theta) * dt;
end

% Affichage de la trajectoire
figure;
plot3(x, y, zeros(length(t)));
xlabel('Position x (m)');
ylabel('Position y (m)');
zlabel('Temps (s)')
title('Trajectoire du robot');
grid on;