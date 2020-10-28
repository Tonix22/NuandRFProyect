
csv = load('rx.csv');
signal_i = csv(:, 1) ./ 2048.0;
signal_q = csv(:, 2) ./ 2048.0;
signal = signal_i + 1j .* signal_q;
% Plot the magnitude of the signal in the time domain
signal = fftshift(abs(fft(signal)));
xf =linspace(0,1950000000,length(signal));
plot(xf,signal);

