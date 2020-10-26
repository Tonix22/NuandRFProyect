x = -10:0.1:10;
signal_i = square (pi);
signal_q = cos (x);
signal = signal_i + 1j .* signal_q;
% Plot the magnitude of the signal in the time domain
plot(abs(signal));
