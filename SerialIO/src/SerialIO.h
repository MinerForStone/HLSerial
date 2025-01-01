#define HEADER_SIZE 4

void setupDataBuffer(unsigned char size);
void send();
void writeLong(unsigned char pos, long value);
void writeByte(unsigned char pos, char value);
