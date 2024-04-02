% Paramètres
freq = 1000; period = 1/freq; duration = 2; num_frames = 100;
initial_duty_cycle = 0.1; final_duty_cycle = 0.9; duty_cycles = linspace(0, 1, num_frames);

% Création des images pour l'animation
frames = cell(1, num_frames);
for i = 1:num_frames
    t = linspace(0, duration, 1000);
    pwm_signal = mod(t, period) < duty_cycles(i) * period;
    figure('visible', 'off'); plot(t, pwm_signal, 'b', 'LineWidth', 2);
    axis([0 duration -0.1 1.1]); xlabel('Temps (s)'); ylabel('Amplitude');
    title(['Signal PWM - Rapport cyclique : ', num2str(duty_cycles(i))]);
    frames{i} = getframe(gcf); close;
end

% Création du fichier vidéo
video_name = 'pwm_animation.mp4'; fps = 10;
writerObj = VideoWriter(video_name, 'MPEG-4'); writerObj.FrameRate = fps; open(writerObj);
for i = 1:num_frames; writeVideo(writerObj, frames{i}); end; close(writerObj);

disp(['Animation PWM enregistrée sous : ', video_name]);
