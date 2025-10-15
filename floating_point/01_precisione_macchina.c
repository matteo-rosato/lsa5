/*
 * Programma 1: Precisione Macchina e Informazioni sulla Rappresentazione
 * 
 * Calcola la precisione macchina (epsilon) per float e double
 * e mostra informazioni sulla rappresentazione IEEE 754
 */

#include <stdio.h>
#include <float.h>
#include <math.h>


float calcola_epsilon_float() {
    printf("\n\n=== Calcolo Precisione Macchina per FLOAT ===\n");
    printf("Iterazione\tEpsilon\t\t\t1.0 + epsilon\n");
    printf("----------------------------------------------------------\n");

    int cifre = 0;
    float epsilon = 0.5f;
    float valore = 1.0f + epsilon;

    while (valore > 1.0f) {
        if (cifre < 10 || cifre % 5 == 0) {
            printf("%d\t\t%.7e\t%.7f\n", cifre, epsilon, valore);
        }
        epsilon /= 2.0f;
        valore = 1.0f + epsilon;
        cifre++;
    }

    epsilon *= 2.0f;

    printf("\nPrecisione macchina calcolata: %.7e\n", epsilon);
    printf("Numero di cifre binarie della mantissa: %d\n", cifre);
    
    return epsilon;
}


double calcola_epsilon_double() {
    printf("\n\n=== Calcolo Precisione Macchina per DOUBLE ===\n");
    printf("Iterazione\tEpsilon\t\t\t\t1.0 + epsilon\n");
    printf("------------------------------------------------------------------\n");

    int cifre = 0;
    double epsilon = 0.5;
    double valore = 1.0 + epsilon;

    while (valore > 1.0) {
        if (cifre < 10 || cifre % 5 == 0) {
            printf("%d\t\t%.16e\t%.16f\n", cifre, epsilon, valore);
        }
        epsilon /= 2.0;
        valore = 1.0 + epsilon;
        cifre++;
    }

    epsilon *= 2.0;

    printf("\nPrecisione macchina calcolata: %.16e\n", epsilon);
    printf("Numero di cifre binarie della mantissa: %d\n", cifre);
    
    return epsilon;
}


void mostra_info_rappresentazione() {
    printf("\n\n=== INFORMAZIONI SULLA RAPPRESENTAZIONE IEEE 754 ===\n");
    
    printf("\nFLOAT (32 bit):");
    printf("\n  Bit totali:      %d", (int)sizeof(float) * 8);
    printf("\n  Bit mantissa:    23 (+ 1 implicito = 24 bit totali)");
    printf("\n  Bit esponente:   8");
    printf("\n  Bit segno:       1");
    printf("\n  Range:           %.2e a %.2e", FLT_MIN, FLT_MAX);
    printf("\n  Cifre decimali:  %d", FLT_DIG);
    printf("\n  Machine epsilon: %.7e", FLT_EPSILON);
    printf("\n  Epsilon = 2^(-23)");
    
    printf("\n\nDOUBLE (64 bit):");
    printf("\n  Bit totali:      %d", (int)sizeof(double) * 8);
    printf("\n  Bit mantissa:    52 (+ 1 implicito = 53 bit totali)");
    printf("\n  Bit esponente:   11");
    printf("\n  Bit segno:       1");
    printf("\n  Range:           %.2e a %.2e", DBL_MIN, DBL_MAX);
    printf("\n  Cifre decimali:  %d", DBL_DIG);
    printf("\n  Machine epsilon: %.16e", DBL_EPSILON);
    printf("\n  Epsilon = 2^(-52)");

    printf("\n\n  SIGNIFICATO di FLT_DIG = %d:", FLT_DIG);
    printf("\n  ✓ Con %d cifre decimali significative, QUALSIASI numero decimale", FLT_DIG);
    printf("\n    può essere arrotondato a float e convertito indietro senza perdita", FLT_DIG);
    printf("\n    delle %d cifre (round-trip esatto per input decimali)", FLT_DIG);
    printf("\n  ✗ NON significa che tutti i numeri decimali a %d cifre siano esatti", FLT_DIG);
    printf("\n    (solo alcuni numeri decimali sono rappresentabili esattamente in binario)");

}


int main() {
    printf("====================================================================\n");
    printf("  PRECISIONE MACCHINA E RAPPRESENTAZIONE IEEE 754\n");
    printf("====================================================================\n");

    mostra_info_rappresentazione();
    calcola_epsilon_float();
    calcola_epsilon_double();

    printf("\n\n====================================================================\n");
    printf("  CONCLUSIONI\n");
    printf("====================================================================\n");
    printf("1. Machine epsilon è il più piccolo numero tale che 1.0 + ε > 1.0\n");
    printf("2. Per float:  ε = 2^(-23) ≈ 1.19 × 10^(-7)\n");
    printf("3. Per double: ε = 2^(-52) ≈ 2.22 × 10^(-16)\n");
    printf("4. Il numero di iterazioni corrisponde ai bit della mantissa\n");
    printf("5. Mai usare == per confrontare numeri in virgola mobile\n");
    printf("====================================================================\n\n");

    return 0;
}
