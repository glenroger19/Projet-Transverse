clear
close
clc

% Paramètres
omega_ext = 16; % Vitesse de rotation de la roue extérieure (en rad/s)
omega_int = 16;  % Vitesse de rotation de la roue intérieure (en rad/s)
L = 0.5;        % Largeur du véhicule (en m)
r = 0.065/2;        % Rayon de la roue (en m)
dt = 0.1;      % Pas de temps (en s)

% Calcul de la courbure de virage
C = abs(omega_ext - omega_int) / (L/r);

% Temps
t = 0:dt:3; % De 0 à 10 secondes avec un pas de dt seconde

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
    % Mise à jour des positions x et y
    x(i) = x(i-1) + r * (omega_ext-omega_int)/L * cos(theta) * dt;
    y(i) = y(i-1) + r * (omega_ext-omega_int)/L * sin(theta) * dt;
end

% Affichage de la trajectoire
figure;
plot3(x, y, t);
xlabel('Position x (m)');
ylabel('Position y (m)');
zlabel('Temps (s)')
title(['Trajectoire du robot pour vitesse de rotation extérieur 16 rad/s et ' ...
    'vitesse de rotation intérieur -16 rad/s']);
grid on;