#include "stdio.h"
#include "math.h"
#include "stdlib.h"

int main()
{
	// ==========================
	// Bagian Training/Learning
	// Bertujuan menghitung bobot
	// ==========================
	
	float x1[4]={ 1, 1, 0, 0};		// neuron masukkan x1 (masukkan boleh biner (1,0), boleh bipolar (1,-1))	
	float x2[4]={ 1, 0, 1, 0};		// neuron masukkan x2
	float  t[4]={ 0, 1, 1, 0};		// target (t) boleh biner / bipolar, sesuaikan apakah AND, OR, AND NOT, XOR
	float  b=1;						// bias, selalu bernilai 1
	float z_in1, z_in2, z_in3;
	float z_in4, z_in5, z_in6;
	float z_in7, z_in8, z_in9;
	float v01, v02, v03;
	float v11, v12, v13;
	float v21, v22, v23;
	float w01, w11, w21, w31;
	
	float v04, v05, v06;
	float v14, v15, v16;
	float v24, v25, v26;
	float w02, w12, w22, w32;
	
	float v07, v08, v09;
	float v17, v18, v19;
	float v27, v28, v29;
	float w03, w13, w23, w33;
	
	const float e=2.7182;
	float z1, z2, z3;
	float z4, z5, z6;
	float z7, z8, z9;
	float y_in, y_in1, y_in2, y_in3, y1;
	float wteta;
	const float alpha=0.8;
	
	float dv01, dv02, dv03, dv04, dv05, dv06, dv07, dv08, dv09;
	float dv11, dv12, dv13, dv14, dv15, dv16, dv17, dv18, dv19;
	float dv21, dv22, dv23, dv24, dv25, dv26, dv27, dv28, dv29;
	
	float dw01, dw11, dw21, dw31,
	dw02, dw12, dw22, dw32,
	dw03, dw13, dw23, dw33;
	
	float vteta_in1, vteta_in2, vteta_in3,
	vteta_in4, vteta_in5, vteta_in6, 
	vteta_in7, vteta_in8, vteta_in9;
	
	float vteta1, vteta2, vteta3,
	vteta4, vteta5, vteta6,
	vteta7, vteta8, vteta9;
	
	int epoch, max_iter;
	
	// inisialisasi bobot
	v01=-0.3;   // (double) rand() / RAND_MAX * 2.0 - 1.0;
	v02=0.3;
	v03=0.3;
	v11=0.2;
	v12=0.3;
	v13=-0.1;
	v21=0.3;
	v22=0.1;
	v23=-0.1;
	
	w01=-0.1;
	w11=0.5;
	w21=-0.3;
	w31=-0.4;
	
	// inisialisasi bobot untuk hidden layer 2;
	v04 = 0.4;
	v14 = 0.2;
	v24 = -0.3;
	v05 = 0.3;
	v15 = 0.2;
	v25 = -0.4;
	v06 = 0.3;
	v16 = 0.2;
	v26 = 0.1;
	
	w02 = 0.4;
	w12 = -0.3;
	w22 = 0.3;
	w32 = 0.1;
	
	// inisialisasi untuk keluaran
	v07 = 0.2;
	v17 = 0.4;
	v27 = -0.1;
	v08 = 0.3;
	v18 = 0.5;
	v28 = 0.2;
	v09 = -0.3;
	v19 = 0.4;
	v29 = 0.2;
	
	w03 = -0.3;
	w13 = 0.1;
	w23 = 0.3;
	w33 = 0.2;
	
	
	printf("Bagian Training/Learning\n\n");
	printf("Nilai bobot awal:\n");
	printf("w01: %.2f\n",w01);
	printf("w11: %.2f\n",w11);
	printf("w21: %.2f\n",w21);
	printf("w31: %.2f\n",w31);
	printf("v01: %.3f\n",v01);
	printf("v02: %.3f\n",v02);
	printf("v03: %.3f\n",v03);
	printf("v11: %.3f\n",v11);
	printf("v12: %.3f\n",v12);
	printf("v13: %.3f\n",v13);
	printf("v21: %.3f\n",v21);
	printf("v22: %.3f\n",v22);
	printf("v23: %.3f\n",v23);

	epoch=0;
	max_iter=1000;
	while (epoch<max_iter)
	{
			// perulangan sebanyak jumlah pasangan data (input dan target)
			int i;
			for (i=0; i<4; i++)
			{
				// Fase I: Propagasi Maju
				// Langkah 4: Hitung keluaran unit tersembunyi (zj)
				// ------------------------------------------------
				// langakh ?? : Hidden Layer 1
				z_in1=b*v01+x1[i]*v11+x2[i]*v21;
				z_in2=b*v02+x1[i]*v12+x2[i]*v22;
				z_in3=b*v03+x1[i]*v13+x2[i]*v23;
								
				//printf("%.2f\n",z_in1);
				//printf("%.2f\n",z_in2);
				//printf("%.2f\n",z_in3);

				// Penerapan fungsi aktivasi untuk hitung sinyal keluaran Hidden 1
				z1=1/(1+pow(e,-z_in1));
				z2=1/(1+pow(e,-z_in2));
				z3=1/(1+pow(e,-z_in3));
		
			    //printf("%.2f\n",z1);
				//printf("%.2f\n",z2);
				//printf("%.2f\n",z3);
				
				// Langkah ?? : Hidden Layer 2
				z_in4 = b*v04+x1[i]*v05+x2[i]*v06;
	            z_in5 = b*v14+x1[i]*v15+x2[i]*v16;
	            z_in6 = b*v24+x1[i]*v25+x2[i]*v26;
				
				// Penerapan fungsi aktivasi untuk hitung sinyal keluaran (Z1)
				z4=1/(1+pow(e,-z_in4));
				z5=1/(1+pow(e,-z_in5));
				z6=1/(1+pow(e,-z_in6));	
				
				// Penerapan fungsi aktivasi untuk hitung keluaran (ZZj)
				z_in7 = b*v07+x1[i]*v08+x2[i]*v09;
				z_in8 = b*v17+x1[i]*v18+x2[i]*v19;
				z_in9 = b*v27+x1[i]*v28+x2[i]*v29;
				
				// Penerapan fungsi aktivasi untuk keluaran ZZj
				z7 =1/(1+pow(e,-z_in7));
				z8 =1/(1+pow(e,-z_in8));
				z9 =1/(1+pow(e,-z_in9));
				
				//printf("%.2f\n",z1);
				//printf("%.2f\n",z2);
				//printf("%.2f\n",z3);
						
				// Langkah 5: Hitung keluaran unit yk
				// ----------------------------------
				
				y_in1=b*w01+z1*w11+z2*w21+z3*w31;
				y_in2=b*w02+z4*w12+z5*w22+z6*w32;
				y_in3=b*w03+z7*w13+z8*w23+z9*w33;
				
				y_in = y_in1 + y_in2 + y_in3;
				//printf("%.2f\n", y_in);
				y1=1/(1+pow(e,-y_in));
				
				// Fase II : Propagasi Balik
		        // Langkah 6: Hitung faktor wteta di unit keluaran yk
		        // --------------------------------------------------
		        
		        wteta=(t[i]-y1)*y1*(1-y1);
		        
		        // Hitung perubahan bobot wkj (dengan alpha=0.2)
		        // ---------------------------------------------
		        
		        dw01=alpha*wteta*b;
		        dw11=alpha*wteta*z1;
		        dw21=alpha*wteta*z2;
		        dw31=alpha*wteta*z3;
		        
		        dw02=alpha*wteta*b;
		        dw12=alpha*wteta*z4;
		        dw22=alpha*wteta*z5;
		        dw32=alpha*wteta*z6;
		        
		        dw03=alpha*wteta*b;
		        dw13=alpha*wteta*z7;
		        dw23=alpha*wteta*z8;
		        dw33=alpha*wteta*z9;
		        
		        //printf("%.2f\n",teta);
				//printf("%.2f\n",dw01);
				//printf("%.2f\n",dw11);
				//printf("%.2f\n",dw21);
				//printf("%.2f\n",dw31);
				
				// Langkah 7: Hitung penjumlahan kesalahan dari unit tersembunyi (vteta_in)
				// ------------------------------------------------------------------------
				
				vteta_in1=wteta*w11;
				vteta_in2=wteta*w21;
				vteta_in3=wteta*w31;
				
				vteta_in4=wteta*w12;
				vteta_in5=wteta*w22;
				vteta_in6=wteta*w32;
				
				vteta_in7=wteta*w13;
				vteta_in8=wteta*w23;
				vteta_in9=wteta*w33;
				
				// Faktor kesalahan vteta di unit tersembunyi:
				// -------------------------------------------
				
				vteta1=vteta_in1*z1*(1-z1);
				vteta2=vteta_in2*z2*(1-z2);
				vteta3=vteta_in3*z3*(1-z3);
				
				vteta4=vteta_in4*z4*(1-z4);
				vteta5=vteta_in5*z5*(1-z5);
				vteta6=vteta_in6*z6*(1-z6);
				
				vteta7=vteta_in7*z7*(1-z7);
				vteta8=vteta_in8*z8*(1-z8);
				vteta9=vteta_in9*z9*(1-z9);
				
				// printf("\nHAsil = %.2f",vteta1);
				// printf("\nHAsil = %.2f",vteta2);
				// printf("\nHasil = %.2f",vteta3);
				
				// Hitung perubahan bobot ke unit tersembunyi (dengan alpha=0.2):
				dv01=alpha*vteta1*b;
				dv02=alpha*vteta2*b;
				dv03=alpha*vteta3*b;
				dv04=alpha*vteta4*b;
				dv05=alpha*vteta5*b;
				dv06=alpha*vteta6*b;
				dv07=alpha*vteta7*b;
				dv08=alpha*vteta8*b;
				dv09=alpha*vteta9*b;
				
				dv11=alpha*vteta1*x1[i];
				dv12=alpha*vteta2*x1[i];
				dv13=alpha*vteta3*x1[i];
				dv14=alpha*vteta4*x1[i];
				dv15=alpha*vteta5*x1[i];
				dv16=alpha*vteta6*x1[i];
				dv17=alpha*vteta7*x1[i];
				dv18=alpha*vteta8*x1[i];
				dv19=alpha*vteta9*x1[i];
				
				dv21=alpha*vteta1*x2[i];
				dv22=alpha*vteta2*x2[i];
				dv23=alpha*vteta3*x2[i];
				dv24=alpha*vteta4*x2[i];
				dv25=alpha*vteta5*x2[i];
				dv26=alpha*vteta6*x2[i];
				dv27=alpha*vteta7*x2[i];
				dv28=alpha*vteta8*x2[i];
				dv29=alpha*vteta9*x2[i];
				
				// Langkah 8: Hitung semua perubahan bobot
				// Perubahan bobot unit keluaran:
				// ---------------------------------------
				
				w01=w01+dw01;
				w11=w11+dw11;
				w21=w21+dw21;
				w31=w31+dw31;
				
				w02=w02+dw02;
				w12=w12+dw12;
				w22=w22+dw22;
				w32=w32+dw32;
				
				w03=w03+dw03;
				w13=w13+dw13;
				w23=w23+dw23;
				w33=w33+dw33;
				
				v01=v01+dv01;
				v02=v02+dv02;
				v03=v03+dv03;
				v04=v04+dv04;
				v05=v05+dv05;
				v06=v06+dv06;
				v07=v07+dv07;
				v08=v08+dv08;
				v09=v09+dv09;
				
				v11=v11+dv11;
				v12=v12+dv12;
				v13=v13+dv13;
				v14=v14+dv14;
				v15=v15+dv15;
				v16=v16+dv16;
				v17=v17+dv17;
				v18=v18+dv18;
				v19=v19+dv19;
				
				v21=v21+dv21;
				v22=v22+dv22;
				v23=v23+dv23;
				v24=v24+dv24;
				v25=v25+dv25;
				v26=v26+dv26;
				v27=v27+dv27;
				v28=v28+dv28;
				v29=v29+dv29;
				
				
				//printf("%.2f\n",w01);
				//printf("%.2f\n",w11);
				//printf("%.2f\n",w21);
				//printf("%.2f\n",w31);
				
				//printf("%.3f\n",v01);
				//printf("%.3f\n",v02);
				//printf("%.3f\n",v03);
				//printf("%.3f\n",v11);
				//printf("%.3f\n",v12);
				//printf("%.3f\n",v13);
				//printf("%.3f\n",v21);
				//printf("%.3f\n",v22);
				//printf("%.3f\n",v23);
				
			}
			
		epoch++;
	}
			
			
	// cetak nilai bobot setelah proses learning
	// -----------------------------------------
	printf("\nNilai bobot setelah proses learning Backpropagation:\n");
	printf("w01: %.2f\n",w01);
	printf("w11: %.2f\n",w11);
	printf("w21: %.2f\n",w21);
	printf("w31: %.2f\n",w31);
	printf("v01: %.3f\n",v01);
	printf("v02: %.3f\n",v02);
	printf("v03: %.3f\n",v03);
	printf("v11: %.3f\n",v11);
	printf("v12: %.3f\n",v12);
	printf("v13: %.3f\n",v13);
	printf("v21: %.3f\n",v21);
	printf("v22: %.3f\n",v22);
	printf("v23: %.3f\n",v23);
			
			
	// =========================================================
	// Bagian Testing
	// Bertujuan menguji bobot yang didapat pada proses training
	// apakah akurasinya sudah mendekati 100%
	// =========================================================
	
	// cetak tittle
	printf("\nBagian Testing\n\n");
	printf(" x1 x2  y\n");
	printf("---------\n");
	int i;
	for (i=0; i<4; i++)
	{	
			// langakh ?? : Hidden Layer 1
				z_in1=b*v01+x1[i]*v11+x2[i]*v21;
				z_in2=b*v02+x1[i]*v12+x2[i]*v22;
				z_in3=b*v03+x1[i]*v13+x2[i]*v23;
								
				//printf("%.2f\n",z_in1);
				//printf("%.2f\n",z_in2);
				//printf("%.2f\n",z_in3);

				// Penerapan fungsi aktivasi untuk hitung sinyal keluaran Hidden 1
				z1=1/(1+pow(e,-z_in1));
				z2=1/(1+pow(e,-z_in2));
				z3=1/(1+pow(e,-z_in3));
		
			    //printf("%.2f\n",z1);
				//printf("%.2f\n",z2);
				//printf("%.2f\n",z3);
				
				// Langkah ?? : Hidden Layer 2
				z_in4 = b*v04+x1[i]*v05+x2[i]*v06;
	            z_in5 = b*v14+x1[i]*v15+x2[i]*v16;
	            z_in6 = b*v24+x1[i]*v25+x2[i]*v26;
				
				// Penerapan fungsi aktivasi untuk hitung sinyal keluaran (Z1)
				z4=1/(1+pow(e,-z_in4));
				z5=1/(1+pow(e,-z_in5));
				z6=1/(1+pow(e,-z_in6));	
				
				// Penerapan fungsi aktivasi untuk hitung keluaran (ZZj)
				z_in7 = b*v07+x1[i]*v08+x2[i]*v09;
				z_in8 = b*v17+x1[i]*v18+x2[i]*v19;
				z_in9 = b*v27+x1[i]*v28+x2[i]*v29;
				
				// Penerapan fungsi aktivasi untuk keluaran ZZj
				z7 =1/(1+pow(e,-z_in7));
				z8 =1/(1+pow(e,-z_in8));
				z9 =1/(1+pow(e,-z_in9));
				
				//printf("%.2f\n",z1);
				//printf("%.2f\n",z2);
				//printf("%.2f\n",z3);
						
				// Langkah 5: Hitung keluaran unit yk
				// ----------------------------------
				
				y_in1=b*w01+z1*w11+z2*w21+z3*w31;
				y_in2=b*w02+z4*w12+z5*w22+z6*w32;
				y_in3=b*w03+z7*w13+z8*w23+z9*w33;
				
				y_in = y_in1 + y_in2 + y_in3;
				//printf("%.2f\n", y_in);
				y1=1/(1+pow(e,-y_in));
		
		// cetak isi
		printf(" %2.0f %2.0f %2.0f\n",x1[i],x2[i],y1);	
		
	}
	
	// cetak footer
	printf("---------\n");
	
	return 0;
}

