extern const char* ntpServer;
extern const long  gmtOffset_sec;
extern const int   daylightOffset_sec;

void printLocalTime();
void setupClock();
void printTime();