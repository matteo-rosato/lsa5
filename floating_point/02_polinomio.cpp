/*
 * 02_polinomio.cpp
 * 
 * SCOPO:
 * Confrontare il metodo classico e il metodo di Horner per la valutazione
 * di un polinomio, evidenziando le differenze di stabilità numerica.
 * 
 * COEFFICIENTI:
 * I coefficienti sono memorizzati in ordine crescente:
 * a[0] = a₀ (termine costante)
 * a[1] = a₁ (coefficiente di x)
 * a[2] = a₂ (coefficiente di x²)
 * ...
 * a[n] = aₙ (coefficiente di x^n)
 * 
 * Quindi il polinomio p(x) = a₀ + a₁x + a₂x² + ... + aₙx^n
 * 
 * CASO DI TEST: Polinomio (x-1)³
 * Questo è un caso critico perché:
 * 1. Ha una radice multipla in x=1 (molteplicità 3)
 * 2. Espandendo: (x-1)³ = x³ - 3x² + 3x - 1
 * 3. Valutando vicino alla radice (x ≈ 1), si ha cancellazione numerica
 * 4. I termini grandi con segni opposti causano perdita di cifre significative
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>


using namespace std;


/*
 * metodo_classico - Valuta un polinomio con il metodo classico
 * 
 * ALGORITMO:
 * Calcola p(x) = a₀ + a₁x + a₂x² + ... + aₙx^n
 * sommando direttamente ogni termine aᵢ·x^i
 * 
 * COMPLESSITÀ:
 * - Moltiplicazioni: n(n+1)/2 + (n+1)
 * - Addizioni: n
 * - Totale: O(n²)
 * 
 * PROBLEMI NUMERICI:
 * 1. Calcolo ripetuto delle potenze x^i causa accumulo di errori
 * 2. Somma di termini grandi con segni opposti → cancellazione numerica
 * 3. Instabile per polinomi con radici vicine al punto di valutazione
 * 
 * PARAMETRI:
 * @param a   vettore dei coefficienti [a₀, a₁, ..., aₙ]
 * @param x0  punto in cui valutare il polinomio
 * @return    valore p(x0)
 */
float metodo_classico(const vector<float>& a, float x0) {
    int n = a.size() - 1;  // grado del polinomio
    float somma = 0.0f;
    
    // Somma ogni termine aᵢ·x^i
    for (int i = 0; i <= n; ++i) {
        // Calcola x^i moltiplicando i volte
        float xp = 1.0f;
        for (int j = 0; j < i; ++j) {
            xp *= x0;
        }
        somma += a[i] * xp;
    }
    return somma;
}


/*
 * metodo_horner - Valuta un polinomio con il metodo di Horner
 * 
 * ALGORITMO:
 * Riscrive p(x) = a₀ + a₁x + a₂x² + ... + aₙx^n come:
 * p(x) = a₀ + x(a₁ + x(a₂ + x(... + x(aₙ₋₁ + x·aₙ)...)))
 * 
 * Parte da aₙ e itera: r = r·x + aᵢ
 * 
 * COMPLESSITÀ:
 * - Moltiplicazioni: n
 * - Addizioni: n
 * - Totale: O(n) - molto più efficiente!
 * 
 * VANTAGGI NUMERICI:
 * 1. Non calcola esplicitamente le potenze x^i
 * 2. Riduce la propagazione degli errori di arrotondamento
 * 3. Più stabile numericamente del metodo classico
 * 4. Mitiga la cancellazione catastrofica
 * 
 * PARAMETRI:
 * @param a   vettore dei coefficienti [a₀, a₁, ..., aₙ]
 * @param x0  punto in cui valutare il polinomio
 * @return    valore p(x0)
 */
float metodo_horner(const vector<float>& a, float x0) {
    int n = a.size() - 1;  // grado del polinomio
    float r = a[n];        // inizia dal coefficiente di grado massimo

    // Itera da aₙ₋₁ fino a a₀
    for (int i = n - 1; i >= 0; --i) {
        r = r * x0 + a[i];
    }
    return r;
}


/*
 * leggi_coefficienti - Acquisisce i coefficienti del polinomio da tastiera
 * 
 * Legge (n+1) coefficienti in ordine crescente: a₀, a₁, ..., aₙ
 * 
 * @param a  vettore da riempire con i coefficienti
 * @param n  grado del polinomio
 * @return   true se la lettura ha successo, false altrimenti
 */
bool leggi_coefficienti(vector<float>& a, int n) {
    a.resize(n+1);
    for (int i = 0; i <= n; ++i) {
        float coeff;
        cout << "a[" << i << "] = ";
        if (!(cin >> coeff)) {
            cerr << "Valore non valido." << endl;
            return false;
        }
        a[i] = coeff;
    }
    return true;
}


/*
 * stampa_polinomio - Stampa il polinomio in forma standard
 * 
 * Stampa dal termine di grado massimo al termine costante
 * Gestisce correttamente i segni + e - tra i termini
 * 
 * @param a  vettore dei coefficienti [a₀, a₁, ..., aₙ]
 */
void stampa_polinomio(const vector<float>& a) {
    int n = a.size() - 1;
    for (int i = n; i >= 0; --i) {
        // Gestione segno: + per positivi, spazio per negativi (il segno - è già nel numero)
        if (i != n) {
            if (a[i] >= 0.0f)
                cout << " + ";
            else
                cout << " ";  // spazio prima del coefficiente negativo
        }
        // Stampa del termine
        if (i == 0)
            cout << a[i];  // termine costante
        else 
            cout << a[i] << "*x^" << i;  // termine con potenza
    }
    cout << '\n';
}


int main() {
    cout << "===========================================\n";
    cout << "  CONFRONTO: Metodo Classico vs Horner\n";
    cout << "===========================================\n\n";

    /*
     * CASO DI TEST: (x-1)³ valutato in x₀ = 1.001
     * 
     * PERCHÉ QUESTO POLINOMIO?
     * 1. Ha radice tripla in x=1 → alta sensibilità vicino alla radice
     * 2. Espansione: (x-1)³ = x³ - 3x² + 3x - 1
     *    Coefficienti: a = [-1, 3, -3, 1] (ordine crescente)
     * 3. Coefficienti alternati in segno → cancellazione numerica
     * 
     * VALORE ESATTO:
     * Per x₀ = 1.001, (x₀-1)³ = (0.001)³ = 1.0×10⁻⁹
     * 
     * PERCHÉ CI SONO DISCREPANZE?
     * 
     * METODO CLASSICO:
     * - Calcola: -1 + 3·1.001 - 3·(1.001)² + (1.001)³
     * - Somma numeri grandi (~3) con segni opposti
     * - Cancellazione: 3.003 - 3.006 ≈ 0.003, ma molti errori accumulati
     * - Errore di arrotondamento float (7 cifre) diventa significativo
     * 
     * METODO DI HORNER:
     * - Calcola: ((1·x - 3)·x + 3)·x - 1
     * - Opera con numeri intermedi più piccoli
     * - Meno moltiplicazioni → meno propagazione errori
     * - Più stabile numericamente
     * 
     * CONCLUSIONE:
     * Anche se nessuno dei due metodi è perfetto in float,
     * Horner tende a dare risultati più accurati, specialmente
     * per polinomi con radici vicine al punto di valutazione.
     */
    
    cout << "Polinomio: (x-1)^3 = x^3 - 3x^2 + 3x - 1\n";
    cout << "Punto di valutazione: x0 = 1.001\n";
    cout << "-------------------------------------------\n\n";
    
    // Coefficienti di (x-1)³ in ordine crescente: a₀, a₁, a₂, a₃
    vector<float> p1 = {-1.0f, 3.0f, -3.0f, 1.0f}; 
    float x0 = 1.001f;

    cout << "Forma espansa: ";
    stampa_polinomio(p1);
    cout << "\n";

    // Calcolo con i tre metodi
    float classico = metodo_classico(p1, x0);
    float horner = metodo_horner(p1, x0);
    float esatto = pow(0.001, 3);

    cout << "RISULTATI:\n";
    cout << "-------------------------------------------\n";
    cout << "Valore esatto:   " << setprecision(10) << esatto << "\n";
    cout << "Metodo classico: " << setprecision(10) << classico << "\n";
    cout << "Metodo Horner:   " << setprecision(10) << horner << "\n";
    cout << "\n";
    
    return 0;
}