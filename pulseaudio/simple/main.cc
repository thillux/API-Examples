#include <iostream>
#include <cstdlib>
#include <pulse/simple.h>
#include <cstring>

const unsigned int SAMPLING_RATE = 8000;
const float MAX_AMPLITUDE = 100.0f;
const int NUM_OF_CHANNELS = 1;
bool terminate = false;

pa_simple* init_pulse_simple(void) {
  pa_simple* s;
  pa_sample_spec ss;
  ss.format = PA_SAMPLE_S16LE;
  ss.channels = NUM_OF_CHANNELS;
  ss.rate = SAMPLING_RATE;
  s = pa_simple_new(NULL, // Use the default server.
      "Test App", // Our application's name.
      PA_STREAM_PLAYBACK,
      NULL, // Use the default device.
      "Test Stream", // Description of our stream.
      &ss,  // Our sample format.
      NULL, // Use default channel map
      NULL, // Use default buffering attributes.
      NULL  // Ignore error code.
      );
  return s;
}

void destroy_pulse_simple(pa_simple* s) {
  pa_simple_free(s);
}

void sig_int_handler(int) {
  terminate = true;
}

int main (void) {
  signal(SIGINT, sig_int_handler);

  pa_simple* s = init_pulse_simple();
  
  uint8_t* buf = new uint8_t[SAMPLING_RATE * NUM_OF_CHANNELS];
  memset(buf, '\0', sizeof(uint8_t) * SAMPLING_RATE * NUM_OF_CHANNELS);

  for(unsigned long t = 0; !terminate; ++t) {
    buf[t % (SAMPLING_RATE * NUM_OF_CHANNELS)] =
      ((t*9 & t >> 4) |
      (t*5 & t >> 7)  |
      (t*3 & t/0x400))
      - 1
    ;

      if (t % SAMPLING_RATE * NUM_OF_CHANNELS == 0) {
        pa_simple_write(s, buf, SAMPLING_RATE * NUM_OF_CHANNELS, NULL);
      }
  }

  std::cout << "terminating" << std::endl;
  delete buf;
  
  destroy_pulse_simple(s);
    
  return EXIT_SUCCESS;
}
