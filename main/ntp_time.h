#ifndef NTP_TIME_H
#define NTP_TIME_H

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

void ntp_time_init();
void ntp_time_deinit();
time_t ntp_time_get();

#ifdef __cplusplus
}
#endif

#endif // NTP_TIME_H
