#ifndef _MD5_
#define _MD5_

#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

#define BIT_PER_BYTE 8
#define BIT_PER_GROUP 512
#define BIT_OF_LENGTH 64

unsigned int A = 0x67452301;
unsigned int B = 0xefcdab89;
unsigned int C = 0x98badcfe;
unsigned int D = 0x10325476;

unsigned int T[64] = { 
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 
};

unsigned int S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

class MD5 {
public:
    MD5(string Message);
    string fillData(string dataIn, unsigned int dataInSize);                             // Step1: fill data.
    vector< vector<unsigned int> > divideBlock(string dataIn, unsigned int dataInSize);  // Step2: divide data into blocks.
    vector<unsigned int> initAndCompression(vector< vector<unsigned int> > bitData);     // Step3: init buffer and compress.
    string getMD5Result(vector<unsigned int> buffer);                                    // Step4: decode the result.
private:
    string MD5Code;
    unsigned int F(unsigned int X, unsigned int Y, unsigned int Z);
    unsigned int G(unsigned int X, unsigned int Y, unsigned int Z);
    unsigned int H(unsigned int X, unsigned int Y, unsigned int Z);
    unsigned int I(unsigned int X, unsigned int Y, unsigned int Z);
    void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T);
    void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T);
    void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T);
    void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T);
    unsigned int shiftLeft(unsigned int X, unsigned int n);
};

// Basic auxiliary function.
unsigned int MD5::F(unsigned int X, unsigned int Y, unsigned int Z) {
    return (X & Y) | ((~X) & Z);
}
unsigned int MD5::G(unsigned int X, unsigned int Y, unsigned int Z) {
    return (X & Z) | (Y & (~Z));
}
unsigned int MD5::H(unsigned int X, unsigned int Y, unsigned int Z) {
    return (X ^ Y ^ Z);
}
unsigned int MD5::I(unsigned int X, unsigned int Y, unsigned int Z) {
    return (Y ^ (X | ~Z));
}
unsigned int MD5::shiftLeft(unsigned int X, unsigned int n) {
    return (X << n) | (X >> (32-n));
}
void MD5::FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T) {
    a = shiftLeft(a + F(b, c, d) + X + T, S) + b;
}
void MD5::GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T) {
    a = shiftLeft(a + G(b, c, d) + X + T, S) + b;
}
void MD5::HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T) {
    a = shiftLeft(a + H(b, c, d) + X + T, S) + b;
}
void MD5::II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int X, unsigned int S, unsigned int T) {
    a = shiftLeft(a + I(b, c, d) + X + T, S) + b;
}

MD5::MD5(string Message) {
    printf("Begin MD5 Algorithm...\n");
    string bitStream = fillData(Message, Message.size());                                // Step1: fill data.
    vector< vector<unsigned int> > bitData = divideBlock(bitStream, bitStream.size());   // Step2: divide data into blocks.
    vector<unsigned int> bitBuffer = initAndCompression(bitData);                        // Step3: init buffer and compress.
    string MD5Code = getMD5Result(bitBuffer);                                            // Step4: decode the result.
    // cout << MD5Code << endl;
    printf("The MD5 Code: %s\n", MD5Code.c_str());
    printf("MD5 Algorithm end! Thank you!\n");
}


// 1. fill data.
string MD5::fillData(string dataIn, unsigned int dataInSize) {
    printf("Start filling data...\n");
    string dataOut(dataIn);

    unsigned int bitOfData = dataInSize * BIT_PER_BYTE;
    unsigned int groupOfData = ceil(1.0 * bitOfData / BIT_PER_GROUP);
    unsigned int numOfMod = bitOfData % BIT_PER_GROUP;
    unsigned int numOfFill = BIT_PER_GROUP - BIT_OF_LENGTH - numOfMod;

    // Fill data, at least one 1.
    unsigned int byteOfFill = numOfFill / BIT_PER_BYTE;
    unsigned int byteOfLength = BIT_OF_LENGTH / BIT_PER_BYTE;
    for (int i = 0; i < byteOfFill; i++) {
        if (i == 0) dataOut += char(0x80);
        else dataOut += char(0x00);
    }

    // Message bit's length.
    bitset<64> dataLen(bitOfData);
    long long bitLen = dataLen.to_ullong();
    int count[8];
    for (int i = 0; i < 8; i++) {
        count[i] = (bitLen >> 8*i) & 0xff;
        dataOut += char(count[i]);
    }

    printf("Finish filling data!\n");
    return dataOut;
}

// 2. divide block.
vector< vector<unsigned int> > MD5::divideBlock(string dataIn, unsigned int dataInSize) {
    printf("Start dividing data into blocks...\n");
    unsigned int numOfBlock = dataInSize * 8 / BIT_PER_GROUP;
    vector< vector<unsigned int> > bitBlock(numOfBlock, vector<unsigned int>(16, 0));
    // For Blocks.
    for (int i = 0; i < numOfBlock; i++) {
        // For 16.
        for (int j = 0; j < 16; j++) {
            // For 32.
            // printf("%c %c %c %c\n", dataIn[i*64+j*4], dataIn[i*64+j*4+1], dataIn[i*64+j*4+2], dataIn[i*64+j*4+3]);
            unsigned int temp = (dataIn[i*64+j*4] & 0x000000ff) 
            | ((dataIn[i*64+j*4+1] << 8)  & 0x0000ff00) 
            | ((dataIn[i*64+j*4+2] << 16) & 0x00ff0000) 
            | ((dataIn[i*64+j*4+3] << 24) & 0xff000000);
            bitBlock[i][j] = temp;
        }
    }
    printf("Finish dividing data into blocks!\n");
    return bitBlock;
}

// 3. Buffer initialize & 4. Cyclic compression
vector<unsigned int> MD5::initAndCompression(vector< vector<unsigned int> > bitData) {
    printf("Start initializing buffer and cyclic compression...\n");
    vector<unsigned int> buffer {A, B, C, D};
    unsigned int a,b,c,d;

    // Cyclic compression.
    for (int i = 0; i < bitData.size(); i++) {
        a = buffer[0];
        b = buffer[1];
        c = buffer[2];
        d = buffer[3];

        // Round 1.
        FF(a, b, c, d, bitData[i][0],  S[0], T[0]);
        FF(d, a, b, c, bitData[i][1],  S[1], T[1]);
        FF(c, d, a, b, bitData[i][2],  S[2], T[2]);
        FF(b, c, d, a, bitData[i][3],  S[3], T[3]);
        FF(a, b, c, d, bitData[i][4],  S[4], T[4]);
        FF(d, a, b, c, bitData[i][5],  S[5], T[5]);
        FF(c, d, a, b, bitData[i][6],  S[6], T[6]);
        FF(b, c, d, a, bitData[i][7],  S[7], T[7]);
        FF(a, b, c, d, bitData[i][8],  S[8], T[8]);
        FF(d, a, b, c, bitData[i][9],  S[9], T[9]);
        FF(c, d, a, b, bitData[i][10], S[10], T[10]);
        FF(b, c, d, a, bitData[i][11], S[11], T[11]);
        FF(a, b, c, d, bitData[i][12], S[12], T[12]);
        FF(d, a, b, c, bitData[i][13], S[13], T[13]);
        FF(c, d, a, b, bitData[i][14], S[14], T[14]);
        FF(b, c, d, a, bitData[i][15], S[15], T[15]);

        // Round 2.
        GG(a, b, c, d, bitData[i][1], S[16], T[16]);
        GG(d, a, b, c, bitData[i][6], S[17], T[17]);
        GG(c, d, a, b, bitData[i][11], S[18], T[18]);
        GG(b, c, d, a, bitData[i][0], S[19], T[19]);
        GG(a, b, c, d, bitData[i][5], S[20], T[20]);
        GG(d, a, b, c, bitData[i][10], S[21], T[21]);
        GG(c, d, a, b, bitData[i][15], S[22], T[22]);
        GG(b, c, d, a, bitData[i][4], S[23], T[23]);
        GG(a, b, c, d, bitData[i][9], S[24], T[24]);
        GG(d, a, b, c, bitData[i][14], S[25], T[25]);
        GG(c, d, a, b, bitData[i][3], S[26], T[26]);
        GG(b, c, d, a, bitData[i][8], S[27], T[27]);
        GG(a, b, c, d, bitData[i][13], S[28], T[28]);
        GG(d, a, b, c, bitData[i][2], S[29], T[29]);
        GG(c, d, a, b, bitData[i][7], S[30], T[30]);
        GG(b, c, d, a, bitData[i][12], S[31], T[31]);

        // Round 3.
        HH(a, b, c, d, bitData[i][5], S[32], T[32]);
        HH(d, a, b, c, bitData[i][8], S[33], T[33]);
        HH(c, d, a, b, bitData[i][11], S[34], T[34]);
        HH(b, c, d, a, bitData[i][14], S[35], T[35]);
        HH(a, b, c, d, bitData[i][1], S[36], T[36]);
        HH(d, a, b, c, bitData[i][4], S[37], T[37]);
        HH(c, d, a, b, bitData[i][7], S[38], T[38]);
        HH(b, c, d, a, bitData[i][10], S[39], T[39]);
        HH(a, b, c, d, bitData[i][13], S[40], T[40]);
        HH(d, a, b, c, bitData[i][0], S[41], T[41]);
        HH(c, d, a, b, bitData[i][3], S[42], T[42]);
        HH(b, c, d, a, bitData[i][6], S[43], T[43]);
        HH(a, b, c, d, bitData[i][9], S[44], T[44]);
        HH(d, a, b, c, bitData[i][12], S[45], T[45]);
        HH(c, d, a, b, bitData[i][15], S[46], T[46]);
        HH(b, c, d, a, bitData[i][2], S[47], T[47]);      

        // Round 4.
        II(a, b, c, d, bitData[i][0], S[48], T[48]);
        II(d, a, b, c, bitData[i][7], S[49], T[49]);
        II(c, d, a, b, bitData[i][14], S[50], T[50]);
        II(b, c, d, a, bitData[i][5], S[51], T[51]);
        II(a, b, c, d, bitData[i][12], S[52], T[52]);
        II(d, a, b, c, bitData[i][3], S[53], T[53]);
        II(c, d, a, b, bitData[i][10], S[54], T[54]);
        II(b, c, d, a, bitData[i][1], S[55], T[55]);
        II(a, b, c, d, bitData[i][8], S[56], T[56]);
        II(d, a, b, c, bitData[i][15], S[57], T[57]);
        II(c, d, a, b, bitData[i][6], S[58], T[58]);
        II(b, c, d, a, bitData[i][13], S[59], T[59]);
        II(a, b, c, d, bitData[i][4], S[60], T[60]);
        II(d, a, b, c, bitData[i][11], S[61], T[61]);
        II(c, d, a, b, bitData[i][2], S[62], T[62]);
        II(b, c, d, a, bitData[i][9], S[63], T[63]);    

        buffer[0] += a;
        buffer[1] += b;
        buffer[2] += c;
        buffer[3] += d;  
    }

    printf("Finish initializing data!\n");
    return buffer;
}

// 5. Get the result.
string MD5::getMD5Result(vector<unsigned int> buffer) {
    printf("Start decoding the result...\n");
    string result;
    for (int i = 0; i < buffer.size(); i++) {
        int x1 = buffer[i] & 0xff;
        int x2 = (buffer[i] >> 8) & 0xff;
        int x3 = (buffer[i] >> 16) & 0xff;
        int x4 = (buffer[i] >> 24) & 0xff;
        // printf("%x %x %x %x\n", x1, x2, x3, x4);
        // result = result + x1 + x2 + x3 + x4;
        
        stringstream ss;
        string temp;
        ss << setfill('0') << setw(2) << hex << x1;
        ss << setfill('0') << setw(2) << hex << x2;
        ss << setfill('0') << setw(2) << hex << x3;
        ss << setfill('0') << setw(2) << hex << x4;
        ss >> temp;
        result += temp;
        
    }
    printf("Finish decoding data!\n");
    return result;
}

int main() {
    string message;
    printf("Please input the message: ");
    getline(cin, message);
    MD5 MD5Test(message);
    return 0;
}

#endif //_MD5_