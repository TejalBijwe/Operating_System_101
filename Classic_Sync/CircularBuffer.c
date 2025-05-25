#include<stdio.h>
#include<stdint.h>

#define BUFFER_SIZE 8

typedef struct 
{
    uint8_t buffer[BUFFER_SIZE];
    int head;
    int tail;
} CircularBuffer;



void initBuffer(CircularBuffer *cb)
{
    cb-> head = 0;
    cb-> tail = 0; 
}
void writeBuffer(CircularBuffer *cb, uint8_t data)
{
    cb ->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
}
uint8_t readBuffer(CircularBuffer *cb)
{
    uint8_t data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    return data;
}

int main()
{
    CircularBuffer cb;
    initBuffer(&cb);

    printf("Writing value from the buffer: \n");
    for(uint8_t i = 1; i <= 7; i++)
    {
        printf("Write: %d\n", i);
        writeBuffer(&cb,i);
    }
    printf("\nRead value from buffers: \n");
    for(int i = 1; i < BUFFER_SIZE; i++)
    {
        uint8_t val = readBuffer(&cb);
        printf("Read: %d\n",val);
    }

    return 0;
}

