/*********************************************************
* Program : DES Algotrithm
* Author  : Liang Junhua
* Date    : 2018/10/25
*********************************************************/ 

#ifndef _DESALGORITHM_
#define _DESALGORITHM_
#include <vector>
#include <string>
#include <map>
using namespace std;

class DES_Algorithm {
public:
    /* Contrustor and deconstructor, initialize all the displace table */
    DES_Algorithm();
    ~DES_Algorithm();

    /* Call for the encryption and decrption according to particular text and key. */
    string des_encryption_process(string plaintext, string key);    /* Return a ciphertext. */
    string des_decryption_process(string ciphertext, string key);   /* Return a plaintext.  */

    /* Overall struction of the des encryption. */
    string IP_initial_displace(string text);
    string T_recursion(string text, vector<string> subKey);
    string T_INV_recursion(string text, vector<string> subKey);
    string W_swap_displace(string text);
    string IP_INV_displace(string text);
private:
    /* All the displace table in specific table. */
    vector<int> IP_TABLE;
    vector<int> IP_INV_TABLE;
    vector<int> ENC_EXTEND_TABLE;
    vector<int> S_BOX_TABLE[8];
    vector<int> P_DISPLACE_TABLE;
    vector<int> PC_ONE_DISPLACE_TABLE;
    vector<int> PC_TWO_COMPRESS_TABLE;

    /* Turn from binary to decimal */
    string DTOB_Table[16];
    map<string, int> BTOD_Table;

    /* Auxiliary function. */
    vector<string> produce_subkey(string key);                              /* Produce subkeys for specific key */
    string xOR(string a, string b);                                         /* XOR function for two string.     */
    string table_transform(string text, vector<int> TABLE);                 /* Implement displace               */
    string Feistel(string R, string sub_key);                               /* DES's Feistel function           */
};

#endif //_DESALGORITHM_