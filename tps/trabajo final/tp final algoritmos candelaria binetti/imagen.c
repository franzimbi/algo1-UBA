#include"imagen.h"
#include"pixel.h"
#include"endiannes.h"



static int leer_entero_file(FILE *f){
    char s[MAX_LENGHT] = {0};
    int i = 0;
    char c;

    while((c = fgetc(f)) != EOF){
        if(c == '#'){
            while((c = fgetc(f)) != '\n'){
                //no hago nada
            }
            continue;
        } 
      //isspace devuelve falso(0) o verdadero(!= 0) si el caracter
      //es un espacio, tabulador, avance de linea,etc
        if(isspace(c) || i == MAX_LENGHT -1){
            if(i==0)
                continue;
            
            s[i]=0;
            int n = atoi(s);
            return n;
        }
        
        s[i] = c; 
        i++;
        
    }
    
    return -1;

}

static int leer_entero(){
    char s[MAX_LENGHT] = {0};
    int i = 0;
    char c;

    while((c = getchar()) != EOF){
        if(c == '#'){
            while((c = getchar()) != '\n'){
                //no hago nada
            }
            continue;
        } 
    
        if(isspace(c) || i == MAX_LENGHT -1){
            if(i==0)
                continue;
            
            s[i]=0;
            int n = atoi(s);
            return n;
        }
        
        s[i] = c; 
        i++;
        
    }
    
    return -1;

}




void espejar_verticalmente(imagen_t *imagen){
    size_t alto = imagen->alto;
    for(size_t x = 0; x < alto/2; x++){ 
        for(size_t y = 0; y < imagen->ancho; y++){
        pixel_t temp = imagen->lienzo[x][y];
        imagen->lienzo[x][y] = imagen->lienzo[alto-x-1][y];
        imagen->lienzo[alto -x-1][y] = temp;
        }

    }

}


void espejar_horizontalmente(imagen_t *imagen){
    size_t ancho = imagen->ancho;
    for(size_t x = 0; x < imagen->alto; x++){ 
        for(size_t y = 0; y < ancho / 2; y++){
        pixel_t temp = imagen->lienzo[x][y];
        imagen->lienzo[x][y] = imagen->lienzo[x][ancho - y - 1];
        imagen->lienzo[x][ancho - y - 1] = temp;
        }

    }

}




imagen_t *_imagen_crear(size_t ancho, size_t alto){
    if(ancho <= 0 || alto <= 0)
        return NULL;
   
    imagen_t *imagen;
    imagen = malloc(sizeof(imagen_t));

    if(imagen == NULL)
        return NULL;
    
    imagen -> ancho = ancho;
    imagen -> alto = alto;
    imagen -> lienzo = malloc(alto * sizeof(pixel_t *));

    if(imagen ->lienzo == NULL){
        free(imagen);
        return NULL;
    }

    for(size_t i = 0; i < alto; i++){
        imagen -> lienzo[i] = malloc(ancho * sizeof(pixel_t));
        if(imagen -> lienzo[i] == NULL){
            imagen -> alto = i;
            imagen_destruir(imagen);
            return NULL;
        }
    }
    return imagen;
}


imagen_t *imagen_recortar(const imagen_t *imagen, size_t x0, size_t y0, size_t ancho, size_t alto){
    
    if(x0 >= imagen -> ancho || y0 >= imagen -> alto)
        return NULL;

    if(x0 + ancho > imagen->ancho)
        ancho = imagen -> ancho - x0;


    if(y0 + alto > imagen->alto)
        alto = imagen -> alto - y0;
    
    
    imagen_t* recorte = _imagen_crear(ancho, alto);

    if(recorte == NULL)
        return NULL;

    for(int i=y0; i-y0 < alto; i++)
        for(int j=x0; j-x0 < ancho; j++)
            recorte->lienzo[i-y0][j-x0] = imagen->lienzo[i][j];
        
    
    return recorte;
}


 imagen_t *imagen_leer_stdin(){
    leer_entero(); //salteo P2
    size_t ancho = leer_entero();
    size_t alto = leer_entero();
    leer_entero(); //salteo maximo
    
    imagen_t *imagen = _imagen_crear(ancho, alto);

    if(imagen == NULL)
        return NULL;

    for(int x = 0; x < alto; x++)	 
        for (int y = 0; y < ancho; y++)
            imagen -> lienzo[x][y] = leer_entero();
        
    

    return imagen;    
 }

 void imagen_escribir(const imagen_t *imagen){
     printf("P2\n");
     printf("%ld\t%ld\n", imagen->ancho, imagen->alto);
     printf("255\n");

     for(int x = 0; x < imagen -> alto; x++){
         for(int y = 0; y < imagen -> ancho; y++)
             printf("%d ", imagen -> lienzo[x][y]);
         
         printf("\n");
     } 
 }
imagen_t *imagen_leer_bmp(FILE *f){
    
    
    char tipo[2];

    int16_t reservado[2];
    //encabezado de imagen
    int32_t ancho;
    int32_t alto;
    int32_t aux;
 
    

    fread(tipo, sizeof(char), 2, f);
    fread(&aux, sizeof(int32_t), 1, f);
    fread(reservado, sizeof(int16_t), 2,f);
    fread(&aux, sizeof(int32_t), 2, f);
    fread(&ancho, sizeof(int32_t), 1, f);
    fread(&alto, sizeof(int32_t), 1, f);
    fread(&aux, sizeof(int16_t), 2, f);
    fread(&aux, sizeof(int32_t), 6, f);
    

    
    imagen_t *imagen = _imagen_crear(ancho, alto);
    if(imagen == NULL)
        return NULL;
    size_t new_line;
    int8_t mas_ceros=0;

    if((imagen->alto)>0){
        for(size_t x=0; x<(imagen->alto); x++){
            
            for(size_t y=0; y<(imagen->ancho); y++){

                componente_t b, g, r;

                fread(&b, sizeof(componente_t), 1, f);
                fread(&g, sizeof(componente_t), 1, f);
                fread(&r, sizeof(componente_t), 1, f);

                imagen -> lienzo[(imagen->alto) -x -1][y] = pixel_desde_rgb(b,g,r);
            
            }
            new_line= (imagen->ancho * 3);
            while(new_line%4){
                fread(&mas_ceros, sizeof(int8_t), 1, f);
                new_line++;
            }
            
        }
    
    }
    return imagen;
}


void imagen_escribir_BMP(const imagen_t *imagen, FILE *f){
    //encabezado de archivo
    char tipo[2]="BM";
   //MEDIDA IMAGEN
    int32_t medida= (imagen -> ancho)*3;
    size_t x = medida % 4;
    size_t y= (4 - x) % 4;
        
    size_t scanline= (medida + y);
    size_t z= scanline * (imagen->alto);
    
    size_t aux= 14 + 40 + z; 
    medida= aux;
    

    int16_t reservado[2]={0};
    int32_t offset=54;
    
    //encabezado de imagen
    int32_t tamano=40;
    int32_t ancho=imagen->ancho;
    int32_t alto=imagen->alto;
    int16_t planos=1;
    int16_t bits_de_color=24;
    int32_t compresion=0;
    int32_t tamano_de_la_imagen=0;
    int32_t resolucion_X=0;
    int32_t resolucion_Y=0;
    int32_t tablas_de_color=0;
    int32_t colores_importantes=0;
    
    fwrite(tipo, sizeof(char), 2, f);
    escribir_int32_little_endian(f, medida);
    fwrite(reservado, sizeof(int16_t), 2,f);
    escribir_int32_little_endian(f, offset);
    escribir_int32_little_endian(f, tamano);
    escribir_int32_little_endian(f, ancho);
    escribir_int32_little_endian(f, alto);
    escribir_int16_little_endian(f, planos);
    escribir_int16_little_endian(f, bits_de_color);
    escribir_int32_little_endian(f, compresion);
    escribir_int32_little_endian(f, tamano_de_la_imagen);
    escribir_int32_little_endian(f, resolucion_X);
    escribir_int32_little_endian(f, resolucion_Y);
    escribir_int32_little_endian(f, tablas_de_color);
    escribir_int32_little_endian(f, colores_importantes);
   
    int8_t mas_ceros=0;
   
    if((imagen->alto)>0){
        for(size_t x=0; x<(imagen->alto); x++){
            for(size_t y=0; y<(imagen->ancho); y++){
                componente_t b, g, r;

                b = pixel_get_azul(imagen->lienzo[(imagen->alto)-x-1][y]);
                g = pixel_get_verde(imagen->lienzo[(imagen->alto)-x-1][y]);
                r = pixel_get_rojo(imagen->lienzo[(imagen->alto)-x-1][y]);

                fwrite(&b, sizeof(componente_t), 1, f);
                fwrite(&g, sizeof(componente_t), 1, f);
                fwrite(&r, sizeof(componente_t), 1, f);


            
            }
            
            size_t new_line= (imagen->ancho * 3);
            while(new_line%4){
                fwrite(&mas_ceros, sizeof(int8_t), 1, f);
                new_line++;
            }
        }
    
    }
 }

 
 imagen_t *imagen_leer_PPM_stdin(){
    leer_entero(); //salteo P2
    size_t ancho = leer_entero();
    size_t alto = leer_entero();
    leer_entero(); //salteo maximo
    imagen_t *imagen = _imagen_crear(ancho, alto);
    if(imagen == NULL)
        return NULL;
    componente_t rgb[3];
    for(int x = 0; x < alto; x++){	 
        for (int y = 0; y < ancho; y++){
            rgb[0]=leer_entero();
            rgb[1]=leer_entero();
            rgb[2]=leer_entero();

            imagen -> lienzo[x][y] = pixel_desde_rgb(rgb[0], rgb[1], rgb[2]);
        }
    }

    return imagen;    
 }



imagen_t *imagen_leer_PPM(FILE *f){
    leer_entero_file(f); //salteo P2
    size_t ancho = leer_entero_file(f);
    size_t alto = leer_entero_file(f);
    leer_entero_file(f); //salteo maximo
    imagen_t *imagen = _imagen_crear(ancho, alto);
    if(imagen == NULL)
        return NULL;
    componente_t rgb[3];
    for(int x = 0; x < alto; x++){	 
        for (int y = 0; y < ancho; y++){
            rgb[0]=leer_entero_file(f);
            rgb[1]=leer_entero_file(f);
            rgb[2]=leer_entero_file(f);

            imagen -> lienzo[x][y] = pixel_desde_rgb(rgb[0], rgb[1], rgb[2]);
        }
    }

    return imagen;    
 }


void imagen_escribir_PPM_stdout(const imagen_t *imagen){
     printf("P3\n");
     printf("%ld\t%ld\n", imagen->ancho, imagen->alto);
     printf("255\n");

     for(int x = 0; x < imagen -> alto; x++){
         for(int y = 0; y < imagen -> ancho; y++){
            componente_t rgb[3];
            rgb[0] = pixel_get_rojo(imagen->lienzo[x][y]);
            rgb[1] = pixel_get_verde(imagen->lienzo[x][y]);
            rgb[2] = pixel_get_azul(imagen->lienzo[x][y]);


            printf("%i %i %i\n", rgb[0], rgb[1], rgb[2]);
         }
     }
 }



void imagen_escribir_PPM(const imagen_t *imagen, FILE *f){
    fprintf(f , "P3\n");
    fprintf(f, "%ld\t%ld\n", imagen->ancho, imagen->alto);
    fprintf(f, "255\n");

    for(int x = 0; x < imagen -> alto; x++){
        for(int y = 0; y < imagen -> ancho; y++){
        componente_t rgb[3];
        rgb[0] = pixel_get_rojo(imagen->lienzo[x][y]);
        rgb[1] = pixel_get_verde(imagen->lienzo[x][y]);
        rgb[2] = pixel_get_azul(imagen->lienzo[x][y]);


        fprintf(f, "%i %i %i\n", rgb[0], rgb[1], rgb[2]);
        }
    }
}
 


imagen_t *imagen_clonar(const imagen_t *imagen){
    return imagen_recortar( imagen, 0, 0, imagen->ancho, imagen->alto);
}





void imagen_destruir(imagen_t *imagen){
    for(size_t i; i < imagen -> alto; i++)
        free (imagen->lienzo[i]);
    
    free(imagen->lienzo);
    free(imagen);
}






 



