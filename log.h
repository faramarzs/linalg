#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

void debug(const char *fmt, ...);
void warn(const char *fmt, ...);
void error(const char *fmt, ...);
void fatal(const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif /* LOG_H */
