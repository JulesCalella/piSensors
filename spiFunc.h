// Function Prototypes
int setUpSPI(int, int);
unsigned char XGAttached(int);
unsigned char MAttached(int);
void initializeXGM(int ssAG, int ssM);
int readAccZ(int ss);
int readAccY(int ss);
int readAccX(int ss);
int readGyroZ(int ss);
int readGyroY(int ss);
int readGyroX(int ss);
int readMagZ(int ss);
int readMagY(int ss);
int readMagX(int ss);
void unitValues(int ssAG, int ssM);
