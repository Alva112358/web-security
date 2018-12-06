/*********************************************************
* Program : DES Algotrithm
* Author  : Liang Junhua
* Date    : 2018/10/25
*********************************************************/ 
#include "DES.h"

/* Constructor initialize all the displace talbe. */
DES_Algorithm::DES_Algorithm() {
    printf("\n\n->Initializing the displace tables...\n");

    IP_TABLE = vector<int> {
        58, 50, 42, 34, 26, 18, 10, 2, 
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9,  1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

    IP_INV_TABLE = vector<int> {
        40,  8, 48, 16, 56, 24, 64, 32,
        39,  7, 47, 15, 55, 23, 63, 31,
        38,  6, 46, 14, 54, 22, 62, 30,
        37,  5, 45, 13, 53, 21, 61, 29,
        36,  4, 44, 12, 52, 20, 60, 28,
        35,  3, 43, 11, 51, 19, 59, 27,
        34,  2, 42, 10, 50, 18, 58, 26,
        33,  1, 41,  9, 49, 17, 57, 25
    };

    ENC_EXTEND_TABLE = vector<int> {
        32,  1,  2,  3,  4,  5,
         4,  5,  6,  7,  8,  9,
         8,  9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
    };

    S_BOX_TABLE[0] = vector<int> {
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
        0, 15,  7,  4, 15,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
        4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
    };

    S_BOX_TABLE[1] = vector<int> {     
        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
         3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
         0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
    };

    S_BOX_TABLE[2] = vector<int> {
        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
         1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
    };

    S_BOX_TABLE[3] = vector<int> { 
         7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        12,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
         3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14       
    };

    S_BOX_TABLE[4] = vector<int> {
         2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
         4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
    };

    S_BOX_TABLE[5] = vector<int> {
        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
         9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
         4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
    };

    S_BOX_TABLE[6] = vector<int> {
         4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
         1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
         6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
    };

    S_BOX_TABLE[7] = vector<int> {
        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
         1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
         7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
         2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
    };

    P_DISPLACE_TABLE = vector<int> {
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
    };

    PC_ONE_DISPLACE_TABLE = vector<int> {
        57, 49, 41, 33, 25, 17,  9,
         1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
    };

    PC_TWO_COMPRESS_TABLE = vector<int> {
        14, 17, 11, 24,  1,  5,
         3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32        
    };

    DTOB_Table[0]  = "0000";
    DTOB_Table[1]  = "0001";
    DTOB_Table[2]  = "0010";
    DTOB_Table[3]  = "0011";
    DTOB_Table[4]  = "0100";
    DTOB_Table[5]  = "0101";
    DTOB_Table[6]  = "0110";
    DTOB_Table[7]  = "0111";
    DTOB_Table[8]  = "1000";
    DTOB_Table[9]  = "1001";
    DTOB_Table[10] = "1010";
    DTOB_Table[11] = "1011";
    DTOB_Table[12] = "1100";
    DTOB_Table[13] = "1101";
    DTOB_Table[14] = "1110";
    DTOB_Table[15] = "1111";

    BTOD_Table.insert(make_pair("0000", 0));
    BTOD_Table.insert(make_pair("0001", 1));
    BTOD_Table.insert(make_pair("0010", 2));
    BTOD_Table.insert(make_pair("0011", 3));
    BTOD_Table.insert(make_pair("0100", 4));
    BTOD_Table.insert(make_pair("0101", 5));
    BTOD_Table.insert(make_pair("0110", 6));
    BTOD_Table.insert(make_pair("0111", 7));
    BTOD_Table.insert(make_pair("1000", 8));
    BTOD_Table.insert(make_pair("1001", 9));
    BTOD_Table.insert(make_pair("1010", 10));
    BTOD_Table.insert(make_pair("1011", 11));
    BTOD_Table.insert(make_pair("1100", 12));
    BTOD_Table.insert(make_pair("1101", 13));
    BTOD_Table.insert(make_pair("1110", 14));
    BTOD_Table.insert(make_pair("1111", 15));

    printf("->Initializing the displace tables is completed\n\n\n");
}

DES_Algorithm::~DES_Algorithm() {
    printf("->Thank you for using this des algorithm!\n");
}


/* The encryption process of plaintext, return a ciphertext. */
string DES_Algorithm::des_encryption_process(string plaintext, string key) {
    printf("->Start the encryption...\n");

    /* A 64bits plaintext turn to 64bits ciphertext. */
    string ciphertext;        /* The ciphertext produced by this plaintext. */
    vector<string> subKey;    /* The subkey to this key. */

    /* Encryption */
    //printf("%s\n", key.c_str());
    subKey = produce_subkey(key);
    ciphertext = IP_initial_displace(plaintext);
    ciphertext = T_recursion(ciphertext, subKey);
    ciphertext = W_swap_displace(ciphertext);
    ciphertext = IP_INV_displace(ciphertext);

    printf("->Finish encryption\n\n\n");
    /* Return this ciphertext. */
    return ciphertext;
}


/* The decryption process of ciphertext, return a plaintext. */
string DES_Algorithm::des_decryption_process(string ciphertext, string key) {
    printf("->Start the decryption...\n");

    /* A 64bits ciphertext turn to 64bits plaintext. */
    string plaintext;         /* The plaintext produced by this ciphertext. */
    vector<string> subKey;    /* The subkey to this key. */

    /* Decryption */
    subKey = produce_subkey(key);
    plaintext = IP_initial_displace(ciphertext);
    plaintext = T_INV_recursion(plaintext, subKey);
    plaintext = W_swap_displace(plaintext);
    plaintext = IP_INV_displace(plaintext);

    printf("->Finish decryption\n\n\n");
    /* Return this plaintext. */
    return plaintext;
}


/* IP displace of the text. */
string DES_Algorithm::IP_initial_displace(string text) {
    printf("->Start to ip displace...\n");
    string result = table_transform(text, IP_TABLE);
    printf("->Ip displace complete!\n");
    return result;
}


/* T recursion that is used in encryption. */
string DES_Algorithm::T_recursion(string text, vector<string> subKey) {
    printf("->Start T recursion...\n");
    /* text = L0+R0 */
    string L0 = text.substr(0,  32);
    string R0 = text.substr(32, 32);
    string Li = L0;
    string Ri = R0;
    string result;
    //printf("->L0 :%s\n", L0.c_str());
    //printf("->R0 :%s\n", R0.c_str());
    for (int i = 0; i < 16; i++) {
        string feistel_result = Feistel(Ri, subKey[i]);
        //printf("->Feistel result:%s\n", feistel_result.c_str());
        string new_Li = Ri;
        string new_Ri = xOR(Li, feistel_result);
        Ri = new_Ri;
        Li = new_Li;
        //printf("->L%-2d:%s\n", i+1, Li.c_str());
        //printf("->R%-2d:%s\n", i+1, Ri.c_str());
    }
    result = Li + Ri;
    printf("->Finish T recursion!\n");
    return result;
}


/* T inverse recursion that is used in decryption. */
string DES_Algorithm::T_INV_recursion(string text, vector<string> subKey) {
    printf("->Start T-reverse recursion...\n");
    /* text = L0+R0 */
    string L0 = text.substr(0,  32);
    string R0 = text.substr(32, 32);
    string Li = L0;
    string Ri = R0;
    string result;
    for (int i = 15; i >= 0; i--) {
        string feistel_result = Feistel(Ri, subKey[i]);
        string new_Li = Ri;
        string new_Ri = xOR(Li, feistel_result);
        Ri = new_Ri;
        Li = new_Li;
    }
    result = Li + Ri;
    printf("->Finish T-reverse recursion!\n");
    return result;
}


/* Swap the high 32bits and the low 32bits. */
string DES_Algorithm::W_swap_displace(string text) {
    printf("->Start swap displace...\n");
    string result = text.substr(32, 32) + text.substr(0, 32);
    printf("->Swap complete!\n");
    return result;
}


/* IP inverse displace of the text. */
string DES_Algorithm::IP_INV_displace(string text) {
    printf("->Start ip-inverse displace...\n");
    string result = table_transform(text, IP_INV_TABLE);
    printf("->Finish ip-inverse displace!\n");
    return result;
}


/*--------------------------------Auxiliary Function--------------------------------*/
/* Produce a particular key's subkey. */
vector<string> DES_Algorithm::produce_subkey(string key) {
    printf("->Start to produce the subkey...\n");
    key = table_transform(key, PC_ONE_DISPLACE_TABLE);
    vector<string> subKey;
    string valid_key;

    /* Valid_key is 56bits. */
    for (int i = 0; i < key.size(); i++) {
        if (!(i+1 == 8*(i+1))) {
            valid_key += key[i];
        }
    }

    string C0 = valid_key.substr(0,  28);
    string D0 = valid_key.substr(28, 28);
    //printf("->C0:%s\n", C0.c_str());
    //printf("->D0:%s\n", D0.c_str());
    string Ci = C0;
    string Di = D0;

    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            string C_1 = Ci.substr(1);
            string D_1 = Di.substr(1);
            Ci = C_1 + Ci[0];
            Di = D_1 + Di[0];
        }
        else {
            string C_1 = Ci.substr(2);
            string D_1 = Di.substr(2);
            Ci = C_1 + Ci[0] + Ci[1];
            Di = D_1 + Di[0] + Di[1];
        }
        //printf("->C%2d:%s\n", i+1, Ci.c_str());
        //printf("->D%2d:%s\n", i+1, Di.c_str());
        subKey.push_back(table_transform(Ci+Di, PC_TWO_COMPRESS_TABLE));
        //printf("->SubKey%-2d: %s\n", i+1, subKey[i].c_str());
    }

    printf("->Complete producing the subkey\n");
    return subKey;
}


/* Feistel function in T recursion function. */
string DES_Algorithm::Feistel(string text, string sub_key) {
    /* Text is 32bits, and ENC_EXTEND_TABLE is 48bits */
    string enc_r_text = table_transform(text, ENC_EXTEND_TABLE);
    enc_r_text = xOR(enc_r_text, sub_key);
    //printf("->E(R0):%s\n", enc_r_text.c_str());
    string result;

    /* Divide enc_r_text into 8 parts, and each str is 4bits. */
    for (int i = 0; i < 8; i++) {
        string rows = "00";
        string cols; 
        for (int j = 0; j < 6; j++) {
            if (j == 0 || j == 5) {
                rows += enc_r_text[i*6+j];
            }
            else {
                cols += enc_r_text[i*6+j];
            }
        }
        //printf("->Row:%s\n", rows.c_str());
        //printf("->Col:%s\n", cols.c_str());

        int row = BTOD_Table[rows];
        int col = BTOD_Table[cols];
        
        int pos = row*16 + col;
        //printf("->%d\n", S_BOX_TABLE[i][pos]);
        result += DTOB_Table[S_BOX_TABLE[i][pos]];
    }

    //printf("->C=%s\n", result.c_str());
    //printf("->P=%s\n", table_transform(result, P_DISPLACE_TABLE).c_str());

    /* Result is 32bits. */
    return table_transform(result, P_DISPLACE_TABLE);
}


/* Xor process of two string. */
string DES_Algorithm::xOR(string a, string b) {
    if (a.length() != b.length()) {
        fprintf(stderr, "->string %s length is not the same as %s\n", a.c_str(), b.c_str());
        exit(1);
    }

    string temp = a;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == b[i]) temp[i] = '0';
        else temp[i] = '1';
    }

    return temp;
}


/* Transform text into some format in TABLE. */
string DES_Algorithm::table_transform(string text, vector<int> TABLE) {
    string temp;
    temp.resize(TABLE.size(), '0');

    for (int i = 0; i < TABLE.size(); i++) {
        temp[i] = text[TABLE[i]-1];
    }

    return temp;
}
/*--------------------------------Auxiliary Function--------------------------------*/