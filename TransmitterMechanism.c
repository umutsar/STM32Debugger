#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 512

void CDC_Transmit_FS(uint8_t *buffer, int len)
{
    printf("%s", buffer);
}

char log_buffer[BUFFER_SIZE];
int log_length = 0;

void log_variable(const char *name, unsigned int value)
{
    int len = snprintf(log_buffer + log_length, BUFFER_SIZE - log_length,
                       "%s: %u,", name, value);
    log_length += len;
}

#define LOG_VAR(v) log_variable(#v, v)

void LOG_POST()
{
    if (log_length > 0)
    {
        log_buffer[log_length - 1] = '\n';
        CDC_Transmit_FS((uint8_t *)log_buffer, log_length);
    }

    log_length = 0;
    log_buffer[0] = '\0';
}

int main()
{
    unsigned int value1 = 12;
    unsigned int value2 = 42;
    unsigned int value3 = 429;

    LOG_VAR(value1);
    LOG_VAR(value2);
    LOG_VAR(value3);

    LOG_POST();

    LOG_VAR(value1);
    LOG_VAR(value2);
    LOG_VAR(value3);

    LOG_POST();

    return 0;
}
