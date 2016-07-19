#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define frand() ((double)rand() / (RAND_MAX+1.0))
/* good enough for our purposes */
#define frandrange(min, max) (int)round((frand() * (max - min)) + min)

typedef int isupper_implementation(char c);

char get_random_char();
void run_test(isupper_implementation);
int isupper_moretime(char c);
int isupper_morespace(char c);
void initialize_map();

int main(int argc, char *argv[])
{
  if (argc == 1) {
    printf("Please specify time or space.\n");
    return -1;
  }

  switch(argv[1][0]) {
    case 's':
      printf("Takes more space.\n");
      initialize_map();
      run_test(isupper_morespace);
      break;
    case 't':
      printf("Takes more time.\n");
      run_test(isupper_moretime);
      break;
      break;
    default:
      printf("Unknown test type.\n");
      return -2;
  }

  printf("done!\n");
}

void run_test(isupper_implementation imp)
{
  char current_char;

  for(int i = 0; i < 10000000; i++) {
    current_char = get_random_char();
    imp(current_char);
  }

  return;
}

int isupper_moretime(char c)
{
  return (c >= 65 && c <= 90);
}

#define MAXCHAR 300
bool map[MAXCHAR];

int isupper_morespace(char c)
{
  int d = (int)c;

  if (d > MAXCHAR)  {
    printf("Unsupported char with code %d\n", d);
    exit(-1);
  }

  return map[d];
}

void initialize_map()
{
  map[0] = false;
  map[1] = false;
  map[2] = false;
  map[3] = false;
  map[4] = false;
  map[5] = false;
  map[6] = false;
  map[7] = false;
  map[8] = false;
  map[9] = false;
  map[10] = false;
  map[11] = false;
  map[12] = false;
  map[13] = false;
  map[14] = false;
  map[15] = false;
  map[16] = false;
  map[17] = false;
  map[18] = false;
  map[19] = false;
  map[20] = false;
  map[21] = false;
  map[22] = false;
  map[23] = false;
  map[24] = false;
  map[25] = false;
  map[26] = false;
  map[27] = false;
  map[28] = false;
  map[29] = false;
  map[30] = false;
  map[31] = false;
  map[32] = false;
  map[33] = false;
  map[34] = false;
  map[35] = false;
  map[36] = false;
  map[37] = false;
  map[38] = false;
  map[39] = false;
  map[40] = false;
  map[41] = false;
  map[42] = false;
  map[43] = false;
  map[44] = false;
  map[45] = false;
  map[46] = false;
  map[47] = false;
  map[48] = false;
  map[49] = false;
  map[50] = false;
  map[51] = false;
  map[52] = false;
  map[53] = false;
  map[54] = false;
  map[55] = false;
  map[56] = false;
  map[57] = false;
  map[58] = false;
  map[59] = false;
  map[60] = false;
  map[61] = false;
  map[62] = false;
  map[63] = false;
  map[64] = false;
  map[65] = true;
  map[66] = true;
  map[67] = true;
  map[68] = true;
  map[69] = true;
  map[70] = true;
  map[71] = true;
  map[72] = true;
  map[73] = true;
  map[74] = true;
  map[75] = true;
  map[76] = true;
  map[77] = true;
  map[78] = true;
  map[79] = true;
  map[80] = true;
  map[81] = true;
  map[82] = true;
  map[83] = true;
  map[84] = true;
  map[85] = true;
  map[86] = true;
  map[87] = true;
  map[88] = true;
  map[89] = true;
  map[90] = true;
  map[91] = true;
  map[92] = true;
  map[93] = true;
  map[94] = true;
  map[95] = true;
  map[96] = true;
  map[97] = true;
  map[98] = false;
  map[99] = false;
  map[100] = false;
  map[101] = false;
  map[102] = false;
  map[103] = false;
  map[104] = false;
  map[105] = false;
  map[106] = false;
  map[107] = false;
  map[108] = false;
  map[109] = false;
  map[110] = false;
  map[111] = false;
  map[112] = false;
  map[113] = false;
  map[114] = false;
  map[115] = false;
  map[116] = false;
  map[117] = false;
  map[118] = false;
  map[119] = false;
  map[120] = false;
  map[121] = false;
  map[122] = false;
  map[123] = false;
  map[124] = false;
  map[125] = false;
  map[126] = false;
  map[127] = false;
  map[128] = false;
  map[129] = false;
  map[130] = false;
  map[131] = false;
  map[132] = false;
  map[133] = false;
  map[134] = false;
  map[135] = false;
  map[136] = false;
  map[137] = false;
  map[138] = false;
  map[139] = false;
  map[140] = false;
  map[141] = false;
  map[142] = false;
  map[143] = false;
  map[144] = false;
  map[145] = false;
  map[146] = false;
  map[147] = false;
  map[148] = false;
  map[149] = false;
  map[150] = false;
  map[151] = false;
  map[152] = false;
  map[153] = false;
  map[154] = false;
  map[155] = false;
  map[156] = false;
  map[157] = false;
  map[158] = false;
  map[159] = false;
  map[160] = false;
  map[161] = false;
  map[162] = false;
  map[163] = false;
  map[164] = false;
  map[165] = false;
  map[166] = false;
  map[167] = false;
  map[168] = false;
  map[169] = false;
  map[170] = false;
  map[171] = false;
  map[172] = false;
  map[173] = false;
  map[174] = false;
  map[175] = false;
  map[176] = false;
  map[177] = false;
  map[178] = false;
  map[179] = false;
  map[180] = false;
  map[181] = false;
  map[182] = false;
  map[183] = false;
  map[184] = false;
  map[185] = false;
  map[186] = false;
  map[187] = false;
  map[188] = false;
  map[189] = false;
  map[190] = false;
  map[191] = false;
  map[192] = false;
  map[193] = false;
  map[194] = false;
  map[195] = false;
  map[196] = false;
  map[197] = false;
  map[198] = false;
  map[199] = false;
  map[200] = false;
  map[201] = false;
  map[202] = false;
  map[203] = false;
  map[204] = false;
  map[205] = false;
  map[206] = false;
  map[207] = false;
  map[208] = false;
  map[209] = false;
  map[210] = false;
  map[211] = false;
  map[212] = false;
  map[213] = false;
  map[214] = false;
  map[215] = false;
  map[216] = false;
  map[217] = false;
  map[218] = false;
  map[219] = false;
  map[220] = false;
  map[221] = false;
  map[222] = false;
  map[223] = false;
  map[224] = false;
  map[225] = false;
  map[226] = false;
  map[227] = false;
  map[228] = false;
  map[229] = false;
  map[230] = false;
  map[231] = false;
  map[232] = false;
  map[233] = false;
  map[234] = false;
  map[235] = false;
  map[236] = false;
  map[237] = false;
  map[238] = false;
  map[239] = false;
  map[240] = false;
  map[241] = false;
  map[242] = false;
  map[243] = false;
  map[244] = false;
  map[245] = false;
  map[246] = false;
  map[247] = false;
  map[248] = false;
  map[249] = false;
  map[250] = false;
  map[251] = false;
  map[252] = false;
  map[253] = false;
  map[254] = false;
  map[255] = false;
  map[256] = false;
  map[257] = false;
  map[258] = false;
  map[259] = false;
  map[260] = false;
  map[261] = false;
  map[262] = false;
  map[263] = false;
  map[264] = false;
  map[265] = false;
  map[266] = false;
  map[267] = false;
  map[268] = false;
  map[269] = false;
  map[270] = false;
  map[271] = false;
  map[272] = false;
  map[273] = false;
  map[274] = false;
  map[275] = false;
  map[276] = false;
  map[277] = false;
  map[278] = false;
  map[279] = false;
  map[280] = false;
  map[281] = false;
  map[282] = false;
  map[283] = false;
  map[284] = false;
  map[285] = false;
  map[286] = false;
  map[287] = false;
  map[288] = false;
  map[289] = false;
  map[290] = false;
  map[291] = false;
  map[292] = false;
  map[293] = false;
  map[294] = false;
  map[295] = false;
  map[296] = false;
  map[297] = false;
  map[298] = false;
  map[299] = false;
}

char get_random_char()
{
  return frandrange(65, 90) + (32 * frandrange(0, 1));
}
