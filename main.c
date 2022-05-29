#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HARF 150
#define SORUDOSYASI "sorular.txt"
#define CEVAPDOSYASI "cevaplar.txt"
#define YANLISCEVAPLARDOSYASI "yanlisCevaplar.txt"

// txt deki dosyalari okuyup bu structta atacak
typedef struct{
	char soru[HARF];
	char cevap[HARF];
	char yanlisCevap[2][HARF];
	
	
}soruVeCevap;

//Dosyalarýn var olup olmadýgýný kontrol eder
void dosyaKontrol(FILE* dosya){
	//dosya açýlýp açýlmadýðýný kontrol ediyor
	if(dosya==NULL){
		printf("Dosya Acilamiyor\n");
		exit(1);
	}
	
}

// Soru ve Cevaplar dosyasýný olusturmak için
void dosyaOlustur(FILE* dosya,char* dosyaAdi){
		dosya=fopen(dosyaAdi,"a");
		dosyaKontrol(dosya);
		fclose(dosya);
}

//Dosyada kac satir oldugunu gosterir
int kacinciSatir(FILE* dosya,char* txtDosya ){
	/*Dosyanin içinde kaçýncý satýrda olduðunu buluyor
	ve programý tekrar açtýðýmýzda kaçýncý satýrda olduðumuzu buluyor
	*/
	char satir[HARF];
	int a = 0;
	dosya=fopen(txtDosya,"r");
	dosyaKontrol(dosya);
	while(fgets(satir,sizeof(satir),dosya)){
		a++;
	}
	fclose(dosya);
	
	
	return a;
	
}

//Dosyaya soru ve cevap yazar
void soruCevapYaz(FILE* dosyaAdi,char* txtDosyaAdi,int kacinciSatir,char* soruYadaCevap){
		char soruCevap[HARF];
		
		dosyaAdi=fopen(txtDosyaAdi,"a");
		
		dosyaKontrol(dosyaAdi);
		
		printf("%d.%s= ",kacinciSatir,soruYadaCevap);
		fgets(soruCevap,HARF,stdin);
		fprintf(dosyaAdi,"%s",soruCevap);
		fclose(dosyaAdi);
		
}



//Dosyadan Soru ve Cevaplarý Gosterir
void soruVeCevapGoster(FILE* dosyaAdi,char* txtDosyasi,FILE* ikinciDosyaAdi, char* ikinciTxtDosya){
	
	char soruGoster[HARF];
	char cevapGoster[HARF];
	int i=1;
	
	dosyaAdi = fopen(txtDosyasi,"r");
	dosyaKontrol(dosyaAdi);
	ikinciDosyaAdi = fopen(ikinciTxtDosya,"r");
	dosyaKontrol(ikinciDosyaAdi);
	
	while(fgets(soruGoster,sizeof(soruGoster),dosyaAdi) && 
	fgets(cevapGoster,sizeof(cevapGoster),ikinciDosyaAdi))
	{
	
	printf("\n%d.Soru\n",i);
	printf("%s\n",soruGoster);
	printf("%d.Cevap\n",i++);
	printf("%s\n",cevapGoster);

	}
		
	fclose(dosyaAdi);
	fclose(ikinciDosyaAdi);
	
}


void randomSayi(int soruSayisi,int sayiArray[]){
	int i;

	for(i=0;i<soruSayisi;i++){
		sayiArray[i] = i;
		
	}
	
	for(i=0;i<soruSayisi;i++){
		int temp = sayiArray[i];
		int r = rand() % soruSayisi;
		
		sayiArray[i] = sayiArray[r];
		sayiArray[r] = temp;
	}
}

bool soruCevapla(soruVeCevap soruVeCevap){
	char cevaplar[3][HARF];
	int cevaplariKaristir[3];
	char cevabiYaz;
	bool kontrol = false;
	bool dogruSecenek = true;

	strcpy(cevaplar[0],soruVeCevap.cevap);
	strcpy(cevaplar[1],soruVeCevap.yanlisCevap[0]);
	strcpy(cevaplar[2],soruVeCevap.yanlisCevap[1]);
	randomSayi(3,cevaplariKaristir);
	
	
	printf("\tA) %s\t",cevaplar[cevaplariKaristir[0]]);
	printf("B) %s\t",cevaplar[cevaplariKaristir[1]]);
	printf("C) %s\n",cevaplar[cevaplariKaristir[2]]);
	do{
	scanf(" %c",&cevabiYaz);
	
	switch(cevabiYaz){
		case 'A':
		case 'a':
			kontrol = cevaplar[cevaplariKaristir[0]] == cevaplar[0];
			return kontrol;
			break;
		case 'B':
		case 'b':	
			kontrol = cevaplar[cevaplariKaristir[1]] == cevaplar[0];
			return kontrol;
			break;
		case 'C':
		case 'c':
			kontrol = cevaplar[cevaplariKaristir[2]] == cevaplar[0];
			return kontrol;
			break;
		default:
			printf("Lutfen gecerli bir secenegi seciniz\n");
			dogruSecenek = false;
			break;
		}
		
	}while(!dogruSecenek);
	
}

int main() {
	
	
	FILE *soru = NULL;
	FILE *cevap = NULL;
	FILE *yanlisCevaplar = NULL;
	
	bool secimSor = true;
	int secim;
	
	dosyaOlustur(soru,SORUDOSYASI);
	dosyaOlustur(cevap,CEVAPDOSYASI);
	dosyaOlustur(yanlisCevaplar,YANLISCEVAPLARDOSYASI);
	printf("Quizle Uygulamasina Hos Geldiniz\n\n");
	
	do{
		
	printf("Soru ve Cevaplarini Yazmak Icin 1\n\n");
	printf("Soru ve Cevaplara Goz Gezdirmek Icin 2\n\n");
	printf("Soru Cozmek Icin 3\n\n");
	printf("Programi Kapatmak Icin 4\n\n");
	scanf("%d",&secim);
	
	
	// Soru yazma ve Cevap Yazma
	if(secim == 1){
		int soruSayisi;
		int j,x,i;
		printf("Kac soru girmek istiyorsunuz\n");
		
		scanf("%d",&soruSayisi);
		//Scanf sorunu için
		fflush(stdin);
		
		j=kacinciSatir(soru,SORUDOSYASI);
		x=kacinciSatir(cevap,CEVAPDOSYASI);
		i=kacinciSatir(yanlisCevaplar,YANLISCEVAPLARDOSYASI);
		
		
		if(j!=x && x!=j){
				printf("Soru ve Cevap sirasinda bir problem olustu\n");
				printf("Satirlar birbirine uyusmuyor\n");
				x=j;
				cevap=fopen(CEVAPDOSYASI,"a");
				dosyaKontrol(cevap);
		
		
				fputs("Cevabi atlamisiniz.\n",cevap);
				fclose(cevap);
			
				
			}while(i % 2 != 0 || (j>0 && i==0)){
					printf("Yanlis cevpalarda eksik cevpalar var\n");
					yanlisCevaplar = fopen(YANLISCEVAPLARDOSYASI,"a");
					dosyaKontrol(yanlisCevaplar);
					
					fputs("Cevabi atlamisiniz.\n",yanlisCevaplar);
					fclose(yanlisCevaplar);
					i++;
				}
			
			
		for(;soruSayisi > 0;j++,x++,soruSayisi--){

		soruCevapYaz(soru,SORUDOSYASI,j+1,"Soru");
		soruCevapYaz(cevap,CEVAPDOSYASI,x+1,"Cevap");
		printf("Yanlis cevaplari girin\n");
		for(i=0;i<2;i++){
			soruCevapYaz(yanlisCevaplar,YANLISCEVAPLARDOSYASI,i+1,"Yanlis Cevap");
		}
		
		printf("\n");
			
		}
		
		
		
	}
	
	//Dosya Okuma
	else if(secim == 2){
		int soruSayisi = kacinciSatir(soru,SORUDOSYASI);
		if(soruSayisi>0){
		
		soruVeCevapGoster(soru,SORUDOSYASI,cevap,CEVAPDOSYASI);
		
	}else{
		printf("\nSoru ve cevaplar bulunmuyor\n\n");
	}
		
	}
	//Soru cevaplama
	else if(secim == 3){
		int soruSayisi = kacinciSatir(soru,SORUDOSYASI);
		
		if(soruSayisi>0){
		
		soruVeCevap quizle[soruSayisi];
		char ch[HARF];
	
		int i = 0;
		int j = 0;

		soru = fopen(SORUDOSYASI,"r");
		dosyaKontrol(soru);
		
		 while ((ch[i] = fgetc(soru)) != EOF)
        {
        	
            
            quizle[j].soru[i] = ch[i];
            if(ch[i] == '\n'){
            	i++;
            	quizle[j].soru[i] = '\0';
				j++;
				i=0;	
			}else{
				i++;
				
			}
        }
        fclose(soru);
        
        i=0;
        j=0;
       	memset(ch,0,HARF);
		
        cevap = fopen(CEVAPDOSYASI,"r");
		dosyaKontrol(cevap);
        while ((ch[i]=fgetc(cevap)) !=EOF)
            {

            quizle[j].cevap[i]=ch[i];
            if(ch[i]=='\n'){
            	i++;
            	quizle[j].cevap[i]='\0';
            	j++;
            	i=0;
			}else{
				i++;
			}
			
		}
        fclose(cevap);
        
        memset(ch,0,HARF);
        i=0;
        j=0;

        int sira = 0;
        
        yanlisCevaplar = fopen(YANLISCEVAPLARDOSYASI,"r");
		dosyaKontrol(yanlisCevaplar);
		
        while ((ch[i]=fgetc(yanlisCevaplar)) !=EOF)
            {
        
			quizle[j].yanlisCevap[sira][i]=ch[i];

            if(ch[i]=='\n'){
            	i++;
            	
            	quizle[j].yanlisCevap[sira][i]='\0';
            	if(sira == 1){
            		j++;
            		sira = 0;
        
				}else if(sira == 0){
					sira = 1;
				}
            	
            	i=0;
			}else{
				i++;
			}
		}
        fclose(yanlisCevaplar);
    
   		int arraySoruSayisi[soruSayisi];
		srand(time(0));
   		randomSayi(soruSayisi,arraySoruSayisi);
  		
	    printf("\n");

		
		bool dogruSecenekKontrol;
		int dogruCevapSayisi = 0;
		int yanlisCevapSayisi = 0;
		
		for(i=0;i<soruSayisi;i++){
			
			printf("%d .Soru = ", i+1);
			printf("%s\n",quizle[arraySoruSayisi[i]].soru);	
			fflush(stdin);
			dogruSecenekKontrol = soruCevapla(quizle[arraySoruSayisi[i]]);
			
			
			if(dogruSecenekKontrol){
			 
         	printf("Dogru Cevap\n\n");
         	dogruCevapSayisi++;
			} else{
				printf("Yanlis Cevap\n\n");
				yanlisCevapSayisi++;
			}

		}
			printf("Toplam Dogru Cevap %d\n",dogruCevapSayisi);
			printf("Yanlis Cevap Sayisi %d\n\n",yanlisCevapSayisi);
			
		  }else{
		  	printf("\nSoru bulunmuyor\n\n");
		  }  
		  
	        
	        }else if(secim == 4){
	        	secimSor = false;
	        	return 0;
			}
		else{ 
		printf("Lutfen 1 ve 4 arasinda bir sayi secin\n\n");
		}
	}while(secimSor);

	return 0;
}
