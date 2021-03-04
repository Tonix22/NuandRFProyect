#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#define TEST (1)
#define FREQUENCY  (0)
#define GAIN       (0)
#define BANDWIDHT  (0)
#define SAMPLERATE (0)  
#define AUTOGAIN   (1)

#define ms_us(T) T*1000
#define MEGA(T)  T*1000000 

#define FREQ         950000000
#define SAMPLE_RATE  MEGA(61)
#define BANDWIDTH_RX 200000
#define BANDWIDHT_TX 56000000

#define rx_TIME ms_us(2000)


#endif