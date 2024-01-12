#include "stdio.h"
#include "math.h"
#include "stdlib.h"

int main()
{
    float x1[4] = {1, 1, 0, 0};
    float x2[4] = {1, 0, 1, 0};
    float t[4] = {1, 1, 1, 0};
    float b = 1;

    // Hidden layer 1
    float u01 = -0.3, u02 = 0.3, u03 = 0.3;
    float u11 = 0.2, u12 = 0.3, u13 = -0.1;
    float u21 = 0.3, u22 = 0.1, u23 = -0.1;

    // Hidden layer 2
    float v01 = 0.4, v02 = 0.2, v03 = -0.3;
    float v11 = 0.3, v12 = 0.2, v13 = -0.4;
    float v21 = 0.3, v22 = 0.2, v23 = 0.1;
    float v31 = 0.1, v32 = 0.3, v33 = 0.2;

    // Output layer
    float w01 = 0.5, w11 = -0.3, w21 = -0.4, w31 = 0.2;

    const float e = 2.7182;
    const float alpha = 0.8;

    int epoch = 0, max_iter = 10000;
    int i;
    while (epoch < max_iter)
    {
    	// perulangan sebanyak jumlah pasangan data (input dan target)
        for ( i = 0; i < 4; i++)
        {
        // Fase I: Propagasi Maju
	// Langkah 4: Hitung keluaran unit tersembunyi (zj)
	// ------------------------------------------------
            float z_in1 = b * u01 + x1[i] * u11 + x2[i] * u21;
            float z_in2 = b * u02 + x1[i] * u12 + x2[i] * u22;
            float z_in3 = b * u03 + x1[i] * u13 + x2[i] * u23;

            float z1 = 1 / (1 + pow(e, -z_in1));
            float z2 = 1 / (1 + pow(e, -z_in2));
            float z3 = 1 / (1 + pow(e, -z_in3));

            float z_in4 = b * v01 + z1 * v11 + z2 * v21 + z3 * v31;
            float z_in5 = b * v02 + z1 * v12 + z2 * v22 + z3 * v32;
            float z_in6 = b * v03 + z1 * v13 + z2 * v23 + z3 * v33;

            float z4 = 1 / (1 + pow(e, -z_in4));
            float z5 = 1 / (1 + pow(e, -z_in5));
            float z6 = 1 / (1 + pow(e, -z_in6));
            
        	// Langkah 5: Hitung keluaran unit yk
			// ----------------------------------
            float y_in1 = b * w01 + z4 * w11 + z5 * w21 + z6 * w31;
            float y1 = 1 / (1 + pow(e, -y_in1));

        	// Fase II : Propagasi Balik
	        // Langkah 6: Hitung faktor wteta di unit keluaran yk
	        // --------------------------------------------------
            float wteta = (t[i] - y1) * y1 * (1 - y1);
            
            // Hitung perubahan bobot wkj (dengan alpha=0.2)
		    // ---------------------------------------------
            float dw01 = alpha * wteta * b;
            float dw11 = alpha * wteta * z4;
            float dw21 = alpha * wteta * z5;
            float dw31 = alpha * wteta * z6;
            
            
			// Langkah 7: Hitung penjumlahan kesalahan dari unit tersembunyi (vteta_in)
			// ------------------------------------------------------------------------
            float vteta_in1 = wteta * w11;
            float vteta_in2 = wteta * w21;
            float vteta_in3 = wteta * w31;
            
        	// Faktor kesalahan vteta di unit tersembunyi:
			// -------------------------------------------
            float vteta1 = vteta_in1 * z4 * (1 - z4);
            float vteta2 = vteta_in2 * z5 * (1 - z5);
            float vteta3 = vteta_in3 * z6 * (1 - z6);

            float dv01 = alpha * vteta1 * b;
            float dv02 = alpha * vteta2 * b;
            float dv03 = alpha * vteta3 * b;
            float dv11 = alpha * vteta1 * z1;
            float dv12 = alpha * vteta2 * z1;
            float dv13 = alpha * vteta3 * z1;
            float dv21 = alpha * vteta1 * z2;
            float dv22 = alpha * vteta2 * z2;
            float dv23 = alpha * vteta3 * z2;
            float dv31 = alpha * vteta1 * z3;
            float dv32 = alpha * vteta2 * z3;
            float dv33 = alpha * vteta3 * z3;


			// Hitung perubahan bobot ke unit tersembunyi (dengan alpha=0.2):
            float du01 = alpha * vteta1 * b;
            float du02 = alpha * vteta2 * b;
            float du03 = alpha * vteta3 * b;
            float du11 = alpha * vteta1 * x1[i];
            float du12 = alpha * vteta2 * x1[i];
            float du13 = alpha * vteta3 * x1[i];
            float du21 = alpha * vteta1 * x2[i];
            float du22 = alpha * vteta2 * x2[i];
            float du23 = alpha * vteta3 * x2[i];

        	// Langkah 8: Hitung semua perubahan bobot
			// Perubahan bobot unit keluaran:
			// ---------------------------------------
            w01 += dw01;
            w11 += dw11;
            w21 += dw21;
            w31 += dw31;

            v01 += dv01;
            v02 += dv02;
            v03 += dv03;
            v11 += dv11;
            v12 += dv12;
            v13 += dv13;
            v21 += dv21;
            v22 += dv22;
            v23 += dv23;
            v31 += dv31;
            v32 += dv32;
            v33 += dv33;

            u01 += du01;
            u02 += du02;
            u03 += du03;
            u11 += du11;
            u12 += du12;
            u13 += du13;
            u21 += du21;
            u22 += du22;
            u23 += du23;
        }

        epoch++;
    }

    			
	// cetak nilai bobot setelah proses learning
	// -----------------------------------------
    printf("\nNilai bobot setelah proses belajar Backpropagation:\n");
    printf("w01: %.2f\n", w01);
    printf("w11: %.2f\n", w11);
    printf("w21: %.2f\n", w21);
    printf("w31: %.2f\n", w31);
    printf("v01: %.3f\n", v01);
    printf("v02: %.3f\n", v02);
    printf("v03: %.3f\n", v03);
    printf("v11: %.3f\n", v11);
    printf("v12: %.3f\n", v12);
    printf("v13: %.3f\n", v13);
    printf("v21: %.3f\n", v21);
    printf("v22: %.3f\n", v22);
    printf("v23: %.3f\n", v23);

    			
	// =========================================================
	// Bagian Testing
	// Bertujuan menguji bobot yang didapat pada proses training
	// apakah akurasinya sudah mendekati 100%
	// =========================================================
	
	// cetak tittle
    printf("\nBagian Testing\n\n");
    printf(" x1 x2  y\n");
    printf("---------\n");
    for ( i = 0; i < 4; i++)
    {
        // hitung z_in1, z_in2, z_in3 ---> untuk hidden layer 1
        float z_in1 = b * u01 + x1[i] * u11 + x2[i] * u21;
        float z_in2 = b * u02 + x1[i] * u12 + x2[i] * u22;
        float z_in3 = b * u03 + x1[i] * u13 + x2[i] * u23;
        
        // hitung z1, z2, z3 ---> untuk hidden layer 1
        float z1 = 1 / (1 + pow(e, -z_in1));
        float z2 = 1 / (1 + pow(e, -z_in2));
        float z3 = 1 / (1 + pow(e, -z_in3));
        
        // hitung z4, z5, z6 ---> untuk hidden layer 2
        float z_in4 = b * v01 + z1 * v11 + z2 * v21 + z3 * v31;
        float z_in5 = b * v02 + z1 * v12 + z2 * v22 + z3 * v32;
        float z_in6 = b * v03 + z1 * v13 + z2 * v23 + z3 * v33;
        
        // hitung z4, z5, z6 ---> untuk hidden layer 2
        float z4 = 1 / (1 + pow(e, -z_in4));
        float z5 = 1 / (1 + pow(e, -z_in5));
        float z6 = 1 / (1 + pow(e, -z_in6));
        
        // hitung y_in1
        float y_in1 = b * w01 + z4 * w11 + z5 * w21 + z6 * w31;
        float y1 = 1 / (1 + pow(e, -y_in1));
        
        // hitung y1
        int output = (y1 >= 0.5) ? 1 : 0;

        // Cetak hasil
        printf(" %2.0f %2.0f %d\n", x1[i], x2[i], output);
    }

    // Cetak footer
    printf("---------\n");

    return 0;
}
