#ifndef MY_CAPTURE_H
#define MY_CAPTURE_H

#define BUFF_SIZE 1024

/* --- capture stdout --- */
int start_capture_stdout(void);
char *close_capture_stdout(void);

/* --- capture stderr --- */
int start_capture_sterr(void);
char *char *close_capture_sterr(void);

#endif /* MY_CAPTURE_H */
