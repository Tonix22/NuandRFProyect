
csv = load('rx.csv');
signal_i = csv(:, 1) ./ 2048.0;
signal_q = csv(:, 2) ./ 2048.0;
signal   = signal_i + 1j .* signal_q;

%frequency axis creation
fs       = 61e6;
M=length(signal);
t_o=M/fs;
t=0:1/fs:t_o;
f_axis=(-fs/2):(1/t_o):(fs/2);
f_axis=f_axis+950e6;
%f_axis   = linspace(-fs/2,fs/2,(1/t_o));


% Plot the magnitude of the signal in the time domain
signal = fftshift(abs(fft([0;signal])));
%plot(signal);
semilogy(f_axis,signal);
%plot(f_axis,signal);

