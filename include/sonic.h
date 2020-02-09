#ifndef SONIC
#define SONIC
    #include <Arduino.h>
    #include "pinout.h"
    #define constSonicTimeToCM 58
    #define SONIC_ERROR_CODE -1
    class Sonic{
        private:
            static Sonic * instance_;
            time_t start_time;
            time_t end_time;
            int max_distance = 200;
            int min_distance = 2;
            bool finished;
            static Sonic* instance(){return instance_;};
        public:
            Sonic();
            void sendImpulse();
            int getDistanceInCM();
            static void intteruptEchoPin();
            void attachSonic();
        };
    


#endif